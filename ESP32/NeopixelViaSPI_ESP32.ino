/*
      Coded for the ESP32
      //Pin out for module
      P23  SPI MOSI  -   To SK6812/WS2812/WS2812B/Neopixel Data In
*/
#include <WiFi.h>
#include "SPI.h"
#include "NeoViaSPI.h"
#include "colourObject.h"

//LED Stuff
const short int numLeds = 389+1;
const byte maxValue = 32;
byte tempColour[3] = {0,0,0};
short int pCnt=0;
unsigned short int cIndex=0;

NeoViaSPI leds = NeoViaSPI(numLeds);

char colourList[9*3]={maxValue,0,0, maxValue,maxValue,0, 0,maxValue,0, 0,maxValue,maxValue, 0,0,maxValue, maxValue,0,maxValue, maxValue,maxValue,maxValue, maxValue,0,0,0,0,0};
colourObject colourPallete(maxValue, 9, colourList);


void setup()
{
  WiFi.mode(WIFI_OFF);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setFrequency(3333333);
  
  //clear
  tempColour[0] = 0;
  tempColour[1] = 0;
  tempColour[2] = 0;
  for(pCnt=0; pCnt<numLeds-1; pCnt++)
  {
    leds.setPixel(pCnt, tempColour);
  }
  renderLEDs();

}


void renderLEDs()
{
  leds.encode();
  SPI.writeBytes(leds.neoBits, leds._NeoBitsframeLength);
  delayMicroseconds(80);
}

void loop()
{

  colourPallete.getColour(cIndex%colourPallete._bandWidth, tempColour);
  leds.setPixel(0, tempColour);
  for(pCnt=numLeds-1; pCnt>0; pCnt--)
  {
    leds.getPixel(pCnt-1, tempColour);
    leds.setPixel(pCnt, tempColour);
  }
  renderLEDs();
  cIndex++;
  delay(1);
}