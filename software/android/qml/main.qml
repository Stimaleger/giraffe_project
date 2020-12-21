import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import "js/fontawesome.js" as FA


ApplicationWindow {
    id: appWindow
    visible: true
    width: 720 * .6
    height: 1240 * .6

    // Load icons
    property var icons: FA.Icons;
    FontLoader { id: id_font; source: "fonts/fontawesome-webfont.ttf" }

    Timer {
        id: wait
        interval: 4000
        running: false
        repeat: false
        onTriggered: popup_connect.close()
    }
    Connections {
        target: c_ble_client
        onConnected: wait.start()
    }

    Popup {
        id: popup_connect
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        height: 300
        width: appWindow.width * .8

        Label {
            id: id_lb
            z: 1
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Connecting . . .")
            font.bold: true
            width: parent.width
            font.pixelSize: 20
        }

        AnimatedImage {
            source: "images/girafe-floss-danse.gif"
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            anchors.fill: parent
        }
    }

    Drawer {
        id: drawer
        width: Math.min(appWindow.width, appWindow.height) / 3 * 2
        height: appWindow.height
        y: appBar.height

        // Start rotation animation on icon
        onAboutToShow: menu_bp.rotate = true
        onAboutToHide: menu_bp.rotate = false

        Rectangle {
            id: logoWtapper
            width: parent.width
            height: parent.height * 0.3
            anchors.margins: 0
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            color: "transparent"

            AnimatedImage {
                source: "images/girafe-floss-danse.gif"
                fillMode: Image.PreserveAspectFit
                height: parent.height
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 0
                playing: visible
            }
        }
    }

    header: ToolBar {
        id: appBar
        height: 56
        width: parent.width
        RowLayout {
            anchors.fill: parent
            anchors.rightMargin: 15
            anchors.leftMargin: 5
            ToolButton {
                id: menu_bp
                property bool rotate: false
                contentItem.transform: Rotation {
                    id: rotation
                    origin.x: menu_bp.contentItem.width / 2
                    origin.y: menu_bp.contentItem.height / 2
                    axis.x: 0; axis.y: 0; axis.z: 1
                    angle: 0
                }
                text: icons.fa_bars
                font.family: "FontAwesome";
                font.pixelSize: 20
                onClicked: drawer.visible ? drawer.close() : drawer.open()
                contentItem.states: State {
                   name: "rotate"
                   when: menu_bp.rotate
                   PropertyChanges {
                       target: rotation
                       angle: 90
                   }
                }
                contentItem.transitions: Transition {
                    NumberAnimation {
                        target: rotation
                        property: "angle"
                        duration: 320
                    }
                }
            }
            Label {
                text: qsTr("Giraffe controller")
                font.pixelSize: 20
                Layout.leftMargin: 15
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            Item {
                Layout.fillWidth: true
            }
            ToolButton {
                id: volume
                font.family: "FontAwesome";
                checkable: true
                font.pixelSize: 20
                enabled: c_ble_client.state_connection
                text: {
                    if (slider.value === 0)
                        icons.fa_volume_off;
                    else if (slider.value <= slider.to / 2)
                        icons.fa_volume_down;
                    else
                        icons.fa_volume_up;
                }
                Slider {
                    id: slider
                    visible: volume.checked
                    anchors.top: parent.bottom
                    anchors.horizontalCenter: volume.horizontalCenter
                    width: 120
                    from: 0
                    value: 15
                    stepSize: 1
                    to: 23
                    onValueChanged: c_ble_client.set_volume(value)
                }
            }
            ToolButton {
                id: bp_connect
                font.family: "FontAwesome";
                text: icons.fa_power_off
                Material.foreground: c_ble_client.state_connection === true ? "green" : "red";
                font.pixelSize: 20
                onClicked: {
                    if (c_ble_client.state_connection === true) {
                        id_lb.text = "Disconnecting . . ."
                        c_ble_client.disconnect();
                    } else {
                        id_lb.text = "Connecting . . ."
                        c_ble_client.connect();
                    }
                    popup_connect.open();
                }
            }
        }
    }

    SwipeView {
        id: view
        width: parent.width
        anchors.bottom: parent.bottom
        anchors.top: appBar.bottom
        anchors.bottomMargin: 20
        enabled: c_ble_client.state_connection
        Card { image: "images/perso/0001.jpg" ; commentary: "Suit up !" }
        Card { image: "images/perso/0002.jpg" ; commentary: "Nos premières vacances..." }
        Card { image: "images/perso/0003.jpg" ; commentary: "Les premières vagues..." }
        Card { image: "images/perso/0004.jpg" ; commentary: "Encore un petit tour à Oléron..." }
        Card { image: "images/perso/0005.jpg" ; commentary: "Bikeuse !" }
        Card { image: "images/perso/0006.jpg" ; commentary: "Lisboa" }
        Card { image: "images/perso/0007.jpg" ; commentary: "La blague de l'année" }
        Card { image: "images/perso/0008.jpg" ; commentary: "Learning to fly" }
        Card { image: "images/perso/0009.jpg" ; commentary: "Degemer mat e Breizh" }
        Card { image: "images/perso/0010.jpg" ; commentary: "Arigato gozaimasu" }
        Card { image: "images/perso/0011.jpg" ; commentary: "\u2665" }
    }

    PageIndicator {
        id: indicator
        count: view.count
        currentIndex: view.currentIndex
        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
