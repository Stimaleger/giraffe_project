import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Popup {
    closePolicy: Popup.NoAutoClose
    ColumnLayout {
        anchors.fill: parent
        spacing: 30
        Label {
            text: qsTr("<b>Trying to connect to the giraffe...</b>")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pixelSize: 20
        }
        BusyIndicator {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
    }
}
