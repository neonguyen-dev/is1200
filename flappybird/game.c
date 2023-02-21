#include <stdint.h> 
#include <pic32mx.h>
#include "flappybird.h"

int x = 16;
int y = 12;

void user_isr(void){
    clear_display();
    y++;
    IFSCLR(0) = 0x100;
    
    insert_sprite(x, y, 17, 12,character);
    
    int button = getbtns();

    if((button & 0b001) == 1){
        if(y <= 32){
            y-=3; 
        }
    }

    if((button & 0b010) == 2){

    }

    if((button & 0b100) == 4){

    }
}

void start(void){

    T2CON = 0x0;
    TMR2 = 0x0;
    PR2 = (80000000 / 256) / 10;

    //Set priority for interrupt
    IPCSET(2) = 0x1f;

    //enable interrupt
    IECSET(0) = 0x100;

    T2CON = 0x8070; //start the timer, reference to timer sheet

    insert_sprite(16, 12, 17, 12,character);

    enable_interrupt();
}

void update(void){
    display_gameupdate();
}