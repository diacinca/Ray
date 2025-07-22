import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import BoatPerformanceChart 1.0

ApplicationWindow {
    id: window
    width: 1200
    height: 800
    visible: true
    title: qsTr("Boat Performance Chart - RPM vs Fuel Flow")
    color: "#f0f0f0"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        // Title
        Text {
            Layout.fillWidth: true
            text: "Engine Performance Monitor"
            font.pixelSize: 24
            font.bold: true
            color: "#2c3e50"
            horizontalAlignment: Text.AlignHCenter
        }

        // Chart container
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"
            border.color: "#bdc3c7"
            border.width: 2
            radius: 8

            PerformanceChart {
                anchors.fill: parent
                anchors.margins: 10
            }
        }

        // Controls
        RowLayout {
            Layout.fillWidth: true
            spacing: 20

            // RPM Control
            GroupBox {
                title: "Engine RPM"
                Layout.preferredWidth: 300

                ColumnLayout {
                    anchors.fill: parent

                    Slider {
                        id: rpmSlider
                        Layout.fillWidth: true
                        from: 0
                        to: 6000
                        value: 1500
                        stepSize: 50

                        onValueChanged: {
                            chartDataModel.currentRpm = value
                        }
                    }

                    Text {
                        text: "RPM: " + Math.round(rpmSlider.value)
                        font.pixelSize: 16
                        font.bold: true
                    }
                }
            }

            // Status Display
            GroupBox {
                title: "Current Status"
                Layout.fillWidth: true

                GridLayout {
                    anchors.fill: parent
                    columns: 2
                    rowSpacing: 10
                    columnSpacing: 20

                    Text {
                        text: "Fuel Flow:"
                        font.pixelSize: 14
                    }
                    Text {
                        text: chartDataModel.currentFuelFlow.toFixed(1) + " L/h"
                        font.pixelSize: 14
                        font.bold: true
                        color: chartDataModel.isEcoMode ? "#27ae60" : "#f39c12"
                    }

                    Text {
                        text: "Mode:"
                        font.pixelSize: 14
                    }
                    Text {
                        text: chartDataModel.isEcoMode ? "ECO" : "NORMAL"
                        font.pixelSize: 14
                        font.bold: true
                        color: chartDataModel.isEcoMode ? "#27ae60" : "#f39c12"
                    }

                    Text {
                        text: "Efficiency:"
                        font.pixelSize: 14
                    }
                    Text {
                        text: chartDataModel.isEcoMode ? "Above Average" : "Below Average"
                        font.pixelSize: 14
                        font.bold: true
                        color: chartDataModel.isEcoMode ? "#27ae60" : "#e74c3c"
                    }
                }
            }

            // Action Buttons
            ColumnLayout {
                Layout.preferredWidth: 200
                spacing: 10

                Button {
                    Layout.fillWidth: true
                    text: "Generate New Data"
                    onClicked: chartDataModel.generateSampleData()
                }

                Button {
                    Layout.fillWidth: true
                    text: "Reset RPM"
                    onClicked: rpmSlider.value = 1500
                }
            }
        }

        // Footer info
        Text {
            Layout.fillWidth: true
            text: "Chart shows fuel consumption patterns: Green area = efficient range, Orange/Red = higher consumption"
            font.pixelSize: 12
            color: "#7f8c8d"
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
        }
    }
}
