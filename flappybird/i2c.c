/*Code is written by N Nguyen*/
/*Doesn't work!*/
#include <stdint.h>
#include <pic32mx.h>
#include "flappybird.h"

void I2C_idle(void){
    while(I2C1CON & 0x1f){}
    while(I2C1STAT & 0x4000){}
}
void I2C_start(void){
    I2C_idle();
    I2C1CONSET = 1; //Start condition
    while(I2C1CON & 1){} //Start condition is not in progress
}
void I2C_stop(void){
    I2C_idle();
    I2C1CONSET = 4; //Stop condition
    while(I2C1CON & 4){}
}
void I2C_restart(void){
    I2C_idle();
    I2C1CONSET = 2; // Restart condition
    I2C_idle();
}
void I2C_ack(void){
    I2C_idle();
    I2C1CONCLR = 0x20; //Acknowledge data bit is cleared, meaning an ack is sent
    I2C1CONSET = 0x10; //Acknowledge sequence bit, cleared by module
}
void I2C_nack(void){
    I2C_idle();
    I2C1CONSET = 0x20; //Acknowledge data bit is set, meaning a nack is sent
    I2C1CONSET = 0x10; //Acknowledge sequence bit, cleared by module
    while(I2C1CON & 0x10){}
}
int I2C_Write(uint8_t data){
    I2C_idle();
    I2C1TRN = data;
    while(I2C1STAT & 0x4000){} //Transmission status 
	if(I2C1STAT & 0x8000){return 0;} //Acknowledge was received
    return 1;
}
uint8_t I2C_Read(){ 
    I2C_idle();
    I2C1CONSET = 0x8; //Receive enable
    while(!(I2C1STAT & 2)){}  
    return I2C1RCV;
}