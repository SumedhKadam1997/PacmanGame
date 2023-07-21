import QtQuick

Item {
    id: itmPoint

    implicitHeight: 20
    implicitWidth: 20

    Image {
        id: imgPoint

        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "qrc:/pacman/assets/Env/Point.png"
    }
}
