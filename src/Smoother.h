//
//  Smoother.h
//  Stimmung
//
//  Created by Juan David Sierra on 5/22/17.
//  Copyright © 2017 Juan David Sierra. All rights reserved.
//

#ifndef Smoother_h
#define Smoother_h

class Smoother {
    double delay,s;
    
public:
    Smoother():delay(0.0),s(0.0){}
    
    ~Smoother(){}
    
    // set the smoothing (pole)
    void setSmooth(double smooth){
        s = smooth;
    }
    
    // compute one sample
    double tick(double input){
        double currentSample = input * (1.0-s);
        currentSample = currentSample + delay;
        delay = currentSample * s;
        return currentSample;
    }
};


#endif /* Smoother_h */
