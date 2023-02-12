#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int getsw( void ){
    //return status of switches
    int temp = (PORTD & 0xf00) >> 8;
    return temp;
}

int getbtns(void){
    //return status of buttons
    int temp = (PORTD & 0xE0) >> 5;
    return temp;
}