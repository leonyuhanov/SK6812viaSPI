#include <stdio.h>
#include "NeoViaSPI.h"
extern "C" {
  #include "libfahw.h"
}

//Pixel Config
const char maxValue=64;
const unsigned short int numLeds=50;
NeoViaSPI leds(numLeds);
char tempColour[3];
const short int rainbowSize = maxValue*6;  
unsigned short int cIndex=0, ledIndex=0;

//SPI Device
int devFD;
static unsigned char spiMode = 0;
static unsigned int spiSpeed = 3333333;

void initSPI();
void renderLEDs();
void getColour(short int colourIndex, char *currentColour);


int main(int argc, char *argv[]) 
{
	initSPI();
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
	  cIndex++;
	  usleep(7000);
	}
}

void renderLEDs()
{
    leds.encode();
	writeBytesToSPI(devFD, leds.neoBits, leds._NeoBitsframeLength, 0, spiSpeed, 8);
	usleep(100);
}

void initSPI()
{
	boardInit();
	if ((devFD = openHW(SPI0_PATH, O_RDWR)) < 0)
	{
        printf("\r\nDEVICE FAILURE: You are not running this as ROOT!\r\n");
    }
	setSPIDataMode(devFD, spiMode);
	setSPIWriteBitsPerWord(devFD, 8);
	setSPIMaxSpeed(devFD, spiSpeed);	
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