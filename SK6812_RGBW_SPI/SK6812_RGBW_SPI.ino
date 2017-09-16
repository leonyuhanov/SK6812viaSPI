/*
      Coded for the NodeMCU module
      //Pin out for module
      D7  DATA  -   To SK6812 Data In
*/
#include <ESP8266WiFi.h>
#include "SPI.h"
#include "NeoViaSPI.h"

//LED Stuff
const short int numLeds = 10;
const byte maxValue = 64;
short int rainbowSize = maxValue*8;
byte tempColour[3] = {0,0,0}, rgbwTempCol[4] = {0,0,0,0};
short int pCnt=0;
unsigned short int cIndex=0;

NeoViaSPI leds = NeoViaSPI(numLeds);

void setup()
{
  WiFi.mode(WIFI_OFF);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setFrequency(3333333);
  
  //clear
  rgbwTempCol[0] = 0;
  rgbwTempCol[1] = 0;
  rgbwTempCol[2] = 0;
  rgbwTempCol[3] = 0;
  for(pCnt=0; pCnt<numLeds; pCnt++)
  {
    leds.setRGBWPixel(pCnt, rgbwTempCol);
  }
  renderLEDs();

}


void renderLEDs()
{
  //leds.rgbToRGBW();
  leds.encode();
  SPI.writeBytes(leds.neoBits, leds._NeoBitsframeLength);
  delayMicroseconds(80);
}

void loop()
{

  testPattern();
//  getColour(cIndex%rainbowSize, tempColour);
//  leds.setPixel(0, tempColour);
//  for(pCnt=numLeds-1; pCnt>0; pCnt--)
//  {
//    leds.getPixel(pCnt-1, tempColour);
//    leds.setPixel(pCnt, tempColour);
//  }
//  renderLEDs();
//  cIndex+=2;
//  delay(10);
}

void testPattern()
{
  //clear

  rgbwTempCol[0] = 0;
  rgbwTempCol[1] = 0;
  rgbwTempCol[2] = 0;
  rgbwTempCol[3] = 0;
  for(pCnt=0; pCnt<numLeds; pCnt++)
  {
    leds.setRGBWPixel(pCnt, rgbwTempCol);
  }
  renderLEDs();
  delay(1000);
  
  rgbwTempCol[0] = maxValue;
  rgbwTempCol[1] = 0;
  rgbwTempCol[2] = 0;
  rgbwTempCol[3] = 0;
  for(pCnt=0; pCnt<numLeds; pCnt++)
  {
    leds.setRGBWPixel(pCnt, rgbwTempCol);
  }
  renderLEDs();
  delay(1000);

  rgbwTempCol[0] = 0;
  rgbwTempCol[1] = maxValue;
  rgbwTempCol[2] = 0;
  rgbwTempCol[3] = 0;
  for(pCnt=0; pCnt<numLeds; pCnt++)
  {
    leds.setRGBWPixel(pCnt, rgbwTempCol);
  }
  renderLEDs();
  delay(1000);
  
  rgbwTempCol[0] = 0;
  rgbwTempCol[1] = 0;
  rgbwTempCol[2] = maxValue;
  rgbwTempCol[3] = 0;
  for(pCnt=0; pCnt<numLeds; pCnt++)
  {
    leds.setRGBWPixel(pCnt, rgbwTempCol);
  }
  renderLEDs();
  delay(1000);

  rgbwTempCol[0] = maxValue;
  rgbwTempCol[1] = maxValue;
  rgbwTempCol[2] = maxValue;
  rgbwTempCol[3] = 0;
  for(pCnt=0; pCnt<numLeds; pCnt++)
  {
    leds.setRGBWPixel(pCnt, rgbwTempCol);
  }
  renderLEDs();
  delay(1000);

  rgbwTempCol[0] = 0;
  rgbwTempCol[1] = 0;
  rgbwTempCol[2] = 0;
  rgbwTempCol[3] = maxValue;
  for(pCnt=0; pCnt<numLeds; pCnt++)
  {
    leds.setRGBWPixel(pCnt, rgbwTempCol);
  }
  renderLEDs();
  delay(1000);

  rgbwTempCol[0] = maxValue;
  rgbwTempCol[1] = maxValue;
  rgbwTempCol[2] = maxValue;
  rgbwTempCol[3] = maxValue;
  for(pCnt=0; pCnt<numLeds; pCnt++)
  {
    leds.setRGBWPixel(pCnt, rgbwTempCol);
  }
  renderLEDs();
  delay(1000);
}

void getColour(short int colourIndex, byte *currentColour)
{

 if( colourIndex>=0 && colourIndex<maxValue )
 {
    currentColour[0] = maxValue;
    currentColour[1] = colourIndex;
    currentColour[2] = 0; 
 }
 else if(colourIndex>=maxValue && colourIndex<maxValue*2)
 {
    currentColour[0] = maxValue-(colourIndex-maxValue);
    currentColour[1] = maxValue;
    currentColour[2] = 0; 
 }
 else if(colourIndex>=maxValue*2 && colourIndex<maxValue*3)
 {
    currentColour[0] = 0;
    currentColour[1] = maxValue;
    currentColour[2] = colourIndex-maxValue*2; 
 }
 else if(colourIndex>=maxValue*3 && colourIndex<maxValue*4)
 {
    currentColour[0] = 0;
    currentColour[1] = maxValue-(colourIndex-maxValue*3);
    currentColour[2] = maxValue; 
 }
 else if(colourIndex>=maxValue*4 && colourIndex<maxValue*5)
 {
    currentColour[0] = colourIndex-maxValue*4;
    currentColour[1] = colourIndex-maxValue*4;
    currentColour[2] = maxValue; 
 }
 else if(colourIndex>=maxValue*5 && colourIndex<maxValue*6)
 {
    currentColour[0] = maxValue;
    currentColour[1] = maxValue-(colourIndex-maxValue*5);
    currentColour[2] = maxValue-(colourIndex-maxValue*5); 
 }
 else if(colourIndex>=maxValue*6 && colourIndex<maxValue*7)
 {
    currentColour[0] = maxValue-(colourIndex-maxValue*6);
    currentColour[1] = 0;
    currentColour[2] = 0; 
 }
 else if(colourIndex>=maxValue*7 && colourIndex<maxValue*8)
 {
    currentColour[0] = (colourIndex-maxValue*7);
    currentColour[1] = 0;
    currentColour[2] = 0; 
 }
 return;
}
