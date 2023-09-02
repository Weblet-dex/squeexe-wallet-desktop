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

    function loadWebOne(){
        let web_one_html = `
        <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=device-width, initial-scale=1.0">
          <title>Dashboard Example</title>
          <script src="https://cdnjs.cloudflare.com/ajax/libs/gsap/3.9.1/gsap.min.js"></script>
          <script src="https://cdn.jsdelivr.net/npm/chart.js@3.0.0/dist/chart.min.js"></script>
          <script src="https://cdn.jsdelivr.net/npm/chartjs-plugin-datalabels@2"></script>
          <style>



            @font-face {
                font-family: 'dinregular';
                src: url('qrc:///atomic_defi_design/Dex/Squeexe/din-webfont.woff2') format('woff2'),
                     url('qrc:///atomic_defi_design/Dex/Squeexe/din-webfont.woff') format('woff');
                font-weight: normal;
                font-style: normal;

            }

            @font-face {
                font-family: 'ds-digitalnormal';
                src: url('ds-digi-webfont.woff2') format('woff2'),
                     url('ds-digi-webfont.woff') format('woff');
                font-weight: normal;
                font-style: normal;

            }

            @font-face {
                font-family: 'nebularegular';
                src: url('nebula-regular-webfont.woff2') format('woff2'),
                     url('nebula-regular-webfont.woff') format('woff');
                font-weight: normal;
                font-style: normal;
            }


            .smallNumber {
              font-family: 'ds-digitalnormal';
              font-size: 1vh;
              color: white;
              white-space: nowrap;
            }
            .mediumNumber {
              font-family: 'ds-digitalnormal';
              font-size: 2vh;
              color: white;
              white-space: nowrap;
            }
            .bigNumber {
              font-family: 'ds-digitalnormal';
              font-size: 3.6vh;
              color: white;
              white-space: nowrap;
            }
            .xbigNumber {
              font-family: 'ds-digitalnormal';
              font-size: 4.5vh;
              color: white;
              white-space: nowrap;
            }
            .titleFont {
              font-family: 'dinregular';
              font-size: 3vh;
              white-space: nowrap;
            }
            .subTitleFont {
              font-family: 'nebularegular';
              font-size: 3.3vh;
              max-height: 3.3vh;
              white-space: nowrap;
            }

            body {
              margin: 0;
              padding: 0;
              background-color: black;
              color: white;
              font-family: 'dinregular';
              font-size: 1vw;
              min-width: 1240px;
              min-height: 630px;
            }
            #dashboard {
              display: flex;
              height: 65vh;
              margin-top: 5vh;
              padding: 1vh;
            }
            #releases {
              width: 48.5%;/*
              height: 100%;*/
              padding: 10px;
              border-radius: 10px;
              border: 1px solid #ff6700;
              box-shadow: 0px 0px 8px 0px #ff6700;
            }
            #mainPriceChart {
              width: 48.5%;/*
              height: 100%;*/
              padding: 10px;
              border-radius: 10px;
              border: 1px solid #ff6700;
              margin-left: 0.5vw;
              box-shadow: 0px 0px 8px 0px #ff6700;
            }

            .release-item,
            .price-item,
            .batch-item {
             /* width: 33.33%;
              height: 100%;*/
              padding: 10px;
              border-radius: 10px;
              border: 1px solid #ff6700;
            }
            canvas {
              display: block;
              width: 100%;
              height: 80%;
              margin: 0 auto;
            }
            .reserve-title {
              font-size: 3.6vh;
              margin-bottom: 8vh;
              margin-top: -6.3vh;
            }
            #release-total {
              position: absolute;
              z-index: 2;
              margin-top: -6vh;
              width: 31%;
              text-align: center;
            }
            .release-info {
              top:4vh;
              position: relative;
            }
            .release-info-title {
              margin-top: -4.5vh;
            }
            .release-content, .batch-content {
              /*color: #ffce56;*/
              margin-bottom: 10px;
            }
            .release-bar-container {
              position: relative;
              display: flex;
              align-content: flex-end;
              height: 20vh;
              /*width: 9vh;*/
              flex-direction: column;
              align-items: flex-end;
            }
            .release-bar {
              position: absolute;
            }
            .release-item {
              display: flex;
              /*background: rgba(255, 99, 132, 0.2);*/
              border: 2px solid rgba(255, 99, 132, 1);
              margin-left: 0.5vw;
              box-shadow: 0px 0px 4px 0px rgba(255, 99, 132, 1);
            }
            .release-item-left {
              width: 80%;
              text-align: left;
            }
            .release-item-right {
              width: 20%;
              text-align: right;
            }

            #dashboardBottom {
              margin-top: 3vh;
              width: 98%;
              height: 22vh;/**/
              position: relative;
              padding-top: 1vw;
              padding-left: 1vw;
              padding-right: 1vw;
            }
            #batches {
              width: 100%;
              height: 100%;
              display: flex;/*
              padding: 10px;*/
              border-radius: 10px;
              border: 1px solid #fd4a00;
              box-shadow: 0px 0px 8px 0px #ff6700;
            }
            .batch-pie-container {
              height: 100%;
            }
            .batch-item {
              width:30%;
              display: flex;
              margin: 1vh;
              margin-right: 0;
            }
            .batch-content {
              /*color: #36a2eb;*/
              margin: 0.35vh;
            }
            .batch-title {
              text-align: center;
              font-size: 2.7vh;
              margin-top: -0.5vh;
            }
            .batch-content-left {
              width: 40%;
            }
            .batch-content-right {
              width: 60%;
              text-align: right;
            }
            .batch-item-label {
              text-align: left;
              width: 47%;
              font-size: 1.8vh;
              font-weight: bold;
              display: inline-table;
            }
            .batch-item-label-right {
              width: 50%;
              display: inline-table;
              font-size: 2.5vh;
            }
            .buyButton {
              width: -webkit-fill-available;
              right: 20%;
              margin-top: 0.5vh;
              border-radius: 8px;
              height: 2.7vh;
              border: 1px solid #009921;
              background: #10ff002b;
              color: white;
              letter-spacing: 1px;
            }
            .release-info-container {
              width: 100%;
              text-align: center;
              color: #36a2eb;
              display: inline-flex;
            }
            .release-info-nav {
              position: absolute;
              margin-top: -4vh;
              font-size: 3vh;
              font-family: 'dinregular';
              width: -webkit-fill-available;
              text-align: right;
            }
            .release-info-container-left {
              width: 50%;
            }
            .release-info-container-right {
              width: 48%;
              margin-top: 6.5vh;
            }
            .release-info-container-left-label {
              width: 100%;
              font-size: 2.3vh;
              margin-top: 2vh;
              margin-bottom: 0.5vh;
              color: rgba(255, 99, 132, 1);
            }
            .release-info-container-right-label, .release-info-container-right-data {
              width: 44%;
              display: inline-flex;
            }
            .release-info-container-right-label {
              font-size: 2.5vh;
              margin-bottom: 1vh;
              max-height: 2.5vh;
              overflow: hidden;
            }
            .release-info-container-right-data {
              flex-direction: row-reverse;
              align-items: flex-end;
            }
            .blue {
              color: #36a2eb;
            }
            .silver {
              color: #C0C0C0;
            }
            .redeemColor {
              color: #cc65fe;
            }
            .tokenColor {
              color: #ff6384;
            }
            .sectionTitle {
              font-family: 'nebularegular';
              font-size: 5vh;
              color: #ff6700;
              position: absolute;
              margin-top: -5vh;
              width: 90%;
              margin-left: 5vw;
              text-align: center;
            }
            #batch1 {
              /*background: rgba(255, 99, 132, 0.2);*/
              border: 2px solid rgba(255, 99, 132, 1);
              box-shadow: 0px 0px 4px 0px rgba(255, 99, 132, 1);
              color: rgba(255, 99, 132, 1);
            }
            #batch2 {
              /*border: rgba(64, 162, 235, 0.2);*/
              border: 2px solid rgba(64, 162, 235, 1);
              box-shadow: 0px 0px 4px 0px rgba(64, 162, 235, 1);
              color: rgba(64, 162, 235, 1);
            }
            #batch3 {
              /*background: rgba(137, 86, 254, 0.2);*/
              border: 2px solid rgba(137, 86, 254, 1);
              box-shadow: 0px 0px 4px 0px rgba(137, 86, 254, 1);
              color: rgba(137, 86, 254, 1);
            }
            .batch-buy-button {
              width: 70%;
              left: 15%;
              position: relative;
            }
          </style>
        </head>
        <body onload="init()" id='bodyID'>
          <div id="dashboard">
            <div class="sectionTitle">DASHBOARD</div>
            <div id="releases">
                <div class="titleFont reserve-title"><span class="blue">Silver ></span> Reserve 1: Zingo</div>
                <div id="release-total" class="titleFont">Reserve Total: <span class="bigNumber">1,200,000,000 G</span></div>
                <div class="release-pie-container" style="position: relative; height:30vh; width:45vw">
                    <canvas class="release-pie" id="reservePie" width="300" height="300"></canvas>
                </div>
                <div class="release-info" id="">
                  <div class="release-info-nav"><span class="arrowLeft"><</span><span class="arrowRight">></span></div>
                  <div class="release-item">
                      <div class="release-item-left">
                          <div class="release-info-title subTitleFont">Release 1: R47</div>
                          <div class="release-info-container">
                              <div class="release-info-container-left">
                                <div class="release-info-container-left-label">
                                  Size of Release
                                </div>
                                <div class="release-info-container-left-data xbigNumber">
                                  200,000,000 G
                                </div>
                                <div class="release-info-container-left-label">
                                  Total Minted
                                </div>
                                <div class="release-info-container-left-data xbigNumber">
                                  100,000,000 G
                                </div>
                              </div>
                              <div class="release-info-container-right">
                                <span class="release-info-container-right-label tokenColor">R47 Spot:</span>
                                <span class='bigNumber release-info-container-right-data tokenColor'>$0.025</span>

                                <span class="release-info-container-right-label redeemColor">Redeem At:</span>
                                <span class='bigNumber release-info-container-right-data redeemColor'>$47</span>

                                <span class="release-info-container-right-label silver">Silver Spot:</span>
                                <span class='bigNumber release-info-container-right-data silver'>$39</span>
                              </div>
                          </div>
                      </div>
                      <div class="release-item-right">
                        <div class="release-bar-container">
                            <canvas class="release-bar" width="150" height="150"></canvas>
                        </div>
                      </div>
                  </div>
                </div>
            </div>
            <div id="mainPriceChart">
              <div class="price-chart">
                <div class="price-title titleFont">Price Comparison Chart</div>
                <div class="price-line-container" style="position: relative; height:56vh; width:100%">
                    <canvas class="price-line" width="400" height="200"></canvas>
                </div>
              </div>
            </div>
          </div>
          <div id="dashboardBottom">
            <div id="batches">
              <div class="sectionTitle silver">BATCHES</div>
              <div class="batch-item" id="batch1">
                <div class="batch-content-left">
                  <div class="batch-pie-container">
                    <canvas class="batch-pie" width="100" height="100"></canvas>
                  </div>
                </div>
                <div class="batch-content-right">
                  <div class="batch-title subTitleFont">Batch 1 - R47</div>
                  <div class="batch-content"><span class="batch-item-label">Minted:</span> <span class='mediumNumber batch-item-label-right'>2,000,000</span></div>
                  <div class="batch-content"><span class="batch-item-label">Sold:</span> <span class='mediumNumber batch-item-label-right'>1,400,000</span></div>
                  <div class="batch-content"><span class="batch-item-label">Sale Price:</span> <span class='mediumNumber batch-item-label-right'>$0.036</span></div>
                  <div class="batch-content"><span class="batch-item-label redeemLabel">Redeem At:</span> <span class='mediumNumber batch-item-label-right'>$47</span></div>
                  <div class="batch-buy-button subTitleFont"><button class="buyButton" title="buy">BUY</button></div>
                </div>
              </div>
              <div class="batch-item" id="batch2">
                <div class="batch-content-left">
                  <div class="batch-pie-container">
                    <canvas class="batch-pie" width="100" height="100"></canvas>
                  </div>
                </div>
                <div class="batch-content-right">
                  <div class="batch-title subTitleFont">Batch 2 - R80</div>
                  <div class="batch-content"><span class="batch-item-label">Minted:</span> <span class='mediumNumber batch-item-label-right'>2,000,000</span></div>
                  <div class="batch-content"><span class="batch-item-label">Sold:</span> <span class='mediumNumber batch-item-label-right'>1,400,000</span></div>
                  <div class="batch-content"><span class="batch-item-label">Sale Price:</span> <span class='mediumNumber batch-item-label-right'>$0.02</span></div>
                  <div class="batch-content"><span class="batch-item-label redeemLabel">Redeem At:</span> <span class='mediumNumber batch-item-label-right'>$80</span></div>
                  <div class="batch-buy-button subTitleFont"><button class="buyButton" title="buy">BUY</button></div>
                </div>
              </div>
              <div class="batch-item" id="batch3">
                <div class="batch-content-left">
                  <div class="batch-pie-container">
                    <canvas class="batch-pie" width="100" height="100"></canvas>
                  </div>
                </div>
                <div class="batch-content-right">
                  <div class="batch-title subTitleFont">Batch 3 - R100</div>
                  <div class="batch-content"><span class="batch-item-label">Minted:</span> <span class='mediumNumber batch-item-label-right'>2,000,000</span></div>
                  <div class="batch-content"><span class="batch-item-label">Sold:</span> <span class='mediumNumber batch-item-label-right'>900,000</span></div>
                  <div class="batch-content"><span class="batch-item-label">Sale Price:</span> <span class='mediumNumber batch-item-label-right'>0.011c</span></div>
                  <div class="batch-content"><span class="batch-item-label redeemLabel">Redeem At:</span> <span class='mediumNumber batch-item-label-right'>$100</span></div>
                  <div class="batch-buy-button subTitleFont"><button class="buyButton" title="buy">BUY</button></div>
                </div>
              </div>
            </div>
          </div>

          <script>
            // Sample data for the pie charts and line chart
            const pieChartData = {
              labels: ['Release1: R47', 'Release2: R80', 'Release3: R100', 'Not Tokenised'],
              datasets: [{
                data: [30, 25, 15, 30],
                backgroundColor: ['#ff6384', '#36a2eb', '#8956ff', '#333333'],
                borderWidth: 0,
              }]
            };

            const lineChartData = {
              labels: ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun'],
              datasets: [
                {
                  label: 'R100 Spot',
                  data: [7, 10, 8, 16, 15, 20],
                  borderColor: '#8956ff',
                  fill: false,
                },
                {
                  label: 'R80 Spot',
                  data: [8, 12, 10, 20, 18, 25],
                  borderColor: '#ff6384',
                  fill: false,
                },
                {
                  label: 'R47 Spot',
                  data: [12.5, 16, 24, 20, 30, 35],
                  borderColor: '#36a2eb',
                  fill: false,
                },
                {
                  label: 'Silver Spot',
                  data: [25, 30, 25, 27, 35, 39],
                  borderColor: '#C0C0C0',
                  fill: false,
                },
                {
                  label: 'Redemption1-$47',
                  data: [47,47,47,47,47,47],
                  borderColor: '#36a2eb',
                  fill: false,
                  borderWidth:1,
                  spanGaps: true,
                },{
                  label: 'Redemption2-$80',
                  data: [80,80,80,80,80,80],
                  borderColor: '#ff6384',
                  fill: false,
                  borderWidth:1,
                  spanGaps: true,
                },{
                  label: 'Redemption3-$100',
                  data: [100,100,100,100,100,100],
                  borderColor: '#8956ff',
                  fill: false,
                  borderWidth:1,
                  spanGaps: true,
                },
              ],
            };

            function init(){
              // GSAP
              gsap.set('#reservePie', { width:window.innerWidth * 0.45 })
              gsap.from('#bodyID', { duration: 1, scale: 1, opacity: 0, delay:0.1 });

              // Create the pie chart using Chart.js
              //Chart.register(ChartDataLabels);
              const releasePie = new Chart(document.querySelector('.release-pie'), {
                type: 'pie',
                data: pieChartData,
                plugins: [ChartDataLabels],
                options: {
                  responsive: true,
                  maintainAspectRatio: false,
                  plugins: {
                      datalabels: {
                        color: 'black', // Label text color
                        font: {
                          weight: 'bold',
                          size: window.innerWidth * .012,
                        },
                        formatter: (value, context) => { // Customize label text (optional)
                          return value + '%';
                        }
                      },
                      legend: {
                          display: true,
                          position: 'right',
                          title: {
                            display: true,
                            font: {
                              size: window.innerWidth * .02,
                              family: 'nebularegular',
                            },
                            color: '#fff',
                            text: 'RELEASES', // Custom legend title text
                            padding: { top: -10, bottom: 5 } // Optional padding
                          },
                          labels: {
                              color: '#36a2eb',
                              font: {
                                size: window.innerWidth * .015
                              }
                          }
                          //boxHeight:
                      },
                  }
                }
              });

              // Create the bar chart using Chart.js
              const releaseBar = new Chart(document.querySelector('.release-bar'), {
                type: 'bar',
                data: {
                  labels: ['R47 Spot Price','Silver Price','Redemption Price'],
                  datasets: [{
                    label: 'Price',
                    data: [35, 39, 47],
                    backgroundColor: ['#ff6384', '#C0C0C0', '#cc65fe'],
                    barPercentage: 1, // Remove gap between bars
                    categoryPercentage: 1, // Remove gap between bars
                  }]
                },
                plugins: [ChartDataLabels],
                options: {
                  responsive: true,
                  maintainAspectRatio: false,
                  scales: {
                    y: {
                      beginAtZero: true,
                      display: false
                    },
                    x: {
                      display: false, // Hide the x-axis
                    }
                  },
                  plugins: {
                      legend: {
                          display: false
                      },
                      datalabels: {
                        color: 'black', // Label text color
                        font: {
                          weight: 'bold',
                          size: 14,
                        },
                        formatter: (value, context) => { // Customize label text (optional)
                          return '$' + value;
                        }
                      },
                  }
                }
              });

              // Create the line chart using Chart.js
              const mainPriceLine = new Chart(document.querySelector('.price-line'), {
                type: 'line',
                data: lineChartData,
                options: {
                  responsive: true,
                  maintainAspectRatio: false,
                  scales: {
                    x: {
                      display: false, // Hide the x-axis
                    },
                    y: {
                      ticks: {
                        min: 0,
                        max: 100,
                        stepSize: 10,
                      },
                      //display: false,
                      position: 'right'
                    }
                  },
                  plugins: {
                      legend: {
                          display: true,
                          position: 'bottom',
                          labels: {
                              color: '#ffffff',
                              font: {
                                size: window.innerWidth * .01
                              }
                          }
                      }
                  }
                }
              });

              // Create the pie charts in the batch
              const batchPies = document.querySelectorAll('.batch-pie');
              const batchColors = ['#ff6384','#40a2eb','#8956fe'];
              let batchID = 0;
              batchPies.forEach((batchPie) => {
                new Chart(batchPie, {
                  type: 'pie',
                  data: {
                    labels: ['Sold','Unsold'],
                    datasets: [{
                      data: [70,30],
                      backgroundColor: [batchColors[batchID],'#333333'],
                      borderWidth: 0,
                    }]
                  },
                  plugins: [ChartDataLabels],
                  options: {
                    responsive: true,
                    maintainAspectRatio: false,
                    plugins: {
                      legend: {
                          display: false,
                          position: 'bottom',
                          /*labels: {
                              color: 'rgb(255, 99, 132)'
                          }*/
                      },
                      datalabels: {
                        color: 'white', // Label text color
                        font: {
                          weight: 'bold',
                          size: 14,
                        },
                        formatter: (value, context) => { // Customize label text (optional)
                          return value + '%';
                        }
                      },
                    }
                  }
                });
                batchID = batchID + 1;
              });
            }
          </script>
        </body>
        `
        dashboard.fzWebOne.enabled = true;
        dashboard.fzWebOne.loadHtml(web_one_html);
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

//    Component.onCompleted:
//    {
//        try
//        {
//            loadWebOne()
//        }
//        catch (e) { console.error(e) }
//    }

//    onWidthChanged: {
//        try
//        {
//            loadWebOne()
//        }
//        catch (e) { console.error(e) }
//    }
}

//    FzChart{
//        id: fzchart
//        x: parent.width * 0.52
//        y: parent.height * 0.136
//        width: parent.width * 0.44
//        height: parent.height * 0.5
//        //anchors.centerIn: parent
//    }

//    Image {
//        id: sqx_bg
//        source: "qrc:///assets/images/dashconcept.png"
//        width: parent.width
//        height: parent.height
//        x: 0
//        y: 0
//        fillMode: Image.Stretch
//        visible: true
//    }

//    GradientButton{
//        x: 20
//        y: 0
//        radius: width
//        width: 200
//        text: qsTr("Back")
//        onClicked: dashboard.fz_page = 0;
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
