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
    , m_maxFuelFlow(80.0)
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
    
    // Define chart area (excluding margins only - no legend)
    QRectF chartRect(MARGIN, MARGIN, 
                     width() - 2 * MARGIN, 
                     height() - 2 * MARGIN);

    // Draw chart components
    drawGrid(painter, chartRect);
    drawAxes(painter, chartRect);
    drawData(painter, chartRect);
    drawCurrentPoint(painter, chartRect);
    
    // Draw median line separately to ensure it's always visible
    drawMedianLine(painter, chartRect);
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
    painter->setPen(QPen(QColor(100, 100, 100), 1, Qt::SolidLine));

    // Only draw horizontal grid lines (Fuel Flow) - updated for 0-80 range with 20 intervals
    for (int flow = 0; flow <= 80; flow += 20) {
        double y = chartRect.bottom() - (flow / 80.0) * chartRect.height();
        painter->drawLine(QPointF(chartRect.left(), y), 
                         QPointF(chartRect.right(), y));
    }
}

void ChartRenderer::drawAxes(QPainter *painter, const QRectF &chartRect)
{
    painter->setFont(QFont("Arial", 10));

    // X-axis in dark grey
    painter->setPen(QPen(QColor(80, 80, 80), 2));
    painter->drawLine(chartRect.bottomLeft(), chartRect.bottomRight());

    // X-axis labels (RPM) - white color
    painter->setPen(QPen(Qt::white, 1));
    for (int rpm = 0; rpm <= 6000; rpm += 1000) {
        double x = chartRect.left() + (rpm / 6000.0) * chartRect.width();
        painter->drawText(QPointF(x - 15, chartRect.bottom() + 20), 
                         QString::number(rpm));
    }

    // Y-axis labels (Fuel Flow) - moved to right side with white color, updated for 0-80 range
    for (int flow = 0; flow <= 80; flow += 20) {
        double y = chartRect.bottom() - (flow / 80.0) * chartRect.height();
        painter->drawText(QPointF(chartRect.right() + 10, y + 5), 
                         QString::number(flow));
    }

    // Axis titles - dark grey color
    painter->setPen(QPen(QColor(80, 80, 80), 1));
    
    // Move Fuel Flow title to right side
    painter->save();
    painter->translate(chartRect.right() + 60, chartRect.center().y());
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

    // Calculate width of each rectangle based on RPM range - now 50 RPM per rectangle
    double rpmRange = m_maxRpm - m_minRpm;
    double rectWidth = chartRect.width() / (rpmRange / 50.0); // 50 RPM per rectangle
    
    // Enable antialiasing for smooth rounded corners
    painter->setRenderHint(QPainter::Antialiasing, true);
    
    for (const auto &pointVar : m_dataPoints) {
        QVariantMap point = pointVar.toMap();
        double rpm = point["rpm"].toDouble();
        double minFlow = point["minFuelFlow"].toDouble();
        double maxFlow = point["maxFuelFlow"].toDouble();
        
        // Calculate rectangle position and dimensions
        double x = chartRect.left() + (rpm / rpmRange) * chartRect.width() - rectWidth / 2;
        double minY = chartRect.bottom() - (minFlow / (m_maxFuelFlow - m_minFuelFlow)) * chartRect.height();
        double maxY = chartRect.bottom() - (maxFlow / (m_maxFuelFlow - m_minFuelFlow)) * chartRect.height();
        double rectHeight = minY - maxY;
        
        // Create the rectangle with 1.5 pixel gap on each side (3 pixels total gap between rectangles)
        double gap = 1.5; // 1.5 pixels gap on each side
        QRectF rect(x + gap, maxY, rectWidth - (gap * 2), rectHeight);
        
        // Create gradient for modern look - dark grey with 50% transparency
        QLinearGradient gradient(rect.topLeft(), rect.bottomLeft());
        gradient.setColorAt(0, QColor(80, 80, 80, 128));   // 50% transparent dark grey
        gradient.setColorAt(0.5, QColor(70, 70, 70, 128)); // 50% transparent darker grey
        gradient.setColorAt(1, QColor(60, 60, 60, 128));   // 50% transparent darkest grey
        
        // Draw rectangle with gradient and rounded corners (smaller radius for smaller rectangles)
        painter->setBrush(QBrush(gradient));
        painter->setPen(QPen(QColor(50, 50, 50, 128), 1)); // 50% transparent dark border
        painter->drawRoundedRect(rect, 2, 2); // 2px rounded corners for smaller rectangles
    }
    
    // Reset brush for other elements
    painter->setBrush(Qt::NoBrush);
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
    
    // Map the current RPM and median fuel flow to chart coordinates for reference
    QPointF currentPointOnMedian = mapToChart(m_currentRpm, medianFuelFlowAtCurrentRpm, chartRect);
    
    // Map the current RPM and ACTUAL current fuel flow to chart coordinates
    QPointF actualCurrentPoint = mapToChart(m_currentRpm, m_currentFuelFlow, chartRect);
    
    // Draw current point at the actual fuel flow position - smaller dot without white border
    QColor pointColor = m_isEcoMode ? QColor(0, 200, 0) : QColor(255, 150, 0);
    painter->setBrush(QBrush(pointColor));
    painter->setPen(QPen(pointColor, 1)); // Use same color for border
    painter->drawEllipse(actualCurrentPoint, 6, 6); // Draw at actual current fuel flow position
}

void ChartRenderer::drawLegend(QPainter *painter, const QRectF &chartRect)
{
    QRectF legendRect(chartRect.left(), chartRect.bottom() + 10, 
                     chartRect.width(), LEGEND_HEIGHT - 10);

    painter->setFont(QFont("Arial", 10));
    
    double itemWidth = legendRect.width() / 4;
    double y = legendRect.top() + 20;

    // Min/Max range - show as a small rectangle with dark grey gradient and rounded corners
    QLinearGradient legendGradient(QPointF(legendRect.left(), y), 
                                   QPointF(legendRect.left(), y + 10));
    legendGradient.setColorAt(0, QColor(80, 80, 80, 128));   // 50% transparent dark grey
    legendGradient.setColorAt(0.5, QColor(70, 70, 70, 128)); // 50% transparent darker grey
    legendGradient.setColorAt(1, QColor(60, 60, 60, 128));   // 50% transparent darkest grey
    painter->setBrush(QBrush(legendGradient));
    painter->setPen(QPen(QColor(50, 50, 50, 128), 1)); // 50% transparent dark border
    painter->drawRoundedRect(QRectF(legendRect.left(), y, 20, 10), 2, 2);
    painter->setPen(QPen(Qt::white));
    painter->drawText(QPointF(legendRect.left() + 25, y + 10), "Fuel Range (50 RPM blocks)");

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
    
    // Draw median line in white - made thinner
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::white, 1, Qt::SolidLine));
    painter->drawPath(medianPath);
}
