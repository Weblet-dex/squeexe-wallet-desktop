import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

import Qaterial 1.0 as Qaterial

import "../Components"
import "../Constants"
import App 1.0
import Dex.Themes 1.0 as Dex

Item {
    id: monitor
    visible: dashboard.fz_page == 1 ? true : false;
    enabled: visible

    FzChart{
        id: fzchart
        x: parent.width * 0.526
        y: parent.height * 0.14
        width: parent.width * 0.426
        height: parent.height * 0.492
        //anchors.centerIn: parent
    }

    Image {
        id: sqx_bg
        source: "qrc:///assets/images/dashconcept.png"
        width: parent.width
        height: parent.height
        x: 0
        y: 0
        fillMode: Image.Stretch
        visible: true
    }

    GradientButton{
        x: 20
        y: 0
        radius: width
        width: 200
        text: qsTr("Back")
        onClicked: dashboard.fz_page = 0;
    }

    SquareButton{
        x: 20
        y: 48
        width: 48
        height: 48
        icon.source: Qaterial.Icons.chevronLeft
        Layout.alignment: Qt.AlignVCenter
        onClicked: dashboard.fz_page = 0;
    }

//    DexRectangle{
//        id: rect_one
//        enabled: true
//        visible: true
//        width: 490
//        height: 500
//        x: (parent.width * 0.25) - (width / 2)
//        y: 40
//        gradient: Gradient
//        {
//            orientation: Gradient.Vertical
//            GradientStop { position: 0.001; color: Dex.CurrentTheme.innerBackgroundColor }
//            GradientStop { position: 1; color: Dex.CurrentTheme.backgroundColor }
//        }
//        DexButton{
//            enabled: true
//            width: 240
//            height: 60
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.bottom: parent.bottom
//            anchors.bottomMargin: 30
//            font: Qt.font({
//                pixelSize: 28,
//                letterSpacing: 0.25,
//                family: "Ubuntu",
//                weight: Font.Medium
//            })
//            border.color: enabled ? Dex.CurrentTheme.accentColor : DexTheme.contentColorTopBold
//            opacity: 1
//            text: "test"
//            //onClicked: openChallenge()
//        }
//    }
}