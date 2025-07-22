#include "chartrenderer.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QFontMetrics>
#include <QtMath>
#include <QPainterPath>

ChartRenderer::ChartRenderer(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_currentRpm(1500.0)
    , m_currentFuelFlow(15.0)
    , m_isEcoMode(false)
    , m_minRpm(0.0)
    , m_maxRpm(6000.0)
    , m_minFuelFlow(0.0)
    , m_maxFuelFlow(50.0)
{
    setAntialiasing(true);
}

void ChartRenderer::paint(QPainter *painter)
{
    if (m_dataPoints.isEmpty())
        return;

    painter->setRenderHint(QPainter::Antialiasing, true);
    
    // Define chart area (excluding margins and legend)
    QRectF chartRect(MARGIN, MARGIN, 
                     width() - 2 * MARGIN, 
                     height() - 2 * MARGIN - LEGEND_HEIGHT);

    // Draw chart components
    drawGrid(painter, chartRect);
    drawAxes(painter, chartRect);
    drawData(painter, chartRect);
    drawCurrentPoint(painter, chartRect);
    drawLegend(painter, chartRect);
}

void ChartRenderer::setDataPoints(const QVariantList &dataPoints)
{
    if (m_dataPoints != dataPoints) {
        m_dataPoints = dataPoints;
        emit dataPointsChanged();
        update();
    }
}

void ChartRenderer::setCurrentRpm(double rpm)
{
    if (!qFuzzyCompare(m_currentRpm, rpm)) {
        m_currentRpm = rpm;
        emit currentRpmChanged();
        update();
    }
}

void ChartRenderer::setCurrentFuelFlow(double fuelFlow)
{
    if (!qFuzzyCompare(m_currentFuelFlow, fuelFlow)) {
        m_currentFuelFlow = fuelFlow;
        emit currentFuelFlowChanged();
        update();
    }
}

void ChartRenderer::setIsEcoMode(bool isEco)
{
    if (m_isEcoMode != isEco) {
        m_isEcoMode = isEco;
        emit ecoModeChanged();
        update();
    }
}

void ChartRenderer::setMinRpm(double minRpm)
{
    if (!qFuzzyCompare(m_minRpm, minRpm)) {
        m_minRpm = minRpm;
        emit minRpmChanged();
        update();
    }
}

void ChartRenderer::setMaxRpm(double maxRpm)
{
    if (!qFuzzyCompare(m_maxRpm, maxRpm)) {
        m_maxRpm = maxRpm;
        emit maxRpmChanged();
        update();
    }
}

void ChartRenderer::setMinFuelFlow(double minFuelFlow)
{
    if (!qFuzzyCompare(m_minFuelFlow, minFuelFlow)) {
        m_minFuelFlow = minFuelFlow;
        emit minFuelFlowChanged();
        update();
    }
}

void ChartRenderer::setMaxFuelFlow(double maxFuelFlow)
{
    if (!qFuzzyCompare(m_maxFuelFlow, maxFuelFlow)) {
        m_maxFuelFlow = maxFuelFlow;
        emit maxFuelFlowChanged();
        update();
    }
}

void ChartRenderer::drawGrid(QPainter *painter, const QRectF &chartRect)
{
    painter->setPen(QPen(QColor(200, 200, 200), 1, Qt::DotLine));

    // Vertical grid lines (RPM)
    for (int rpm = 0; rpm <= 6000; rpm += 1000) {
        double x = chartRect.left() + (rpm / 6000.0) * chartRect.width();
        painter->drawLine(QPointF(x, chartRect.top()), 
                         QPointF(x, chartRect.bottom()));
    }

    // Horizontal grid lines (Fuel Flow)
    for (int flow = 0; flow <= 50; flow += 10) {
        double y = chartRect.bottom() - (flow / 50.0) * chartRect.height();
        painter->drawLine(QPointF(chartRect.left(), y), 
                         QPointF(chartRect.right(), y));
    }
}

void ChartRenderer::drawAxes(QPainter *painter, const QRectF &chartRect)
{
    painter->setPen(QPen(Qt::black, 2));
    painter->setFont(QFont("Arial", 10));

    // X-axis
    painter->drawLine(chartRect.bottomLeft(), chartRect.bottomRight());
    
    // Y-axis
    painter->drawLine(chartRect.bottomLeft(), chartRect.topLeft());

    // X-axis labels (RPM)
    for (int rpm = 0; rpm <= 6000; rpm += 1000) {
        double x = chartRect.left() + (rpm / 6000.0) * chartRect.width();
        painter->drawText(QPointF(x - 15, chartRect.bottom() + 20), 
                         QString::number(rpm));
    }

    // Y-axis labels (Fuel Flow)
    for (int flow = 0; flow <= 50; flow += 10) {
        double y = chartRect.bottom() - (flow / 50.0) * chartRect.height();
        painter->drawText(QPointF(chartRect.left() - 40, y + 5), 
                         QString::number(flow));
    }

    // Axis titles
    painter->save();
    painter->translate(chartRect.left() - 50, chartRect.center().y());
    painter->rotate(-90);
    painter->drawText(QPointF(-50, 0), "Fuel Flow (L/h)");
    painter->restore();

    painter->drawText(QPointF(chartRect.center().x() - 30, chartRect.bottom() + 50), 
                     "RPM");
}

void ChartRenderer::drawData(QPainter *painter, const QRectF &chartRect)
{
    if (m_dataPoints.size() < 2)
        return;

    // Prepare paths for different data series
    QPainterPath minPath, maxPath, medianPath;
    QPolygonF fillPolygon;

    for (const auto &pointVar : m_dataPoints) {
        QVariantMap point = pointVar.toMap();
        double rpm = point["rpm"].toDouble();
        double minFlow = point["minFuelFlow"].toDouble();
        double maxFlow = point["maxFuelFlow"].toDouble();
        double medianFlow = point["medianFuelFlow"].toDouble();

        QPointF minPoint = mapToChart(rpm, minFlow, chartRect);
        QPointF maxPoint = mapToChart(rpm, maxFlow, chartRect);
        QPointF medianPoint = mapToChart(rpm, medianFlow, chartRect);

        if (minPath.isEmpty()) {
            minPath.moveTo(minPoint);
            maxPath.moveTo(maxPoint);
            medianPath.moveTo(medianPoint);
            fillPolygon << minPoint;
        } else {
            minPath.lineTo(minPoint);
            maxPath.lineTo(maxPoint);
            medianPath.lineTo(medianPoint);
            fillPolygon << minPoint;
        }
    }

    // Create fill polygon for min-max range
    for (int i = m_dataPoints.size() - 1; i >= 0; --i) {
        QVariantMap point = m_dataPoints[i].toMap();
        double rpm = point["rpm"].toDouble();
        double maxFlow = point["maxFuelFlow"].toDouble();
        fillPolygon << mapToChart(rpm, maxFlow, chartRect);
    }

    // Draw fill area (min-max range)
    painter->setBrush(QBrush(QColor(100, 150, 255, 50)));
    painter->setPen(Qt::NoPen);
    painter->drawPolygon(fillPolygon);

    // Draw min line
    painter->setPen(QPen(QColor(255, 100, 100), 2, Qt::DashLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(minPath);

    // Draw max line
    painter->setPen(QPen(QColor(255, 100, 100), 2, Qt::DashLine));
    painter->drawPath(maxPath);

    // Draw median line
    painter->setPen(QPen(QColor(50, 150, 50), 3));
    painter->drawPath(medianPath);
}

void ChartRenderer::drawCurrentPoint(QPainter *painter, const QRectF &chartRect)
{
    QPointF currentPoint = mapToChart(m_currentRpm, m_currentFuelFlow, chartRect);
    
    // Draw vertical line at current RPM
    painter->setPen(QPen(Qt::darkGray, 2, Qt::DotLine));
    painter->drawLine(QPointF(currentPoint.x(), chartRect.top()),
                     QPointF(currentPoint.x(), chartRect.bottom()));

    // Draw current point
    QColor pointColor = m_isEcoMode ? QColor(0, 200, 0) : QColor(255, 150, 0);
    painter->setBrush(QBrush(pointColor));
    painter->setPen(QPen(Qt::black, 2));
    painter->drawEllipse(currentPoint, 8, 8);

    // Draw current value label
    painter->setFont(QFont("Arial", 12, QFont::Bold));
    painter->setPen(QPen(Qt::black));
    QString label = QString("RPM: %1\nFuel: %2 L/h\n%3")
                    .arg(QString::number(m_currentRpm, 'f', 0))
                    .arg(QString::number(m_currentFuelFlow, 'f', 1))
                    .arg(m_isEcoMode ? "ECO MODE" : "NORMAL");
    
    QPointF labelPos = currentPoint + QPointF(15, -30);
    if (labelPos.x() + 100 > chartRect.right()) {
        labelPos.setX(currentPoint.x() - 100);
    }
    
    painter->drawText(labelPos, label);
}

void ChartRenderer::drawLegend(QPainter *painter, const QRectF &chartRect)
{
    QRectF legendRect(chartRect.left(), chartRect.bottom() + 10, 
                     chartRect.width(), LEGEND_HEIGHT - 10);

    painter->setFont(QFont("Arial", 10));
    
    double itemWidth = legendRect.width() / 4;
    double y = legendRect.top() + 20;

    // Min/Max range
    painter->setBrush(QBrush(QColor(100, 150, 255, 50)));
    painter->setPen(QPen(QColor(255, 100, 100), 2, Qt::DashLine));
    painter->drawRect(QRectF(legendRect.left(), y, 20, 10));
    painter->setPen(QPen(Qt::black));
    painter->drawText(QPointF(legendRect.left() + 25, y + 10), "Min/Max Range");

    // Median line
    painter->setPen(QPen(QColor(50, 150, 50), 3));
    painter->drawLine(QPointF(legendRect.left() + itemWidth, y + 5),
                     QPointF(legendRect.left() + itemWidth + 20, y + 5));
    painter->setPen(QPen(Qt::black));
    painter->drawText(QPointF(legendRect.left() + itemWidth + 25, y + 10), "Median");

    // Eco mode
    painter->setBrush(QBrush(QColor(0, 200, 0)));
    painter->setPen(QPen(Qt::black, 2));
    painter->drawEllipse(QPointF(legendRect.left() + 2 * itemWidth + 10, y + 5), 5, 5);
    painter->setPen(QPen(Qt::black));
    painter->drawText(QPointF(legendRect.left() + 2 * itemWidth + 25, y + 10), "Eco Mode");

    // Normal mode
    painter->setBrush(QBrush(QColor(255, 150, 0)));
    painter->setPen(QPen(Qt::black, 2));
    painter->drawEllipse(QPointF(legendRect.left() + 3 * itemWidth + 10, y + 5), 5, 5);
    painter->setPen(QPen(Qt::black));
    painter->drawText(QPointF(legendRect.left() + 3 * itemWidth + 25, y + 10), "Normal");
}

QPointF ChartRenderer::mapToChart(double rpm, double fuelFlow, const QRectF &chartRect) const
{
    double x = chartRect.left() + (rpm / (m_maxRpm - m_minRpm)) * chartRect.width();
    double y = chartRect.bottom() - (fuelFlow / (m_maxFuelFlow - m_minFuelFlow)) * chartRect.height();
    return QPointF(x, y);
}
