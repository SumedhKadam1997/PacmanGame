import QtQuick

Item {
    id: itmWall

    implicitHeight: 20
    implicitWidth: 20

    Image {
        id: imgWall

        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "qrc:/pacman/assets/Env/Wall.png"
    }
}
