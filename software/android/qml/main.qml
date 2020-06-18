import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0


ApplicationWindow {
    id: root
    title: qsTr("Giraffe project")
    width: 720 * .7
    height: 1240 * .7
    visible: true

    Connections {
        target: c_ble_client
        onConnected: id_popup_connexion.close()
    }

    header: ToolBar {
        id: id_toolbar
        height: root.height * .07
        RowLayout {
            anchors.fill: parent
            Label {
                Layout.leftMargin: 20
                text: qsTr("<b>Giraffe Controller</b>")
                font.pixelSize: 24
            }
        }
    }

    ConnexionPopup {
        id: id_popup_connexion
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: parent.width * .8
        height: parent.height * .3
    }

    ColumnLayout {
        id: id_swipe_view
        anchors {
            top: id_toolbar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            topMargin: 5
            leftMargin: 10
            rightMargin: 10
        }
        Mp3View {
            id: id_mp3_view
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        LedView {
            id: id_led_view
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
