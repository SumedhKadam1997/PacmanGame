import QtQuick

Item {
    id: itmFloor

    implicitHeight: 20
    implicitWidth: 20

    Image {
        id: imgFloor

        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "qrc:/pacman/assets/Env/Floor.png"
    }
}
