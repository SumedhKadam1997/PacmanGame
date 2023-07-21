import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import PacmanGame 1.0
import "imports"

Window {
    id: mainWindow

    color: "#1E1E1E"
    flags: Qt.FramelessWindowHint | Qt.Window
    height: 540
    maximumHeight: 540
    maximumWidth: 380
    minimumHeight: 540
    minimumWidth: 380
    title: qsTr("Pacman Game")
    visible: true
    width: 380

    Image {
        id: imgMain

        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/pacman/assets/pacman_main.png"

        Rectangle {
            id: btnStart

            color: "#A8CD1D"
            height: 50
            radius: 10
            width: 200

            anchors {
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: 10
                verticalCenter: parent.verticalCenter
                verticalCenterOffset: 80
            }

            Text {
                id: txtStart

                anchors.fill: parent
                color: "#1A1C40"
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("START")
                verticalAlignment: Text.AlignVCenter

                font {
                    family: "bradley hand itc"
                    pixelSize: 24
                    weight: Font.Bold
                }
            }

            MouseArea {
                id: maStart

                anchors.fill: parent

                onClicked: {
                    gameLoader.sourceComponent = gameComponent;
                    gameController.play();
                }
            }
        }
    }

    Image {
        id: imgClose

        height: 20
        source: "qrc:/pacman/assets/close.png"
        width: 20

        anchors {
            right: parent.right
            rightMargin: 20
            top: parent.top
            topMargin: 20
        }

        MouseArea {
            id: maClose

            anchors.fill: parent

            onClicked: {
                Qt.quit();
            }
        }
    }

    Component {
        id: blankComponent

        Item {
        }
    }

    Component {
        id: gameComponent

        Game {
        }
    }

    GameController {
        id: gameController

    }

    Loader {
        id: gameLoader

        Keys.enabled: true
        anchors.fill: parent
        focus: true
        sourceComponent: blankComponent

        Keys.onPressed: event => {
            if (event.key === 16777220) {
                gameLoader.sourceComponent = gameComponent;
            }
        }
    }
}
