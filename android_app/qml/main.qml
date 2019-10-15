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
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        text: "<b>Giraffe Control</b>"
        font.pixelSize: 34
        opacity: .8
    }

    ToolButton {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 20
        height: 40
        width: 40
        Image {
            anchors.fill: parent
            source: "images/settings.svg"
            fillMode: Image.PreserveAspectFit
            mipmap: true
            opacity: .8
        }
    }

    Rectangle {
        id: rectangle
        anchors.bottom: parent.bottom
        anchors.margins: 20
        anchors.right: parent.right
        anchors.left: parent.left
        height: 40
        radius: 20
        color: Material.color(Material.Purple)
        opacity: .6
    }

    RowLayout {
        anchors.fill: rectangle
        anchors.rightMargin: 15
        anchors.leftMargin: 15
        ToolButton {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Image {
                anchors.fill: parent
                anchors.margins: 5
                source: "images/palette.svg"
                fillMode: Image.PreserveAspectFit
                mipmap: true
                opacity: swip_view.currentIndex === 0 ? .5 : 1
            }
            onClicked: swip_view.currentIndex = 0
        }
        ToolButton {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Click me 2"
            onClicked: swip_view.currentIndex = 1
            highlighted: swip_view.currentIndex === 1
        }
        ToolButton {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Click me 3"
            onClicked: swip_view.currentIndex = 2
            highlighted: swip_view.currentIndex === 2
        }
    }

    SwipeView {
        id: swip_view
        anchors.top: parent.top
        anchors.bottom: rectangle.top
        anchors.right: parent.right
        anchors.left: parent.left
        interactive: false
        Item {
            ColorPicker {
                z: 2
                anchors.centerIn: parent
            }
        }
        Item {

        }
        Item {

        }
    }
}
