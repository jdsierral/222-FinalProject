//
//  AudioProcessor.cpp
//  Stimmung
//
//  Created by Juan David Sierra on 5/19/17.
//  Copyright © 2017 Juan David Sierra. All rights reserved.
//

#include "AudioProcessor.hpp"

// ==============================================================  //
// ==============================================================  //

AudioProcessor::AudioProcessor(int fs, unsigned int intendedBufSize, int numChans)
: sampleRate(fs), bufSize(intendedBufSize), nChans(numChans), gain(1), repeatEnabled(true)
{
    //    string filePath = "/Users/JuanS/Developer/CCRMA/222/Stimmung/AudioFiles/Quad.wav";
    //    string filePath = "/Users/JuanS/Developer/CCRMA/222/Stimmung/AudioFiles/Thomas_Mackay.wav";
    //    string filePath = "/Users/JuanS/Music/Stimmung/Stimmung/AudioFiles/NoiseTest.wav";
    string filePath = "/Users/JuanS/Developer/CCRMA/222/Stimmung/AudioFiles/Stimmung-May19.wav";
    
    Stk::setSampleRate(sampleRate);
    
    try {
        file = new FileWvIn(filePath);
    } catch (StkError &error) {
        error.printMessage();
    }
    
    
    try {
        dac = new RtAudio();
    } catch (StkError &error) {
        error.printMessage();
    }
    
    rotator  = new Rotator();
    
    frontFft = new Convolver("Front");
    backFft  = new Convolver("Back");
    leftFft  = new Convolver("Left");
    rightFft = new Convolver("Right");
}

AudioProcessor::~AudioProcessor() {
    file->closeFile();
    
    cout
    << "Dac Closing! playback stopped after "
    << dac->getStreamTime()
    << "seconds!"
    << endl;
    
    dac->closeStream();
    
    delete file;
    delete dac;
    delete rotator;
    delete frontFft;
    delete backFft;
    delete leftFft;
    delete rightFft;
}

// ==============================================================  //

void AudioProcessor::initAudio( RtAudioCallback callback ) {
    RtAudio::StreamParameters params;
    params.deviceId = dac->getDefaultOutputDevice();
    cout << "Using Device: " << dac->getDeviceInfo(params.deviceId).name << endl;
    params.nChannels = 2;
    cout << "With " << params.nChannels << " Channels." << endl;
    RtAudioFormat format = RTAUDIO_FLOAT64;
    
    cout << nChans << endl;
    
    try {
        dac->openStream(&params, NULL, format, sampleRate, &bufSize, callback, file);
        cout << "Running " <<endl;
    } catch ( RtAudioError &error ) {
        error.printMessage();
        exit(1);
    }
    
    resizeBuffers(bufSize);
    initFftsIRs();
    
    posSmooth.setSmooth(0.99);
}


void AudioProcessor::getFileStatistics() {
    cout << "File Sample Rate: " << file->getFileRate() << endl;
    if (file->getFileRate() != Stk::sampleRate()) {
        cout << "Match SampleRates!" << endl;
        exit(1);
    }
    
    cout << "Number of Channels: " << file->channelsOut() << endl;
}

// ==============================================================  //

void AudioProcessor::resizeBuffers(unsigned int bufSize) {
    frontSpkr.resize(bufSize, 1);
    backSpkr .resize(bufSize, 1);
    leftSpkr .resize(bufSize, 1);
    rightSpkr.resize(bufSize, 1);
    BinLeft  .resize(bufSize, 1);
    BinRight .resize(bufSize, 1);
}

// ==============================================================  //

void AudioProcessor::startStreaming() {
    try {
        dac->startStream();
    } catch (StkError &error) {
        error.printMessage();
        exit(1);
    }
}

// ==============================================================  //

void AudioProcessor::initFftsIRs() {
    frontFft->loadIrData(   0, 0, sampleRate);
    leftFft ->loadIrData( -90, 0, sampleRate);
    rightFft->loadIrData(  90, 0, sampleRate);
    backFft ->loadIrData(-179, 0, sampleRate);
}

// ==============================================================  //

void AudioProcessor::setPos(float newPos) {
    rotator->setPos(newPos);
}

void AudioProcessor::setGain(float newGain) {
    gain = newGain;
}

float AudioProcessor::getPos(){
    return rotator->getPos();
}

// ==============================================================  //

int AudioProcessor::tick( void *outBuffer, unsigned int bufSize, void* dataBuffer){
    StkFloat* out =  (StkFloat*)outBuffer;
    FileWvIn* file = (FileWvIn*)dataBuffer;
    
    for (int n = 0; n < bufSize; n++) {
        float w = file->tick(0);
        float x = file->lastOut(1);
        float y = file->lastOut(2);
        float z = file->lastOut(3);
        
        rotator->process(x, y);
        
        frontSpkr[n] =  w + x;
        backSpkr [n] =  w - x;
        leftSpkr [n] =  w + y;
        rightSpkr[n] =  w - y;
        
        BinLeft[n] = 0;
        BinRight[n] = 0;
    }
    
    frontFft->process(&frontSpkr[0], &BinLeft[0], &BinRight[0], bufSize);
    backFft-> process(&frontSpkr[0], &BinLeft[0], &BinRight[0], bufSize);
    leftFft-> process(&frontSpkr[0], &BinLeft[0], &BinRight[0], bufSize);
    rightFft->process(&frontSpkr[0], &BinLeft[0], &BinRight[0], bufSize);
    
    
    for (int n = 0; n < bufSize; n++) {
        BinLeft[n] = (leftSpkr[n] + frontSpkr[n])/2.0;
        BinRight[n] = (rightSpkr[n] + frontSpkr[n])/2.0;
    }
    
    
    for (int n = 0; n < bufSize; n++) {
        out[2 * n] = BinLeft[n] * gain;
        out[2 * n+1] = BinRight[n] * gain;
        
        if (BinLeft[n] > 1.0 || BinRight[n] > 1.0)
            cout << "Clipped!" << endl;
    }
    
    if (file->isFinished()) {
        if (repeatEnabled)
            file->reset();
        if (!file->isOpen())
            return 1;
    }
    return 0;
}
