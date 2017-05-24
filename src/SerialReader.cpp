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
    tcgetattr(STDOUT_FILENO, &old_stdio);
    
    memset(&stdio, 0 , sizeof(stdio));
    stdio.c_iflag = 0;
    stdio.c_oflag = 0;
    stdio.c_cflag=0;
    stdio.c_lflag=0;
    stdio.c_cc[VMIN]=1;
    stdio.c_cc[VTIME]=0;
    
    tcsetattr(STDOUT_FILENO, TCSANOW, &stdio);
    tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    
    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL; // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;
    
    portId =  open (portName.c_str(), O_RDWR, O_NONBLOCK);
    cfsetspeed(&tio, baudRate);
    cfsetspeed(&tio, baudRate);
    
    tcsetattr(portId, TCSANOW, &tio);
    
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
    portName = "/dev/ttyACMO";
}
