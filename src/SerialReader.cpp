//
//  SerialReader.cpp
//  Stimmung
//
//  Created by Juan David Sierra on 5/19/17.
//  Copyright © 2017 Juan David Sierra. All rights reserved.
//

#include "SerialReader.hpp"



SerialReader::SerialReader() : portId(0), portName(""), baudRate(B9600){
}


bool SerialReader::init() {
    
    memset(&pConf,0,sizeof(pConf));
    pConf.c_iflag=0;
    pConf.c_oflag=0;
    pConf.c_cflag=CS8|CREAD|CLOCAL;
    pConf.c_lflag=0;
    pConf.c_cc[VMIN]=2;
    pConf.c_cc[VTIME]=2;
    
    portId =  open (portName.c_str(), O_RDONLY);
    cfsetspeed(&pConf, baudRate);
    tcsetattr(portId, TCSANOW, &pConf);
    
    return portId != 0;
}


int SerialReader::tick(void* dataByte, size_t dataSize) {
    return (int)read(portId, dataByte, dataSize);
    
}


int SerialReader::getPortId() {
    return portId;
}

void SerialReader::setPortName(string portName) {
    this->portName = portName;
}

void SerialReader::setBaudRate(int newBaudRate) {
    baudRate = newBaudRate;
}

void SerialReader::setMacPortName() {
//    portName = "/dev/cu.usbmodem641";
    portName = "/dev/cu.usbmodem411";
}

void SerialReader::setLinuxPortName() {
   portName = "/dev/ttyACM0";
   //portName = "/dev/ttyS1";
}
