#include <stdint.h>
#include <pic32mx.h>
#include "flappybird.h"

void I2C_idle(void){
    while(I2C1CON & 0x1f);
    while(I2C1STAT & 0x4);
}
void I2C_start(void){
    I2C_idle();
    I2C1CONSET = 1;
    while(I2C1CON & 1);
}
void I2C_stop(void){
    I2C_idle();
    I2C1CONSET = 4;
}
void I2C_restart(void){
    I2C_idle();
    I2C1CONSET = 2;
}
void I2C_ack(void){
    I2C_idle();
    I2C1CONCLR = 0x20;
    I2C1CONSET = 0x10;
    while(I2C1CON & 0x10);
}
void I2C_nack(void){
    I2C_idle();
    I2C1CONSET = 0x20;
    I2C1CONSET = 0x10;
    while(I2C1CON & 0x10);
}