//
//  Convolver.hpp
//  Stimmung
//
//  Created by Juan David Sierra on 5/19/17.
//  Copyright © 2017 Juan David Sierra. All rights reserved.
//

#ifndef Convolver_hpp
#define Convolver_hpp

#include <stdio.h>
#include <iostream>
#include "math.h"
#include "fft.h"
#include "Stk.h"
#include "mit_hrtf_lib.h"

using namespace stk;
using namespace std;

class Convolver {
public:
    Convolver(string name);
    ~Convolver();
    
    void process(StkFloat* spkr, StkFloat* leftBin, StkFloat* rightBin, unsigned int bufSize);
    void initBuffers();
    void setFFTSize(int nFFT);
    void loadIrData(int azimuth, int elevation, int sampleRate);
    
private:
    int nFFT;
    int nTaps;
    
    int rdPos;
    int wtPos;
    
    
    short* pLeft;
    short* pRight;
    
    int sampleRate;
    
    StkFrames resL;
    StkFrames resR;
    vector<complex> irL;
    vector<complex> irR;
    vector<complex> dataL;
    vector<complex> dataR;
    
    string name;
    
};



#endif /* Convolver_hpp */
