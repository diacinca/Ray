#include "chartdatamodel.h"
#include <QRandomGenerator>
#include <QtMath>
#include <algorithm>

ChartDataModel::ChartDataModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_currentRpm(1500.0)
    , m_currentFuelFlow(0.0)
    , m_isEcoMode(false)
{
}

int ChartDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_dataPoints.size();
}

QVariant ChartDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_dataPoints.size())
        return QVariant();

    const DataPoint &point = m_dataPoints.at(index.row());

    switch (role) {
    case RpmRole:
        return point.rpm;
    case MinFuelFlowRole:
        return point.minFuelFlow;
    case MaxFuelFlowRole:
        return point.maxFuelFlow;
    case MedianFuelFlowRole:
        return point.medianFuelFlow;
    case CurrentFuelFlowRole:
        return point.currentFuelFlow;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ChartDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RpmRole] = "rpm";
    roles[MinFuelFlowRole] = "minFuelFlow";
    roles[MaxFuelFlowRole] = "maxFuelFlow";
    roles[MedianFuelFlowRole] = "medianFuelFlow";
    roles[CurrentFuelFlowRole] = "currentFuelFlow";
    return roles;
}

void ChartDataModel::setCurrentRpm(double rpm)
{
    if (qFuzzyCompare(m_currentRpm, rpm))
        return;

    m_currentRpm = qBound(0.0, rpm, 6000.0);
    updateCurrentFuelFlow();
    emit currentRpmChanged();
}

void ChartDataModel::generateSampleData()
{
    beginResetModel();
    m_dataPoints.clear();

    // Generate data points every 50 RPM for finer granularity
    for (int rpm = 0; rpm <= 6000; rpm += 50) {
        DataPoint point;
        point.rpm = rpm;

        // Base fuel flow calculation (quadratic relationship with RPM)
        double baseFuelFlow = 0.5 + (rpm / 6000.0) * 45.0 + qPow(rpm / 6000.0, 2) * 5.0;
        
        // Add some variation for min/max
        double variation = baseFuelFlow * 0.2; // 20% variation
        point.minFuelFlow = qMax(0.0, baseFuelFlow - variation);
        point.maxFuelFlow = qMin(50.0, baseFuelFlow + variation);
        
        // Set median to be clearly between min and max (closer to optimal efficiency)
        point.medianFuelFlow = point.minFuelFlow + (point.maxFuelFlow - point.minFuelFlow) * 0.4;

        // Current fuel flow will be updated based on current RPM
        point.currentFuelFlow = baseFuelFlow;

        m_dataPoints.append(point);
    }

    endResetModel();
    updateCurrentFuelFlow();
}

QVariantList ChartDataModel::getDataPoints() const
{
    QVariantList result;
    for (const auto &point : m_dataPoints) {
        QVariantMap pointMap;
        pointMap["rpm"] = point.rpm;
        pointMap["minFuelFlow"] = point.minFuelFlow;
        pointMap["maxFuelFlow"] = point.maxFuelFlow;
        pointMap["medianFuelFlow"] = point.medianFuelFlow;
        pointMap["currentFuelFlow"] = point.currentFuelFlow;
        result.append(pointMap);
    }
    return result;
}

double ChartDataModel::getCurrentFuelFlowAtRpm(double rpm) const
{
    return interpolateFuelFlow(rpm, false);
}

void ChartDataModel::updateCurrentFuelFlow()
{
    double newFuelFlow = interpolateFuelFlow(m_currentRpm, false);
    
    // Add some random variation to simulate real conditions
    auto *generator = QRandomGenerator::global();
    double variation = (generator->generateDouble() - 0.5) * 0.3; // ±15% variation
    newFuelFlow *= (1.0 + variation);
    
    if (!qFuzzyCompare(m_currentFuelFlow, newFuelFlow)) {
        m_currentFuelFlow = newFuelFlow;
        
        // Determine if we're in eco mode (below median)
        double medianAtCurrentRpm = interpolateFuelFlow(m_currentRpm, true);
        bool newEcoMode = m_currentFuelFlow < medianAtCurrentRpm;
        
        if (m_isEcoMode != newEcoMode) {
            m_isEcoMode = newEcoMode;
            emit ecoModeChanged();
        }
        
        emit currentFuelFlowChanged();
    }
}

double ChartDataModel::interpolateFuelFlow(double rpm, bool useMedian) const
{
    if (m_dataPoints.isEmpty())
        return 0.0;

    // Find the two nearest points for interpolation
    auto it = std::lower_bound(m_dataPoints.begin(), m_dataPoints.end(), rpm,
                               [](const DataPoint &point, double value) {
                                   return point.rpm < value;
                               });

    if (it == m_dataPoints.begin()) {
        return useMedian ? it->medianFuelFlow : it->medianFuelFlow;
    }
    
    if (it == m_dataPoints.end()) {
        return useMedian ? (it - 1)->medianFuelFlow : (it - 1)->medianFuelFlow;
    }

    // Linear interpolation between two points
    const DataPoint &p1 = *(it - 1);
    const DataPoint &p2 = *it;
    
    double ratio = (rpm - p1.rpm) / (p2.rpm - p1.rpm);
    
    if (useMedian) {
        return p1.medianFuelFlow + ratio * (p2.medianFuelFlow - p1.medianFuelFlow);
    } else {
        // For current fuel flow, interpolate the median but add some variation
        double baseFuelFlow = p1.medianFuelFlow + ratio * (p2.medianFuelFlow - p1.medianFuelFlow);
        return baseFuelFlow;
    }
}
