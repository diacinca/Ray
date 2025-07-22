import QtQuick 2.15
import BoatPerformanceChart 1.0

Item {
    id: root

    ChartRenderer {
        id: chartRenderer
        anchors.fill: parent
        
        dataPoints: chartDataModel ? chartDataModel.getDataPoints() : []
        currentRpm: chartDataModel ? chartDataModel.currentRpm : 0
        currentFuelFlow: chartDataModel ? chartDataModel.currentFuelFlow : 0
        isEcoMode: chartDataModel ? chartDataModel.isEcoMode : false
        minRpm: chartDataModel ? chartDataModel.minRpm : 0
        maxRpm: chartDataModel ? chartDataModel.maxRpm : 6000
        minFuelFlow: chartDataModel ? chartDataModel.minFuelFlow : 0
        maxFuelFlow: chartDataModel ? chartDataModel.maxFuelFlow : 50

        Connections {
            target: chartDataModel
            function onDataChanged() {
                chartRenderer.dataPoints = chartDataModel.getDataPoints()
            }
        }
    }
}
