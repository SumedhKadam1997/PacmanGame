import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: popPauseOverlay

    closePolicy: Popup.NoAutoClose

    background: Rectangle {
        color: "#A6000000"
    }

    Rectangle {
        id: rectPauseOverlay

        anchors.centerIn: parent
        color: "#050505"
        height: 240
        width: 180

        ColumnLayout {
            spacing: 0

            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 50
            }

            Item {
                id: itmResume

                height: 24
                width: 75

                Text {
                    anchors.fill: parent
                    color: "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    text: qsTr("Resume")
                    verticalAlignment: Text.AlignVCenter

                    font {
                        family: "bradley hand itc"
                        pixelSize: 14
                        weight: Font.Bold
                    }
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        gameController.play();
                    }
                }
            }

            Rectangle {
                height: 1
                width: 75
            }

            Item {
                id: itmRestart

                height: 24
                width: 75

                Text {
                    anchors.fill: parent
                    color: "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    text: qsTr("Restart")
                    verticalAlignment: Text.AlignVCenter

                    font {
                        family: "bradley hand itc"
                        pixelSize: 14
                        weight: Font.Bold
                    }
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        gameController.restart();
                    }
                }
            }

            Rectangle {
                height: 1
                width: 75
            }

            Item {
                id: itmQuit

                height: 24
                width: 75

                Text {
                    anchors.fill: parent
                    color: "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    text: qsTr("Quit")
                    verticalAlignment: Text.AlignVCenter

                    font {
                        family: "bradley hand itc"
                        pixelSize: 14
                        weight: Font.Bold
                    }
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        Qt.quit();
                    }
                }
            }
        }
    }
}
