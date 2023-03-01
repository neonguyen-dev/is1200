#include <stdint.h>
#include <pic32mx.h>
#include "flappybird.h"

void I2C_idle(void){
    while(I2C1CON & 0x1f){
        if(I2C1CON & 0x1){
            display_string(0, "start con");
            display_textupdate();
        }
        if(I2C1CON & 0x2){
            display_string(0, "repeated start con");
            display_textupdate();
        }
        if(I2C1CON & 0x4){
            display_string(0, "stop con");
            display_textupdate();
        }
        if(I2C1CON & 0x8){
            display_string(0, "receive con");
            display_textupdate();
        }
        if(I2C1CON & 0x10){
            display_string(0, "acknowledge con");
            display_textupdate();
        }
    }
    while(I2C1STAT & 0x4000){
        display_string(0, "Master transmit in progress");
        display_textupdate();
    }
}
void I2C_start(void){
    I2C_idle();
    display_string(0, "start");
    display_textupdate();
    I2C1CONSET = 1; //Start condition
    while(I2C1CON & 1); //Start condition is not in progress
}
void I2C_stop(void){
    I2C_idle();
    display_string(0, "stop");
    display_textupdate();
    I2C1CONSET = 4; //Stop condition
}
void I2C_restart(void){
    I2C_idle();
    display_string(0, "restart");
    display_textupdate();
    I2C1CONSET = 2; // Restart condition
}
void I2C_ack(void){
    I2C_idle();
    display_string(0, "ack");
    display_textupdate();
    I2C1CONCLR = 0x20; //Acknowledge data bit is cleared, meaning an ack is sent
    I2C1CONSET = 0x10; //Acknowledge sequence bit, cleared by module
}
void I2C_nack(void){
    I2C_idle();
    display_string(0, "nack");
    display_textupdate();
    I2C1CONSET = 0x20; //Acknowledge data bit is set, meaning a nack is sent
    I2C1CONSET = 0x10; //Acknowledge sequence bit, cleared by module
}
int I2C_Write(uint8_t data){
	I2C1TRN = data;
    I2C_ack();
	I2C_idle();
    display_string(0, "write");
    display_textupdate();
	while(I2C1STAT & 0x8000); //Acknowledge was received
}
void I2C_Read(uint8_t * value){
    I2C1CONSET = 0x8;
    while(I2C1CON & 0x8);
    while(I2C1STAT & 0x2);
    *value = I2C1RCV;
    I2C_nack();
}