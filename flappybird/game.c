#include <stdint.h> 
#include <pic32mx.h>
#include "flappybird.h"

void user_isr(void){

}

void start(void){
    
}

void update(void){
    int button = getbtns();

    if((button & 0b001) == 1){

    }

    if((button & 0b010) == 2){

    }

    if((button & 0b100) == 4){

    }
    display_image(0, character);
}