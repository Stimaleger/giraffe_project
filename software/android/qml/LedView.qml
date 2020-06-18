import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Item {
    id: root
    ColumnLayout {
        Label {
            text: qsTr("LED configuration: ")
            font.pixelSize: 18
            font.underline: true
            font.bold: true
        }
        SwipeView {
            id: view
            Layout.fillHeight: true
            currentIndex: 0
            Item {

            }
            Item {

            }
            Item {

            }
        }
    }
    PageIndicator {
        id: indicator
        count: view.count
        currentIndex: view.currentIndex
        anchors.bottom: root.bottom
        anchors.horizontalCenter: root.horizontalCenter
        interactive: false
    }
    Rectangle {
        color: "transparent"
        height: root.height
        anchors.right: root.right
        width: 50
        Label {
            text: "<b>></b>"
            font.pixelSize: 20
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: view.currentIndex++
        }
        visible: view.currentIndex < view.count - 1
    }
    Rectangle {
        color: "transparent"
        height: root.height
        anchors.left: root.left
        width: 50

        Label {
            text: "<"
            font.bold: true
            font.pixelSize: 20
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: view.currentIndex--
        }
        visible: view.currentIndex != 0
    }
}
