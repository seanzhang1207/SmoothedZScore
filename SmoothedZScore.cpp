/*
  RingBuffer.cpp - A simple ring buffer
  Created by Sean Zhang, July 29, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "SmoothedZScore.h"

SmoothedZScore::SmoothedZScore(int lag, float threshold, float influence) {
    _buf = new CircularBuffer(lag, sizeof(int));
    _lag = lag;
    _threshold = threshold;
    _influence = influence;
    _sig = 0;
    _avgFilter = 0.0;
    _stdFilter = 0.0;
    _negSignalCallback = NULL;
    _posSignalCallback = NULL;
    _noSignalCallback = NULL;
}

SmoothedZScore::~SmoothedZScore() {
    delete _buf;
}

void SmoothedZScore::feedData(int data) {
    if (_buf.getDataCount() == _lag) {
        if (abs(data - _avgFilter) > _threshold * _stdFilter) {
            if (data > _avgFilter) {
                sig = 1;
                if (_posSignalCallback) {
                    (*_posSignalCallback)();
                }
            } else {
                sig = -1;
                if (_negSignalCallback) {
                    (*_negSignalCallback)();
                }
            }
            int tmpData;
            _buf.getDataAtIndex(-1, &tmpData);
            int filtered = (int)(_influence * data + (1 - _influence) * tmpData);
            _buf.appendData(&filtered);
        } else {
            sig = 0;
            if (_noSignalCallback) {
                (*_noSignalCallback)();
            }
            _buf.appendData(data);
        }
        for (int i=0; i<_lag; i++) {
            int tmpData;
            _buf.getDataAtIndex(i, &tmpData);
            _avgFilter += (float)tmpData;
        }
        _avgFilter /= _lag;


        for (int i=0; i<_lag; i++) {
            int tmpData;
            _buf.getDataAtIndex(i, &tmpData);
            _stdFilter += ((float)tmpData - _avgFilter) * ((float)tmpData - _avgFilter);
        }
        _stdFilter /= _lag;
        _stdFilter = sqrt(_stdFilter);

    } else {
        _buf.appendData(&data);
        if (dataCount == _lag) {
            for (int i=0; i<_lag; i++) {
                int tmpData;
                _buf.getDataAtIndex(i, &tmpData);
                _avgFilter += (float)tmpData;
            }
            _avgFilter /= _lag;


            for (int i=0; i<_lag; i++) {
                int tmpData;
                _buf.getDataAtIndex(i, &tmpData);
                _stdFilter += ((float)tmpData - _avgFilter) * ((float)tmpData - _avgFilter);
            }
            _stdFilter /= _lag;
            _stdFilter = sqrt(_stdFilter);
        }
    }
}

void SmoothedZScore::registerCallback(int sig, void (*callback)()) {
    if (sig == 1) {
        _posSignalCallback = callback;
    } else if (sig == -1) {
        _negSignalCallback = callback;
    } else if (sig == 0) {
        _noSignalCallback = callback;
    }
}
