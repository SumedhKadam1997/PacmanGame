import QtQuick

Item {
    id: itmPacman

    property bool isDead: false
    property alias rotationAngle: imgPacman.rotation
    property bool running: false

    function animatePacman() {
        timPacman.start();
    }

    function inanimatePacman() {
        timPacman.stop();
    }

    implicitHeight: 20
    implicitWidth: 20

    Behavior on x  {
        NumberAnimation {
            duration: 200
        }
    }
    Behavior on y  {
        NumberAnimation {
            duration: 200
        }
    }

    Component.onDestruction: {
        timPacman.stop();
    }

    Timer {
        id: timPacman

        interval: 80
        repeat: true

        onTriggered: {
            itmPacman.running = !itmPacman.running;
        }
    }

    Image {
        id: imgPacman

        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: itmPacman.isDead ? "qrc:/pacman/assets/Pacman/Dead.png" : itmPacman.running ? "qrc:/pacman/assets/Pacman/Closed.png" : "qrc:/pacman/assets/Pacman/Open.png"
    }
}
