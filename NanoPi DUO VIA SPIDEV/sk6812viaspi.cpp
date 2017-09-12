#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <string.h>
#include "NeoViaSPI.h"


//LED Stuff
const short int numLeds = 300;
const char maxValue = 64;
short int rainbowSize = maxValue*6;
char tempColour[3] = {0,0,0};
short int ledIndex=0;
unsigned short int cIndex=0;

//LEDs
NeoViaSPI leds(numLeds);

//SPI stuff
int spiDevice;
const char *device = "/dev/spidev1.0";
uint8_t spiMode;
uint8_t bits = 8;
uint32_t speed = 3333333;
uint8_t returnBuffer;

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
	  cIndex+=5;
	  usleep(10000);
    }

    return 0;
 }
 


 void renderLEDs()
{
	struct spi_ioc_transfer spiDataTransferBlock;
	uint8_t dataBlock[leds._NeoBitsframeLength];
	
	leds.encode();
	memcpy(dataBlock, leds.neoBits, leds._NeoBitsframeLength);
	
	spiDataTransferBlock.tx_buf = (unsigned long)dataBlock;
	spiDataTransferBlock.rx_buf = (unsigned long)returnBuffer;
	spiDataTransferBlock.len = leds._NeoBitsframeLength;
	spiDataTransferBlock.delay_usecs = 0;
	spiDataTransferBlock.speed_hz = speed;
	spiDataTransferBlock.bits_per_word = bits;
	ioctl(spiDevice, SPI_IOC_MESSAGE(1), &spiDataTransferBlock);	
	
	usleep(100);
	
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

void initSPI()
{
	spiDevice = open(device, O_RDWR);
	if(spiDevice<0){printf("\r\nSPI DEVICE FAILED TO OPEN\r\n");}
	spiMode = SPI_MODE_0;
	//Set SPI Mode 
	ioctl(spiDevice, SPI_IOC_WR_MODE, &spiMode);
	if( ioctl(spiDevice, SPI_IOC_RD_MODE, &spiMode)==-1 ){printf("\r\nMODE NOT SET\r\n");}
	//set Bits Per Word
	ioctl(spiDevice, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if( ioctl(spiDevice, SPI_IOC_RD_BITS_PER_WORD, &bits)==-1 ){printf("\r\nBITS NOT SET\r\n");}
	//Set SPI Speed
	ioctl(spiDevice, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if( ioctl(spiDevice, SPI_IOC_RD_MAX_SPEED_HZ, &speed)==-1 ){printf("\r\nSPEED NOT SET\r\n");}
}
