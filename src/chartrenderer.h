#ifndef CHARTRENDERER_H
#define CHARTRENDERER_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QVariantList>

class ChartRenderer : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QVariantList dataPoints READ dataPoints WRITE setDataPoints NOTIFY dataPointsChanged)
    Q_PROPERTY(double currentRpm READ currentRpm WRITE setCurrentRpm NOTIFY currentRpmChanged)
    Q_PROPERTY(double currentFuelFlow READ currentFuelFlow WRITE setCurrentFuelFlow NOTIFY currentFuelFlowChanged)
    Q_PROPERTY(bool isEcoMode READ isEcoMode WRITE setIsEcoMode NOTIFY ecoModeChanged)
    Q_PROPERTY(double minRpm READ minRpm WRITE setMinRpm NOTIFY minRpmChanged)
    Q_PROPERTY(double maxRpm READ maxRpm WRITE setMaxRpm NOTIFY maxRpmChanged)
    Q_PROPERTY(double minFuelFlow READ minFuelFlow WRITE setMinFuelFlow NOTIFY minFuelFlowChanged)
    Q_PROPERTY(double maxFuelFlow READ maxFuelFlow WRITE setMaxFuelFlow NOTIFY maxFuelFlowChanged)

public:
    explicit ChartRenderer(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

    // Property getters
    QVariantList dataPoints() const { return m_dataPoints; }
    double currentRpm() const { return m_currentRpm; }
    double currentFuelFlow() const { return m_currentFuelFlow; }
    bool isEcoMode() const { return m_isEcoMode; }
    double minRpm() const { return m_minRpm; }
    double maxRpm() const { return m_maxRpm; }
    double minFuelFlow() const { return m_minFuelFlow; }
    double maxFuelFlow() const { return m_maxFuelFlow; }

    // Property setters
    void setDataPoints(const QVariantList &dataPoints);
    void setCurrentRpm(double rpm);
    void setCurrentFuelFlow(double fuelFlow);
    void setIsEcoMode(bool isEco);
    void setMinRpm(double minRpm);
    void setMaxRpm(double maxRpm);
    void setMinFuelFlow(double minFuelFlow);
    void setMaxFuelFlow(double maxFuelFlow);

signals:
    void dataPointsChanged();
    void currentRpmChanged();
    void currentFuelFlowChanged();
    void ecoModeChanged();
    void minRpmChanged();
    void maxRpmChanged();
    void minFuelFlowChanged();
    void maxFuelFlowChanged();

private:
    void drawGrid(QPainter *painter, const QRectF &chartRect);
    void drawAxes(QPainter *painter, const QRectF &chartRect);
    void drawData(QPainter *painter, const QRectF &chartRect);
    void drawCurrentPoint(QPainter *painter, const QRectF &chartRect);
    void drawMedianLine(QPainter *painter, const QRectF &chartRect);
    void drawLegend(QPainter *painter, const QRectF &chartRect);
    
    QPointF mapToChart(double rpm, double fuelFlow, const QRectF &chartRect) const;
    
    QVariantList m_dataPoints;
    double m_currentRpm;
    double m_currentFuelFlow;
    bool m_isEcoMode;
    double m_minRpm;
    double m_maxRpm;
    double m_minFuelFlow;
    double m_maxFuelFlow;
    
    // Chart styling
    static constexpr int MARGIN = 60;
    static constexpr int LEGEND_HEIGHT = 80;
};

#endif // CHARTRENDERER_H
