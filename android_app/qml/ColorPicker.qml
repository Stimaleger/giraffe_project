import QtQuick 2.0
import QtQuick.Controls 1.0 as QtControls
import QtQuick.Controls.Material 2.12
import QtGraphicalEffects 1.12

Column {
    id: picker

    property color color

    property real hue
    property real saturation: 0.5
    property real lightness: 0.5

    onColorChanged: {
        var min = Math.min(color.r, Math.min(color.g, color.b))
        var max = Math.max(color.r, Math.max(color.g, color.b))
        var c = max - min
        var h

        if (c === 0) {
            h = 0
        } else if (max === color.r) {
            h = ((color.g - color.b) / c) % 6
        } else if (max === color.g) {
            h = ((color.b - color.r) / c) + 2
        } else if (max === color.b) {
            h = ((color.r - color.g) / c) + 4
        }
        picker.hue = (1/6) * h
        picker.saturation = c / (1 - Math.abs(2 * ((max+min)/2) - 1))
        picker.lightness = (max + min)/2
    }
    onHueChanged: redrawTimer.restart()
    onSaturationChanged: redrawTimer.restart()

    Timer {
        id: redrawTimer
        interval: 4
        onTriggered: {
            hsCanvas.requestPaint();
            hsMarker.x = Math.round(hsCanvas.width*picker.hue - 2)
            hsMarker.y = Math.round(hsCanvas.width*(1-picker.saturation) - 2)

            //this to work assumes the above rgb->hsl conversion is correct
            picker.color = Qt.hsla(picker.hue, picker.saturation, picker.lightness, 1)
        }
    }

    Row {
        id: pickerRow
        clip: true
        Behavior on height {
            NumberAnimation {
                duration: units.longDuration
                easing.type: "InOutQuad"
            }
        }
        RoundMouseArea {
            id: roundarea
            width: 255
            height: width
            onPress: {
                hsMarker.x = roundarea.mouseX
                hsMarker.y = roundarea.mouseY
                picker.hue = roundarea.mouseX / width
                picker.saturation = 1 - hsMarker.y / height
            }
            onPositionChanged: {
                hsMarker.x = roundarea.mouseX
                hsMarker.y = roundarea.mouseY
                picker.hue = roundarea.mouseX / width
                picker.saturation = 1 - hsMarker.y / height
            }

            Canvas {
                id: hsCanvas
                anchors.fill: parent
                anchors.margins: 0
                onPaint: {
                    var ctx = getContext('2d');
                    var gradient = ctx.createLinearGradient(0, 0, width, 0)
                    for (var i = 0; i < 10; ++i) {
                        gradient.addColorStop(i/10, Qt.hsla(i/10, 1, picker.lightness, 1));
                    }

                    ctx.beginPath();
                    ctx.fillStyle = gradient;
                    ctx.arc(width / 2, height / 2, width / 2, 0, 2*Math.PI, true);
                    ctx.fill();
                }
            }
            Rectangle {
                id: hsMarker
                width: 20
                x: roundarea.x + roundarea.width / 2 - width/2
                y: roundarea.y + roundarea.height / 2  - width/2
                height: width
                radius: width
                color: Material.color(Material.BlueGrey)
                border {
                    color: Material.color(Material.Indigo)
                    width: 3
                }
            }
        }
    }
}
