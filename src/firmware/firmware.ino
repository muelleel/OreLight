#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include "OneButton.h"

Adafruit_NeoPixel led(1, 4, NEO_GRB + NEO_KHZ800);
OneButton button(14);

bool fading = false;
int fadingCounter = 0;

int common[][3] = {{0, 0, 0}, {255, 255, 0}, {255, 0, 0}, {61, 224, 229}, {0, 255, 0}, {255, 255, 255}};
int commonCounter = 0;

int dimmingDirection = true;

int color[] = {255, 255, 255};
int saturation = 255;

struct { 
    bool fading;
    int color[3];
    int saturation;
} flash;

void setup() {
  Serial.begin(115200);
  
  EEPROM.begin(sizeof(flash));
  EEPROM.get(0, flash);

  color[0] = flash.color[0];
  color[1] = flash.color[1];
  color[2] = flash.color[2];
  
  fading = flash.fading;
  if(flash.fading == -1) flash.fading = false;
  saturation = flash.saturation;
  saveConfig();
  
  led.begin();
  led.clear();

  button.attachClick([]() {
    //cycle common colours on Single-Click and store Position
    if(commonCounter >= 5) commonCounter = 0; else commonCounter++;
    Serial.println(commonCounter);
    color[0] = common[commonCounter][0];
    color[1] = common[commonCounter][1];
    color[2] = common[commonCounter][2];

    flash.color[0] = common[commonCounter][0];
    flash.color[1] = common[commonCounter][1];
    flash.color[2] = common[commonCounter][2];
    saveConfig();
    
  });
  
  button.attachDoubleClick([]() {
    //start Fading and store fading-status
    fading = !fading;
    
    flash.fading = fading;
    saveConfig();
  });

  button.attachLongPressStart([]() {
    //on each new Longpress reverse the direction the dimming will go
    dimmingDirection = !dimmingDirection;
  });

  button.attachDuringLongPress([]() {
    //on long press increment or decrement based on direction the saturation value
    if(dimmingDirection) {
      if(saturation < 255) saturation++;
    } else {
      if(saturation > 10) saturation--;
    }
    delay(10); //this delay controls the speed of the dimm-controlls
  });
  button.attachLongPressStop([]() {
    flash.saturation = saturation;
    saveConfig();
  });
}

void loop() {
  button.tick();

  if(fading) {
    fadingCounter++;
    if(fadingCounter >= 65535) fadingCounter = 0;
    led.setPixelColor(0, led.ColorHSV(fadingCounter, 255, saturation));
  } else {
    led.setPixelColor(0, led.Color(color[0]*(saturation/255.0), color[1]*(saturation/255.0), color[2]*(saturation/255.0)));
  }
  
    
  led.show();

}

void saveConfig() {
  EEPROM.put(0, flash);
  EEPROM.commit();
}
