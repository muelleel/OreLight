# OreLight

Wemos D1 Mini - ESP 8266 Minecraft OreLight firmware
Dimmable, Preprogrammed Ore-Colors, RGB

## Materials
- wemos d1 mini (esp8266 chip) ~ 20ct
- wemos d1 shield WS2812B ~ 1€
- mini momentary push button tactile (6x6mm) ~ 1ct
- 2x 3-4cm isolated copper wire
- 2d-paper and 3d-white and gray filament printer
- solderiron + solder
- paper, scissors and glue

## Build
### Hardware
1. Solder the LED-header on the d1 mini chip, so the esp8266-chip "heatsink" is in between the carrier-board and the LED-header. Be sure to solder the Board in the right way, GND to GND and so on. Also keep the two boards while soldering tight together!
2. Print the ```/3d-printable/orelight_base.stl``` with white filament (!!! NO SUPPORTS !!!), pause the print at layer 100 and insert the the soldered Hardware and resume/ finish the Print.
3. Print the ```/3d-printable/orelight_pattern_button.stl``` with gray filament.
4. Print the Layout ```/sheets/oreLightPaper.pdf``` and cut 5 rectangles from it - also cut on one peace a little notch for the button
5. Glue the paper peaces inside the printed cube
6. Solder the button ontop the LED-header to D5 and GND pin and push it into it's place - secure the Button with some glue
7. If needed glue the Cube onto the Base - but it should be a friction-fit.

### Software
1. Open ```/src/resetEeprom/resetEeprom.ino``` with the Arduino IDE and upload the code to the wemos chip - you may need to download board-information and the dependencys yourself!
2. Open and Upload ```/src/firmware/firmware.ino```

done!

See button usage info in ```/sheets/documentation.pdf```
