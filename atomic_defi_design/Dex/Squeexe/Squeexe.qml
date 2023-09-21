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
    id: squeexe
    anchors.fill: parent
    //property var silvrep : "empty"
    //property string silvrstr : "empty"

    Shortcut{
        sequence: "F7"
        onActivated: {
            var tmpAg = Number(agWebObj.agCurrent) + 1;
            agWebObj.agCurrent = JSON.stringify(tmpAg);
            agWebObj.setAgPrice(agWebObj.agCurrent);
        }
    }

//    Shortcut{
//        sequence: "F8"
//        onActivated: {
//            var fiat_html = `
//            <!DOCTYPE html>
//            <html>
//            <body>
//              <iframe
//                style="border-radius: 4px; border: 1px solid #58585f; margin: auto;max-width: 420px"
//                src="https://buy.onramper.com"
//                height="630px"
//                width="420px"
//                title="Onramper widget"
//                allow="accelerometer; autoplay; camera; gyroscope; payment">
//              </iframe>
//            </body>
//            </html>`
//            dashboard.onRamper.loadHtml(fiat_html);
//            //API.app.trading_pg.upt_ag_price()
//            //sqx_labl.text = silvrep
//        }
//    }

    function updTxt(nwTxt){
        sqx_labl.text = "" + nwTxt;
    }

    Item{
        id: agdboard
        anchors.fill: parent
        visible: dashboard.ag_page == 0 ? true : false;
        enabled: visible

//         GradientButton{
//             y: 20
//             height: 60
//             width: 300
//             anchors.horizontalCenter: parent.horizontalCenter
//             radius: width
//             text: qsTr("Monitor")
//             onClicked: dashboard.ag_page = 0;
//         }

//         DexGradientAppButton{
//             y: 100
//             height: 60
//             width: 300
//             anchors.horizontalCenter: parent.horizontalCenter
//             iconSource: Qaterial.Icons.plus
//             radius: 15
//             padding: 25
//             font: DexTypo.body2
//             text: qsTr("Monitor")
//             onClicked: dashboard.ag_page = 0;
//         }

//         DefaultButton{
//             y: 180
//             height: 60
//             width: 300
//             anchors.horizontalCenter: parent.horizontalCenter
//             radius: 18
//             label.text: qsTr("Monitor")
//             label.font.pixelSize: 16
//             content.anchors.centerIn: content.parent
//             content.anchors.leftMargin: enabled ? 23 : 48
//             content.anchors.rightMargin: 23
//             onClicked: dashboard.ag_page = 0;
//         }

//         DexAppOutlineButton{
//             y: 260
//             height: 60
//             width: 300
//             anchors.horizontalCenter: parent.horizontalCenter
//             text: qsTr("Monitor")
//             leftPadding: 40
//             rightPadding: 40
//             radius: 18
//             onClicked: {
//                 agWebObj.agCurrent++;
//                 agWebObj.setAgPrice(agWebObj.agCurrent);
//             }
//        }
    }

//    Monitor{
//        id: monitr
//        anchors.fill: parent
//        visible: dashboard.ag_page == 1 ? true : false;
//        enabled: visible
//    }

//    Label{
//        id: sqx_labl
//        anchors.horizontalCenter: parent.horizontalCenter
//        y: 360
//        font.pixelSize: 22
//        //text: API.app.trading_pg.ag_price
//        text: API.app.trading_pg.ag_price
//        color: "#FFFFFF"
//    }
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
