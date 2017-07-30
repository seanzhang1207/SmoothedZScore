/*
  RingBuffer.cpp - A simple ring buffer
  Created by Sean Zhang, July 29, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int bufferSize, unsigned int itemSize) {
    _buf = (byte *)malloc(itemSize * bufferSize);
    _bufferSize = bufferSize;
    _itemSize = itemSize;
    _startIndex = 0;
    _dataCount = 0;
}

CircularBuffer::~CircularBuffer() {
    free(_buf);
}

int CircularBuffer::appendData(void *ptr) {
    memcpy(_buf + ((_startIndex + _dataCount) % _bufferSize) * _itemSize, ptr, _itemSize);
    if (_dataCount == 10) {
        _startIndex = (_startIndex + 1) % _bufferSize;
    } else {
        _dataCount ++;
    }
    return _dataCount - 1;
}

int CircularBuffer::getDataAtIndex(int index, void *ptr) {
    if (((_startIndex + index) % _bufferSize) >= _dataCount) {
        return -1;
    }
    memcpy(ptr, _buf + ((_startIndex + index) % _bufferSize) * _itemSize, _itemSize);
    return 0;
}

int CircularBuffer::getDataCount() {
    return _dataCount;
}
