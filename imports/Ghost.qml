import QtQuick

Item {
    id: itmGhost

    property alias eyesImgSrc: imgEyes.source
    property alias ghostImgSrc: imgGhost.source

    implicitHeight: 20
    implicitWidth: 20

    Image {
        id: imgGhost

        anchors.fill: parent
        fillMode: Image.PreserveAspectFit

        Image {
            id: imgEyes

            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
        }
    }
}
