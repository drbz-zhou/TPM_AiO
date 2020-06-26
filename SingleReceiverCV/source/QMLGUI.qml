import QtQuick 2.0

import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    id: window
    width: 1920
    height: 1080
    title: qsTr("Visualizer")
    visibility: Qt.Window

    signal viewClicked(string first)
    signal setDemoMenuState(int state)

    Image {
        id: matrix_1;
        objectName: "matrix_1"
        source: "image://matrix_provider_1/id"
        width: window.width*0.3//height/2
        height: window.width*0.38
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 50
        anchors.bottomMargin: 50
        anchors.leftMargin: 50
        anchors.topMargin: 50

        visible: true

        cache: false;
        asynchronous : false
        opacity: 0.8

        function updateGrid(){
            matrix_1.source = ""; // this line clears image cache so that new image is loaded
            matrix_1.source = "image://matrix_provider_1/id";
        }
    }
    Canvas{
        id: canvas
        anchors.fill: matrix_1;
        objectName: "canvas"
        width: matrix_1.width
        height: matrix_1.height
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        opacity: 0.7
        visible: true

        antialiasing: true


        property real minCircleRadius: 20
        property real maxCircleRadius: 50
        property real minForce: 0.01;   //20            // defines which force corresponds to minCircleRadius

        property color circleColor: "orange"

        property variant circles: [10,30, 0.2];

        function drawCircles(circleData){
            circles = circleData;
            console.debug("canvas ")
            canvas.requestPaint();
        }


        onPaint: {
            var ctx = getContext("2d");
            ctx.save();
            console.debug("repaint")
            ctx.clearRect ( 0 , 0 , canvas.width, canvas.height );

            // draw colored circle
            // size should be between 0 and 1.0
            function drawCircle(x,y,size) {
                ctx.beginPath();
                ctx.strokeStyle =  '#f4f442';// Qt.lighter("orange", 1 + size)
                var r = size;// minCircleRadius + size*(maxCircleRadius-minCircleRadius)
                ctx.arc(x, y, r, 0, Math.PI*2, true);
                ctx.lineWidth = 5;
                ctx.closePath();
                ctx.stroke();
                console.debug("canvas draw circle " + x +","+ y+"," + r + "," + canvas.width + "," + ctx.lineWidth )
            }
            //console.debug(circles.length);
            if(circles.length>2){
                for(var i = 0; i < circles.length; i = i + 3){
                    //if(circles[i+2] > noiseFloor){
                    var x = circles[i]*canvas.width;
                    var y = circles[i+1]*canvas.height;
                    var r = circles[i+2]*canvas.width; //(circles[i+2]-noiseFloor)/minForce;
                    //console.debug(i/3 + " " + x + " " + y + " " + r);
                    drawCircle(x,y,r);
                    //}
                }

            }

            ctx.restore();
            //console.debug("repaint")
        }

    }


    Text{
        id: label_1
        text: "bottom"
        font.pointSize: 20
        anchors.top: matrix_1.bottom
        anchors.left: parent.left
        color: Qt.lighter(primaryColor, 5)
    }
    function updateLabel_1(info){
        label_1.text = info;
    }

    signal qmlSignal(string msg)
    Item {
        id: item_1
        width: 300
        height: 300
        anchors.top: label_1.bottom
        anchors.left: parent.left


        MouseArea {
            anchors.fill: parent
            onClicked: {

                console.debug("qmlSignal 1")
                window.qmlSignal("Hello from QML")
                console.debug("qmlSignal 2")
            }

        }
    }

    property real noiseFloor: 0.005;


    Image {
        id: plot_1;
        objectName: "plot_1"
        source: "img_beach.jpg"
        width: window.width*0.61
        //height: window.height
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.left: matrix_1.right
        anchors.bottom: parent.bottom

        anchors.rightMargin: 50
        anchors.bottomMargin: 50
        anchors.leftMargin: 50
        anchors.topMargin: 50
        cache: false;
        asynchronous : false
        opacity: 1
        function updatePlot(){
            plot_1.source = ""; // this line clears image cache so that new image is loaded
            plot_1.source = "image://plot_Provider_1/id";
        }
    }



}

