//
//  main.cpp
//  Serial
//
//  Created by Juan David Sierra on 5/3/17.
//  Copyright © 2017 Juan David Sierra. All rights reserved.
//

#include <iostream>

using namespace std;

float pos;

//int main(int argc, const char * argv[]) {
//    
//    
//    
//    
//    return 0;
//}




// ======================================================================= //

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

void serialRead(int* serialPort, int br) {
    struct termios tio;
    struct termios stdio;
    struct termios old_stdio;

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
    
    *serialPort = open ("/dev/cu.usbmodem411", O_RDWR, O_NONBLOCK);
    cfsetspeed(&tio, br);
    cfsetspeed(&tio, br);
    
    tcsetattr(*serialPort, TCSANOW, &tio);
    
    
    
}

int main(int argc,char** argv)
{
    int serialPort;
    int dataByte;
    int n = 0;
    
    serialRead(&serialPort, B9600);
    
    
    while (true) {
        char dataSize = read(serialPort, &dataByte, 1);
        
        if (dataSize > 0) {
            if (++n % 4 != 0) {
                dataByte = (dataByte<<1) + dataByte;
            } else {
                cout << dataByte << endl;
                dataByte = 0;
            }
            
        }
        sleep(0.01);
    }
    
    
    close(serialPort);
    
    return EXIT_SUCCESS;
}
