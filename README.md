# Giraffe project

Connected giraffe using 3D printing, electronic and software

## 3D Printing

This part describe printing / 3D 

### Giraffe model

TODO.

### Basement

Basement has been developped with fusion 360.
TODO describe printing process for basement.

## Hardware 

TODO.

## ESP32

This part descibe arduino software for ESP32.

### Change partition management of ESP32

1 - You need to change partition management in file $ARDUINO_DIRECTORY/hardware/espressif/esp32/tools/partitions/default.csv to :

``` csv
# Name,   Type, SubType, Offset,  Size, Flags
nvs,      data, nvs,     0x9000,  0x5000,
otadata,  data, ota,     0xe000,  0x2000,
app0,     app,  ota_0,   0x10000, 0x1F0000,
app1,     app,  ota_1,   0x200000,0x200000,

```
Due to bluetooth stack size. [See this issue](https://github.com/espressif/arduino-esp32/issues/1075)

2 - Update maximum application flash size in file $ARDUINO_DIRECTORY/hardware/espressif/esp32/board.txt at line 12 with the corresponding size your set in previous step:

```
esp32.upload.maximum_size=2031616
```

## Android APP

TODO.

## Integration

![Integration video](images/basement.gif). 

TODO.
