import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Item {
    id: root
    ColumnLayout {
        anchors.fill: parent
        Label {
            text: qsTr("Mp3 configuration: ")
            font.pixelSize: 18
            font.underline: true
            font.bold: true
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTr("Volume")
                font.bold: true
                Layout.fillWidth: true
            }
            Slider {

            }
        }
    }
}
