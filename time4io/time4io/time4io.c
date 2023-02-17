#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int getsw( void ){
    //return status of switches
    int temp = (PORTD & 0xf00) >> 8; // 1111 0000 0000
    return temp;
}

int getbtns(void){
    //return status of buttons
    int temp = (PORTD & 0xE0) >> 5; // 1110 0000
    return temp;
}