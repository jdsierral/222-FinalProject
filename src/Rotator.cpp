//
//  Rotator.cpp
//  Stimmung
//
//  Created by Juan David Sierra on 5/19/17.
//  Copyright © 2017 Juan David Sierra. All rights reserved.
//

#include "Rotator.hpp"



Rotator::Rotator()
: theta(0)
{
}

void Rotator::process(float &x, float &y) {
    float x_ = x * cos(theta * 2 * M_PI) - y * sin(theta * 2 * M_PI);
    float y_ = x * sin(theta * 2 * M_PI) + y * cos(theta * 2 * M_PI);
    
    x = y_;
    y = x_;
}

void Rotator::setPos(float newTheta) {
    theta = newTheta;
}

float Rotator::getPos() {
    return theta;
}
