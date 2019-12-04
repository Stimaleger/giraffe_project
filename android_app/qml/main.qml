import QtQuick 2.8
import QtQuick.Controls 2.12
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0


ApplicationWindow {
    id: root
    title: qsTr("El secret project")
    width: 500; height: 700
    visible: true
    background: Image { z:-1; source: "images/background.png"; opacity: 0.4 }

    Label {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        text: "<b>Giraffe Control</b>"
        font.pixelSize: 50
        opacity: .8
    }

    ToolButton {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 20
        height: title.height
        width: height
        Image {
            anchors.fill: parent
            source: "images/settings.svg"
            fillMode: Image.PreserveAspectFit
            mipmap: true
            opacity: .8
        }
    }

    SwipeView {
        id: swip_view
        anchors {
            top: title.bottom
            right: parent.right
            left: parent.left
            bottom: parent.bottom
            margins: 40
        }
        interactive: false
        Item {
            AnimatedImage {
                id: gif_giraffe
                property int nb_cyle: 0

                source: "images/girafe.gif"
                playing: false
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 20
                width: 550
                mipmap: true
                onCurrentFrameChanged: {
                    if (currentFrame == 0)
                        nb_cyle++;
                    if (nb_cyle == 4 && currentFrame == 0) {
                        gif_giraffe.playing = false;
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        gif_giraffe.nb_cyle = 0
                        gif_giraffe.playing = true;
                        bubble.visible = true
                    }
                }
            }
            Image {
                id: bubble
                source: "images/bubble.svg"
                visible: false
                anchors.left: gif_giraffe.right
                anchors.top: gif_giraffe.top
                anchors.topMargin: 120
                anchors.leftMargin: -100
                anchors.right: parent.right
                mipmap: true
                Label {
                    anchors.centerIn: bubble
                    text: qsTr("Coucou Clem \u2764")
                    font.pixelSize: 20
                }
            }
        }
        Item {

        }
        Item {

        }
    }
}
