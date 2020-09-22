import QtQuick 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "../Constants"

TextEdit {
    property string text_value
    property bool privacy: false

    font.family: Style.font_family
    font.pixelSize: Style.textSize
    text: privacy && General.privacy_mode ? General.privacy_text : text_value
    wrapMode: Text.WordWrap
    selectByMouse: true
    readOnly: true

    color: Style.colorText
    Behavior on color { ColorAnimation { duration: Style.animationDuration } }

    onLinkActivated: Qt.openUrlExternally(link)

    DefaultMouseArea {
        anchors.fill: parent
        cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
        acceptedButtons: Qt.NoButton
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
