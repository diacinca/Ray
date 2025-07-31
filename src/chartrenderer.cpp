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
    
    // Fill background with black
    painter->fillRect(boundingRect(), Qt::black);
    
    // Define chart area (excluding margins and legend)
    QRectF chartRect(MARGIN, MARGIN, 
                     width() - 2 * MARGIN, 
                     height() - 2 * MARGIN - LEGEND_HEIGHT);

    // Draw chart components
    drawGrid(painter, chartRect);
    drawAxes(painter, chartRect);
    drawData(painter, chartRect);
    drawCurrentPoint(painter, chartRect);
    
    // Draw median line separately to ensure it's always visible
    drawMedianLine(painter, chartRect);
    
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
    painter->setPen(QPen(QColor(100, 100, 100), 1, Qt::DotLine));

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
    painter->setPen(QPen(Qt::white, 2));
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

    // Draw fill area (min-max range) - transparent blue
    painter->setBrush(QBrush(QColor(0, 100, 255, 80)));
    painter->setPen(Qt::NoPen);
    painter->drawPolygon(fillPolygon);

    // Draw min line in white
    painter->setPen(QPen(Qt::white, 2, Qt::DashLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(minPath);

    // Draw max line in white
    painter->setPen(QPen(Qt::white, 2, Qt::DashLine));
    painter->drawPath(maxPath);
}


void ChartRenderer::drawCurrentPoint(QPainter *painter, const QRectF &chartRect)
{
    // Calculate the median fuel flow at current RPM
    double medianFuelFlowAtCurrentRpm = 0.0;
    bool foundMedian = false;
    
    // Find median fuel flow by interpolating between data points
    for (int i = 0; i < m_dataPoints.size() - 1; ++i) {
        QVariantMap point1 = m_dataPoints[i].toMap();
        QVariantMap point2 = m_dataPoints[i + 1].toMap();
        
        double rpm1 = point1["rpm"].toDouble();
        double rpm2 = point2["rpm"].toDouble();
        
        if (m_currentRpm >= rpm1 && m_currentRpm <= rpm2) {
            double median1 = point1["medianFuelFlow"].toDouble();
            double median2 = point2["medianFuelFlow"].toDouble();
            
            // Linear interpolation
            double ratio = (m_currentRpm - rpm1) / (rpm2 - rpm1);
            medianFuelFlowAtCurrentRpm = median1 + ratio * (median2 - median1);
            foundMedian = true;
            break;
        }
    }
    
    // If we couldn't interpolate, use the closest point
    if (!foundMedian && !m_dataPoints.isEmpty()) {
        // Find closest data point
        int closestIndex = 0;
        double minDistance = qAbs(m_dataPoints[0].toMap()["rpm"].toDouble() - m_currentRpm);
        
        for (int i = 1; i < m_dataPoints.size(); ++i) {
            double distance = qAbs(m_dataPoints[i].toMap()["rpm"].toDouble() - m_currentRpm);
            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = i;
            }
        }
        medianFuelFlowAtCurrentRpm = m_dataPoints[closestIndex].toMap()["medianFuelFlow"].toDouble();
    }
    
    // Map the current RPM and median fuel flow to chart coordinates
    QPointF currentPointOnMedian = mapToChart(m_currentRpm, medianFuelFlowAtCurrentRpm, chartRect);
    
    // Draw vertical line at current RPM
    painter->setPen(QPen(Qt::lightGray, 2, Qt::DotLine));
    painter->drawLine(QPointF(currentPointOnMedian.x(), chartRect.top()),
                     QPointF(currentPointOnMedian.x(), chartRect.bottom()));

    // Draw current point on the median line
    QColor pointColor = m_isEcoMode ? QColor(0, 200, 0) : QColor(255, 150, 0);
    painter->setBrush(QBrush(pointColor));
    painter->setPen(QPen(Qt::white, 3));
    painter->drawEllipse(currentPointOnMedian, 10, 10);

    // Draw current value label
    painter->setFont(QFont("Arial", 12, QFont::Bold));
    painter->setPen(QPen(Qt::white));
    QString label = QString("RPM: %1\nMedian: %2 L/h\nCurrent: %3 L/h\n%4")
                    .arg(QString::number(m_currentRpm, 'f', 0))
                    .arg(QString::number(medianFuelFlowAtCurrentRpm, 'f', 1))
                    .arg(QString::number(m_currentFuelFlow, 'f', 1))
                    .arg(m_isEcoMode ? "ECO MODE" : "NORMAL");
    
    QPointF labelPos = currentPointOnMedian + QPointF(15, -40);
    if (labelPos.x() + 120 > chartRect.right()) {
        labelPos.setX(currentPointOnMedian.x() - 120);
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
    painter->setBrush(QBrush(QColor(0, 100, 255, 80)));
    painter->setPen(QPen(Qt::white, 2, Qt::DashLine));
    painter->drawRect(QRectF(legendRect.left(), y, 20, 10));
    painter->setPen(QPen(Qt::white));
    painter->drawText(QPointF(legendRect.left() + 25, y + 10), "Min/Max Range");

    // Median line
    painter->setPen(QPen(Qt::white, 3));
    painter->drawLine(QPointF(legendRect.left() + itemWidth, y + 5),
                     QPointF(legendRect.left() + itemWidth + 20, y + 5));
    painter->setPen(QPen(Qt::white));
    painter->drawText(QPointF(legendRect.left() + itemWidth + 25, y + 10), "Median");

    // Eco mode
    painter->setBrush(QBrush(QColor(0, 200, 0)));
    painter->setPen(QPen(Qt::white, 2));
    painter->drawEllipse(QPointF(legendRect.left() + 2 * itemWidth + 10, y + 5), 5, 5);
    painter->setPen(QPen(Qt::white));
    painter->drawText(QPointF(legendRect.left() + 2 * itemWidth + 25, y + 10), "Eco Mode");

    // Normal mode
    painter->setBrush(QBrush(QColor(255, 150, 0)));
    painter->setPen(QPen(Qt::white, 2));
    painter->drawEllipse(QPointF(legendRect.left() + 3 * itemWidth + 10, y + 5), 5, 5);
    painter->setPen(QPen(Qt::white));
    painter->drawText(QPointF(legendRect.left() + 3 * itemWidth + 25, y + 10), "Normal");
}

QPointF ChartRenderer::mapToChart(double rpm, double fuelFlow, const QRectF &chartRect) const
{
    double x = chartRect.left() + (rpm / (m_maxRpm - m_minRpm)) * chartRect.width();
    double y = chartRect.bottom() - (fuelFlow / (m_maxFuelFlow - m_minFuelFlow)) * chartRect.height();
    return QPointF(x, y);
}

void ChartRenderer::drawMedianLine(QPainter *painter, const QRectF &chartRect)
{
    if (m_dataPoints.size() < 2)
        return;
        
    // Create median path
    QPainterPath medianPath;
    bool firstPoint = true;
    
    for (const auto &pointVar : m_dataPoints) {
        QVariantMap point = pointVar.toMap();
        double rpm = point["rpm"].toDouble();
        double medianFlow = point["medianFuelFlow"].toDouble();
        
        QPointF medianPoint = mapToChart(rpm, medianFlow, chartRect);
        
        if (firstPoint) {
            medianPath.moveTo(medianPoint);
            firstPoint = false;
        } else {
            medianPath.lineTo(medianPoint);
        }
    }
    
    // Draw median line in white
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::white, 3, Qt::SolidLine));
    painter->drawPath(medianPath);
}
