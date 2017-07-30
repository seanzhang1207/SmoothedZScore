/*
  SmoothedZScore.h - Peak detection with smoothed z-score algorithm
  Created by Sean Zhang, July 29, 2017.
  Released into the public domain.
*/
#ifndef SmoothedZScore_h
#define SmoothedZScore_h

#include "Arduino.h"
#include "CircularBuffer.h"

class SmoothedZScore
{

    public:
        SmoothedZScore(int lag, float threshold, float influence);
        ~SmoothedZScore();
        void feedData(int data);
        void registerCallback(int signal, void (*f)());
    private:
        int _lag;
        float _threshold;
        float _influence;
        float _avgFilter = 0;
        float _stdFilter = 0;
        int _sig;
        CircularBuffer *_buf;
        void (*_negSignalCallback)();
        void (*_posSignalCallback)();
        void (*_noSignalCallback)();
};

#endif
