import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12


Item {
    id: root
    property string image;
    property alias commentary: comment.text

    function flip() {
        if (flipable.flipped) {
            c_ble_client.play("0");
        } else {
            c_ble_client.play(image.match("([1-9]{1,2}(0)?).jpg")[1]);
        }
        flipable.flipped = !flipable.flipped
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 50
        anchors.bottomMargin: 100
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        Flipable {
            id: flipable
            property bool flipped: false
            Layout.fillHeight: true
            Layout.fillWidth: true

            back: Image {
                id: back
                source: root.image
                anchors.centerIn: parent
                anchors.fill: parent
                anchors.margins: 20
                fillMode: Image.PreserveAspectFit
            }
            front: Image {
                source: back.paintedHeight > back.paintedWidth ? "images/back.jpg" : "images/back_90.jpg"
                anchors.centerIn: parent
                anchors.fill: parent
                anchors.margins: 20
                fillMode: Image.PreserveAspectFit
            }

            transform: Rotation {
                id: rotation
                origin.x: flipable.width/2
                origin.y: flipable.height/2
                axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
                angle: 0    // the default angle
            }

            states: State {
                name: "back"
                PropertyChanges { target: rotation; angle: 180 }
                when: flipable.flipped
            }

            transitions: Transition {
                NumberAnimation { target: rotation; property: "angle"; duration: 800 }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: root.flip()
            }
        }

        Label {
            id: comment
            Layout.fillWidth: true
            text: qsTr("Example")
            font.pixelSize: 15
            font.italic: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
