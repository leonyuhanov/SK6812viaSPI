#include <bcm2835.h>
#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>
#include "NeoViaSPI.h"


//LED Stuff
const short int numLeds = 25;
const char maxValue = 255;
short int rainbowSize = maxValue*6;
char tempColour[3] = {0,0,0};
short int ledIndex=0;
unsigned short int cIndex=0;

//LEDs
NeoViaSPI leds(numLeds);;

	
void renderLEDs();
void getColour(short int colourIndex, char *currentColour);

int main(int argc, char *argv[])
{
	//Init LEDs
	  bcm2835_init();
	  bcm2835_spi_begin();
	  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
	  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
	  bcm2835_spi_setClockDivider(250016000/3333333); 			  // The default 6000000


    while(1)
	{
	  getColour(cIndex%rainbowSize, tempColour);
	  leds.setPixel(0, tempColour);
	  for(ledIndex=numLeds-1; ledIndex>0; ledIndex--)
	  {
		leds.getPixel(ledIndex-1, tempColour);
		leds.setPixel(ledIndex, tempColour);
	  }
	  renderLEDs();
	  cIndex+=5;
	  bcm2835_delay(5);
    }

    return 0;
 }
 
void renderLEDs()
{
  
	leds.encode();
	bcm2835_spi_writenb(leds.neoBits, leds._NeoBitsframeLength);
	bcm2835_delayMicroseconds(80);
		
}

void getColour(short int colourIndex, char *currentColour)
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
 return;
}

