#ifndef NeoViaSPI_h
#define NeoViaSPI_h

class NeoViaSPI
{
  public:
    NeoViaSPI(unsigned short int numLEDs);
    void setPixel(short int pixelIndex, char *pixelColour);
    void getPixel(short int pixelIndex, char *pixelColour);
    void encode();
    
    char* LEDs;
    char* neoBits;
    
    unsigned short int _rainbowSize;
    unsigned short int _LEDframeLength;
    unsigned short int _NeoBitsframeLength;
	unsigned short int _memoryLength;
    unsigned short int _numLEDs;
    unsigned short int _counter;
    unsigned short int _nCounter;
    char _colCounter;
    char _bitCounter;
    
  private:
    char _blankValue;
    char _tmpValue;
    char _blankBlock;
    char _testValues[4][2];
};

#endif
