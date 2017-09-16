#include "NeoViaSPI.h"

NeoViaSPI::NeoViaSPI(unsigned short int numLEDs)
{  
  _numLEDs = numLEDs;
  _bytesPerLED = 4;
  _LEDframeLength = _numLEDs*_bytesPerLED;
  _NeoBitsframeLength = _LEDframeLength*4;
  
  LEDs = new byte[_LEDframeLength];
  neoBits = new byte[_NeoBitsframeLength];

  _blankValue = 0;
  _blankBlock = 192;
  
  //set up test values;
  _testValues[0][0] = 0;
  _testValues[0][1] = 136;
  _testValues[1][0] = 64;
  _testValues[1][1] = 140;
  _testValues[2][0] = 128;
  _testValues[2][1] = 200;
  _testValues[3][0] = 192;
  _testValues[3][1] = 204;
}

void NeoViaSPI::setPixel(short int pixelIndex, byte *pixelColour)
{
  _counter = _bytesPerLED*pixelIndex;
  LEDs[ _counter ] = pixelColour[1];
  LEDs[ _counter + 1 ] = pixelColour[0];
  LEDs[ _counter + 2 ] = pixelColour[2];
}
void NeoViaSPI::setRGBWPixel(short int pixelIndex, byte *pixelRGBWColour)
{
  _counter = _bytesPerLED*pixelIndex;
  LEDs[ _counter ] = pixelRGBWColour[1];
  LEDs[ _counter + 1 ] = pixelRGBWColour[0];
  LEDs[ _counter + 2 ] = pixelRGBWColour[2];
  LEDs[ _counter + 3 ] = pixelRGBWColour[3];
}

void NeoViaSPI::getPixel(short int pixelIndex, byte *pixelColour)
{
   _counter = _bytesPerLED*pixelIndex;
   pixelColour[0] = LEDs[ _counter + 1 ];
   pixelColour[1] = LEDs[ _counter ];
   pixelColour[2] = LEDs[ _counter + 2 ];
}
void NeoViaSPI::getRGBWPixel(short int pixelIndex, byte *pixelRGBWColour)
{
   _counter = _bytesPerLED*pixelIndex;
   pixelRGBWColour[0] = LEDs[ _counter + 1 ];
   pixelRGBWColour[1] = LEDs[ _counter ];
   pixelRGBWColour[2] = LEDs[ _counter + 2 ];
   pixelRGBWColour[3] = LEDs[ _counter + 3 ];
}

void NeoViaSPI::encode()
{
  _nCounter = 0;
  //Pixel Loop
  for(_counter=0; _counter<_LEDframeLength; _counter+=_bytesPerLED)
  {
    //Colour Loop
    for(_colCounter=0; _colCounter<_bytesPerLED; _colCounter++)
    {
      //Bit Loop
      _tmpValue = LEDs[_counter+_colCounter];
      for(_bitCounter=0; _bitCounter<4; _bitCounter++)
      {
        _blankValue = (_tmpValue & _blankBlock);
        if( _blankValue == _testValues[0][0] )
        {
          neoBits[_nCounter] = _testValues[0][1];
        }
        else if( _blankValue == _testValues[1][0] )
        {
          neoBits[_nCounter] = _testValues[1][1];
        }
        else if( _blankValue == _testValues[2][0] )
        {
          neoBits[_nCounter] = _testValues[2][1];
        }
        else if( _blankValue == _testValues[3][0] )
        {
          neoBits[_nCounter] = _testValues[3][1];
        }
        _tmpValue = _tmpValue<<2;
        _nCounter++;
      }
    }
  }
}

unsigned int NeoViaSPI::saturation(byte *pixelRGBWColour)
{
    float low, high;
    
    // Find the smallest of all three parameters.
    low = min(pixelRGBWColour[0], min(pixelRGBWColour[1], pixelRGBWColour[2]));
    // Find the highest of all three parameters.
    high = max(pixelRGBWColour[0], max(pixelRGBWColour[1], pixelRGBWColour[2]));
    // The difference between the last two variables
    // divided by the highest is the saturation.
    return round(100 * ((high - low) / high));
}

byte NeoViaSPI::getWhite(byte *pixelRGBWColour) 
{
    return (255 - saturation(pixelRGBWColour)) / 255 * (pixelRGBWColour[0] + pixelRGBWColour[1] + pixelRGBWColour[2]) / 3;
}

void NeoViaSPI::rgbToRGBW()
{
  _nCounter = 0;
  
  for(_counter=0; _counter<_LEDframeLength; _counter+=_bytesPerLED)
  {
   _tmpCol[0] = LEDs[ _counter + 1 ];
   _tmpCol[1] = LEDs[ _counter ];
   _tmpCol[2] = LEDs[ _counter +2];
   LEDs[ _counter + 3 ] = getWhite(_tmpCol); 
  }
    
}

