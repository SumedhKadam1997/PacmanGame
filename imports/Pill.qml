import QtQuick

Item {
    id: itmPill

    implicitHeight: 20
    implicitWidth: 20

    Image {
        id: imgPill

        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "qrc:/pacman/assets/Env/Pill.png"
    }
}
