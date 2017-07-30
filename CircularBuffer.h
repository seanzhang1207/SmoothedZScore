/*
  CircularBuffer.h - A simple cicular buffer
  Created by Sean Zhang, July 29, 2017.
  Released into the public domain.
*/
#ifndef CircularBuffer_h
#define CircularBuffer_h

#include "Arduino.h"

class CircularBuffer
{

    public:
        CircularBuffer(int bufferSize, unsigned int itemSize);
        ~CircularBuffer();
        int appendData(void *ptr);
        int getDataAtIndex(int index, void *ptr);
        int getDataCount();
    private:
        int _bufferSize;
        int _itemSize;
        byte *_buf;
        int _startIndex;
        int _dataCount;
};

#endif
