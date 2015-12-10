/*
 * 
 * 
 * 
 *
 */

#include "application.h"
#include "neopixel/neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D6
#define PIXEL_COUNT 26
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
String lastCommand = "";
String lastColor = "";

void setup() 
{
  strip.begin();
  strip.setBrightness(30);
  strip.show(); // Initialize all pixels to 'off'
  Particle.function("circle", colorCircle);
  Particle.function("flash", flash);
  
  Particle.function("chase", chase);
  
  chase("red");
  
}
void loop() 
{
    uint32_t color;
    if (lastCommand == "circle"){
        
        
        if (lastColor=="green"){
            color = strip.Color(0, 255, 0);
        } else if(lastColor=="red") {
            color = strip.Color(255, 0, 0);
        } else if(lastColor=="yellow") {
            color = strip.Color(255,255, 0);
        } else if(lastColor=="blue") {
            color = strip.Color(0,0, 255);
        } else if (lastColor=="pink") {
            color = strip.Color(253,41,218);
        } else if (lastColor=="orange") {
            color = strip.Color(255,102,0);
        } else if (lastColor=="purple") {
            color = strip.Color(102,0,204);
        }
        //if we mess up, it could be a blank color and a null ref
        lastColor = "";
        lastCommand = "";

        for(uint16_t i=0;i<5;i++){
            colorWipe(color, 100);
            delay(400);
            colorWipe(strip.Color(0, 0, 0), 100);
        }
    } else if (lastCommand == "flash"){
        color = getColor(lastColor);
        bool isRed = (lastColor=="red") ? true : false;
        lastColor = "";
        lastCommand = "";
        for(uint16_t l=0;l<((isRed) ? 30 : 10);l++){
            uint16_t i;
            for(i=0; i<strip.numPixels(); i++) {
                strip.setPixelColor(i,color);
            }
            strip.show();
            delay(500);
            i=0;
            for(i=0; i<strip.numPixels(); i++) {
                strip.setPixelColor(i,strip.Color(0, 0, 0));
            }
            strip.show();
            delay(500);
        }
    }  else if (lastCommand == "chase"){
        color = getColor(lastColor);
        //bool isRed = (lastColor=="red") ? true : false;
        lastColor = "";
        lastCommand = "";
        for(uint16_t r=0;r<20;r++){
            uint16_t t;
            for(t=0; t<strip.numPixels(); t++) {
                strip.setPixelColor(t,color);
                strip.show();
                delay(25);
                strip.setPixelColor(t,strip.Color(0, 0, 0));
                //since there is no delay setting pixels, this will set it off and turn on the next one
            }
            strip.show(); //we have to wipe out that last pixel
        }
    }

}
int flash(String command){
    lastCommand = "flash";
    lastColor = command;
    if (allowedColors(command)==1) 
        return 1;
    else {
        lastCommand = "";
        lastColor = "";
        return -1;
    }
}

int chase(String command){
    lastCommand = "chase";
    lastColor = command;
    if (allowedColors(command)==1) 
        return 1;
    else {
        lastCommand = "";
        lastColor = "";
        return -1;
    }
}

int allowedColors(String color){
    if (color == "green") 
        return 1;
    else if (color == "red")
        return 1;
    else if (color == "yellow")
        return 1;
    else if (color == "blue")
        return 1;
    else if (color == "pink")
        return 1;
    else if (color == "orange")
        return 1;
    else if (color == "purple")
        return 1;
    else {
        lastCommand = "";
        lastColor = "";
        return -1;
    }
}

uint32_t getColor(String color){
        if (color=="green"){
            return strip.Color(0, 255, 0);
        } else if(color=="red") {
            return strip.Color(255, 0, 0);
        } else if(color=="yellow") {
            return strip.Color(255,255, 0);
        } else if(color=="blue") {
            return strip.Color(0,0, 255);
        } else if (color=="pink") {
            return strip.Color(253,41,218);
        } else if (color=="orange") {
            return strip.Color(255,102,0);
        } else if (color=="purple") {
            return strip.Color(102,0,204);
        }
    return strip.Color(255, 0, 0);
}


int colorCircle(String command){
    lastCommand = "circle";
    lastColor = command;
    if (command == "green") {
        return 1;
    }
    else if (command == "red")
        return 1;
    else if (command == "yellow")
        return 1;
    else if (command == "blue")
        return 1;
    else if (command == "pink")
        return 1;
    else if (command == "orange")
        return 1;
    else if (command == "purple")
        return 1;
    else {
        lastCommand = "";
        lastColor = "";
        return -1;
    }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
