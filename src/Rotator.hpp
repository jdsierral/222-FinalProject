//
//  Rotator.hpp
//  Stimmung
//
//  Created by Juan David Sierra on 5/19/17.
//  Copyright © 2017 Juan David Sierra. All rights reserved.
//

#ifndef Rotator_hpp
#define Rotator_hpp

#include <stdio.h>
#include <math.h>

#include "Stk.h"

using namespace stk;


class Rotator {
public:
    
    Rotator();
    void process(float &x, float &y);
    
    void setPos(float newTheta);
    float getPos();
    
    
private:
    float theta;
    
    
};

#endif /* Rotator_hpp */
