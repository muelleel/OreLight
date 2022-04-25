#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  struct { 
    bool fading;
    int color[3];
    int saturation;
  } flash;
  EEPROM.begin(sizeof(flash));


  flash.color[0] = 0;
  flash.color[1] = 0;
  flash.color[2] = 0;

  flash.fading = false;
  flash.saturation = 255;

  EEPROM.put(0, flash);
  EEPROM.commit();
}

void loop() {
  // put your main code here, to run repeatedly:


}
