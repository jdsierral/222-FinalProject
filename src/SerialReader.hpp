//
//  SerialReader.hpp
//  Stimmung
//
//  Created by Juan David Sierra on 5/19/17.
//  Copyright © 2017 Juan David Sierra. All rights reserved.
//

#ifndef SerialReader_hpp
#define SerialReader_hpp

#include <stdio.h>


#include <iostream>
#include <string.h>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

class SerialReader {
public:
    SerialReader ();
    ~SerialReader ();
    
    bool init();
    
    int getPortId();
    void setPortName(string portName);
    void setBaudRate(int baudRate);
    void setMacPortName();
    void setLinuxPortName();
    
    int tick(void* dataByte, size_t dataSize);
    
    
private:
    
    float maxData;
    
    int portId;
    string portName;
    int baudRate;
    
    struct termios pConf;
};



#endif /* SerialReader_hpp */
