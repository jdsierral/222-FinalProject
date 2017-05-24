//
//  AudioProcessor.hpp
//  Stimmung
//
//  Created by Juan David Sierra on 5/19/17.
//  Copyright © 2017 Juan David Sierra. All rights reserved.
//

#ifndef AudioProcessor_hpp
#define AudioProcessor_hpp

#include <stdio.h>
#include "Stk.h"
#include "RtAudio.h"
#include "FileWvIn.h"
#include "Convolver.hpp"
#include "Rotator.hpp"
#include "Smoother.h"

using namespace stk;
using namespace std;


class AudioProcessor {
public:
    AudioProcessor(int fs, unsigned int intendedBufSize, int numChans);
    ~AudioProcessor();
    
    int tick( void *outBuffer, unsigned int bufSize, void* dataBuffer);
    

    void initAudio( RtAudioCallback callback );
    void resizeBuffers(unsigned int bufSize);
    void startStreaming();
    void getFileStatistics();
    void initFftsIRs();
    void setGain(float newGain);
    
    void setPos(float newPos);
    float getPos();
    
    
private:
    RtAudio* dac;
    FileWvIn* file;
    
    // Processing Modules
    
    Rotator* rotator;
    Convolver* frontFft;
    Convolver* backFft;
    Convolver* leftFft;
    Convolver* rightFft;
    
    // Callback Variables
    
    unsigned int bufSize;
    int sampleRate;
    const int nChans;
    
    // Buffers
    
    StkFrames frontSpkr;
    StkFrames backSpkr;
    StkFrames leftSpkr;
    StkFrames rightSpkr;
    
    StkFrames BinLeft;
    StkFrames BinRight;
    
    // Processing Variables
    
    Smoother posSmooth;
    
    float gain;
    int nFFT;
    int irLen;
    
    // Playback Options
    
    bool repeatEnabled;
    
    
};

#endif /* AudioProcessor_hpp */
