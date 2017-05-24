//
//  main.cpp
//  Stimmung
//
//  Created by Juan David Sierra on 5/19/17.
//  Copyright © 2017 Juan David Sierra. All rights reserved.
//

#include <iostream>
#include "Stk.h"
#include "FileWvIn.h"
#include "RtAudio.h"


#include "SerialReader.hpp"
#include "Rotator.hpp"
#include "Convolver.hpp"
#include "AudioProcessor.hpp"



// ========================================================
// Change this for Mac or Linux as a preProcessor Flag
//__MACOSX_CORE__
//__UNIX_JACK__
// ========================================================


#define NUM_CHANS 1
#define SAMPLE_RATE 44100
#define BUF_SIZE 512




using namespace stk;


bool done;
AudioProcessor processor(SAMPLE_RATE, BUF_SIZE, NUM_CHANS);
bool macMode = false;



int tick( void *outBuffer, void* inBuffer, unsigned int bufSize, double streamTime, RtAudioStreamStatus status, void* dataBuffer) {
    return processor.tick(outBuffer, bufSize, dataBuffer);
}


int main(int argc, char * argv[]) {
    
    if ( 0 == strcmp(argv[1], "MAC")) {
        cout << "MacModeEnabled" << endl;
        macMode = true;
    }
    
    // ====================================================
    // ====================================================
    
    SerialReader* serial;
    serial = new SerialReader;
    if (macMode) {
        serial->setMacPortName();
    } else {
        serial->setLinuxPortName();
    }
    
    if (serial->init()) {
        cout<< "SerialPort Opened" << endl;
    } else {
        cout << "Not working" << endl;
    }
    
    // ====================================================
    // ====================================================
    
    done = false;
    
    processor.readFile(macMode);
    processor.getFileStatistics();
    processor.initAudio( &tick );
    processor.startStreaming();
    
    char data[2];
    while (!done) {
        usleep(20);
        data[0] = data[1] = 0;
        int numBytes = serial->tick((void*)data, 2);
        
        if (numBytes == 2) {
            float pos = (float)data[0]/256.f;
            float gain = (float)data[1]/256.f;
            
            cout << "Pos: " << pos  << endl;
            cout << "Gain: "<< gain << endl;
            processor.setPos(pos);
            processor.setGain(gain);
        }
    }
    
    
    
    return 0;
}
