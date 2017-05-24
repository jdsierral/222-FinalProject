//
//  Convolver.cpp
//  Stimmung
//
//  Created by Juan David Sierra on 5/19/17.
//  Copyright © 2017 Juan David Sierra. All rights reserved.
//

#include "Convolver.hpp"


Convolver::Convolver(string name) : name(name), rdPos(0), wtPos(0) {
}

Convolver::~Convolver(){
    
}

void Convolver::initBuffers(){
}

void Convolver::process(StkFloat* spkr, StkFloat* leftBin, StkFloat* rightBin, unsigned int bufSize){
    
    for (int n = 0; n < nFFT; n++)
        dataL[n] = complex( n < bufSize ? spkr[n] : 0.0 );
    
    CFFT::Forward(dataL.data(), nFFT);
    
    for (int n = 0; n < nFFT; n++) {
        dataR[n] = dataL[n] * irR[n];
        dataL[n] *= irL[n];
    }
    
    CFFT::Inverse(dataL.data(), nFFT);
    CFFT::Inverse(dataR.data(), nFFT);
    
    for (int n = 0; n < nFFT; n ++) {
        resL[wtPos] += dataL[n].re();
        resR[wtPos] += dataR[n].re();
        
        if (++wtPos <= nFFT) wtPos = 0;
    }
    
    for (int n = 0; n < bufSize; n ++) {
        leftBin[n]  += resL[rdPos];
        rightBin[n] += resR[rdPos];
        
        resL[rdPos] = 0;
        resR[rdPos] = 0;
        if (++rdPos <= nFFT) rdPos = 0;
    }
    
    wtPos = rdPos;
}


void Convolver::setFFTSize(int nFFT) {
    this->nFFT = nFFT;
    
    irL.resize(nFFT);
    irR.resize(nFFT);
    dataL.resize(nFFT);
    dataR.resize(nFFT);
    resL.resize(nFFT, 1, 0);
    resR.resize(nFFT, 1, 0);
}

void Convolver::loadIrData(int azimuth, int elevation, int sampleRate) {
    nTaps = mit_hrtf_availability(azimuth, elevation, sampleRate, 0);
    
    if (nTaps) {
        pLeft = (short*)malloc(nTaps * sizeof(short));
        pRight= (short*)malloc(nTaps * sizeof(short));
        
        nTaps = mit_hrtf_get(&azimuth, &elevation, sampleRate, 0, pLeft, pRight);
    } else {
        
        cout << "HRTF " << name << "Not Loaded correctly" << endl;
        exit(1);
    }
    
    int p = 1;
    while (p <= nTaps) {
        p *= 2;
    }
    
    setFFTSize(p);
    
    for (int n = 0; n < nFFT; n++) {
        // Verify this numbers O.o they seem odd.
        irL[n] = complex ( n < nTaps ? (double)pLeft[n] / 16536.0 : 0);
        irR[n] = complex ( n < nTaps ? (double)pRight[n]/ 16536.0 : 0);
    }
    
    delete pLeft;
    delete pRight;
    
    CFFT::Forward(irL.data(), nFFT);
    CFFT::Forward(irR.data(), nFFT);
    
    cout << "HRTF " << name << " Loaded correctly" << endl;
}
