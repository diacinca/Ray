#ifndef CHARTDATAMODEL_H
#define CHARTDATAMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QVariant>

struct DataPoint {
    double rpm;
    double minFuelFlow;
    double maxFuelFlow;
    double medianFuelFlow;
    double currentFuelFlow;
};

class ChartDataModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(double minRpm READ minRpm NOTIFY dataChanged)
    Q_PROPERTY(double maxRpm READ maxRpm NOTIFY dataChanged)
    Q_PROPERTY(double minFuelFlow READ minFuelFlow NOTIFY dataChanged)
    Q_PROPERTY(double maxFuelFlow READ maxFuelFlow NOTIFY dataChanged)
    Q_PROPERTY(double currentRpm READ currentRpm WRITE setCurrentRpm NOTIFY currentRpmChanged)
    Q_PROPERTY(double currentFuelFlow READ currentFuelFlow NOTIFY currentFuelFlowChanged)
    Q_PROPERTY(bool isEcoMode READ isEcoMode NOTIFY ecoModeChanged)

public:
    enum DataRoles {
        RpmRole = Qt::UserRole + 1,
        MinFuelFlowRole,
        MaxFuelFlowRole,
        MedianFuelFlowRole,
        CurrentFuelFlowRole
    };

    explicit ChartDataModel(QObject *parent = nullptr);

    // QAbstractListModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Property getters
    double minRpm() const { return 0.0; }
    double maxRpm() const { return 6000.0; }
    double minFuelFlow() const { return 0.0; }
    double maxFuelFlow() const { return 50.0; }
    double currentRpm() const { return m_currentRpm; }
    double currentFuelFlow() const { return m_currentFuelFlow; }
    bool isEcoMode() const { return m_isEcoMode; }

    // Property setters
    void setCurrentRpm(double rpm);

    // Public methods
    Q_INVOKABLE void generateSampleData();
    Q_INVOKABLE QVariantList getDataPoints() const;
    Q_INVOKABLE double getCurrentFuelFlowAtRpm(double rpm) const;

    Q_SIGNAL void dataChanged();

signals:
    void currentRpmChanged();
    void currentFuelFlowChanged();
    void ecoModeChanged();

private:
    void updateCurrentFuelFlow();
    double interpolateFuelFlow(double rpm, bool useMedian = false) const;

    QList<DataPoint> m_dataPoints;
    double m_currentRpm;
    double m_currentFuelFlow;
    bool m_isEcoMode;
};

#endif // CHARTDATAMODEL_H
