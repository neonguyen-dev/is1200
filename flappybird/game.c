/*Following code is written by P Patranika and N Nguyen*/
#include <stdint.h> 
#include <stdlib.h>
#include <pic32mx.h>
#include "flappybird.h"

int x = 16;
int y = 12;

int xObstacle[4] = {128, 128, 128, 128};

int obstaclewidth = 11;

int distanceBetweenObstacles = 24;

int timeoutCharacter = 0;
int timeoutObstacle = 0;
int timeoutInsertObstacle[4] = {0, 0, 0, 0};

int r[4];

int surpassedObstacle[4];

void insertObstacle(int obstacle){
    if(timeoutInsertObstacle[obstacle] >= (distanceBetweenObstacles * obstacle)){
        switch (r[obstacle])
        {
        case 0:
            insert_sprite((uint8_t *)obstacle1, xObstacle[obstacle], 0, obstaclewidth, 32);
            break;
        case 1:
            insert_sprite((uint8_t *)obstacle2, xObstacle[obstacle], 0, obstaclewidth, 32);
            break;        
        case 2:
            insert_sprite((uint8_t *)obstacle3, xObstacle[obstacle], 0, obstaclewidth, 32);
            break;        
        case 3:
            insert_sprite((uint8_t *)obstacle4, xObstacle[obstacle], 0, obstaclewidth, 32);
            break;        
        case 4:
            insert_sprite((uint8_t *)obstacle5, xObstacle[obstacle], 0, obstaclewidth, 32);
            break;        
        case 5:
            insert_sprite((uint8_t *)obstacle6, xObstacle[obstacle], 0, obstaclewidth, 32);
            break;        
        case 6:
            insert_sprite((uint8_t *)obstacle7, xObstacle[obstacle], 0, obstaclewidth, 32);
            break;        
        case 7:
            insert_sprite((uint8_t *)obstacle8, xObstacle[obstacle], 0, obstaclewidth, 32);
            break;        
        case 8:
            insert_sprite((uint8_t *)obstacle9, xObstacle[obstacle], 0, obstaclewidth, 32);
            break;        
        case 9:
            insert_sprite((uint8_t *)obstacle10, xObstacle[obstacle], 0, obstaclewidth, 32);
            break;        
                
        default:
            break;
        }
        xObstacle[obstacle]--;
    }
    
    if(xObstacle[obstacle] == -(obstaclewidth)){
        xObstacle[obstacle] = 128;
        timeoutInsertObstacle[obstacle] = distanceBetweenObstacles * obstacle;
        r[obstacle] = rand() % 10;
        surpassedObstacle[obstacle] = 0;
    }

    //Score checker & obstacle shrinker
    if(xObstacle[obstacle] < x && !surpassedObstacle[obstacle]){
        PORTE += 1;
        surpassedObstacle[obstacle] = 1;
        if(PORTE % 10 == 0 && currentGap > 13){
            shrink_obstacles(r);
            currentGap--;
        }
    }

}

void user_isr(void)
{
    int button = getbtns();
    //User inputs
    if(OnButtonEnter(4)){
        y-=6;
    }

    if(button & 0b001){
        x++;
        if(x >= 127 - 11){
            x = 127 - 11;
        }
    }
    if(button & 0b010){
        x--;
        if(x <= 0){
            x = 0;
        }
    }
    
    //Checking upperbounds
    if(y <= 0){
        y = 0;
    }  

    if(IFS(0) & 0x100){
    //Incrementing timer counts
    int i;
    timeoutCharacter++;
    timeoutObstacle++;
    for (i = 0; i < 4; i++)
    {
        timeoutInsertObstacle[i]++;
    }
    
    clear_display();
    IFSCLR(0) |= 0x100;
    
    y++;
    
    //Inserting obstacles
    insertObstacle(0);
    insertObstacle(1);
    insertObstacle(2);
    insertObstacle(3);
    
    //Checks for collision on character
    /*if(collision_check(x, y, character)){
        //Protocol for ending game if true
        endGame = 1;
        T2CONCLR = 0x8070;
        return;
    }*/
    
    insert_sprite((uint8_t *)character, x, y, 10, 7);
    //Shrink gap between obstacles
    
    }
}

void start(int seed)
{
    clear_display();
    PORTE = 0;
    distanceBetweenObstacles = 24 + obstaclewidth;

    srand(seed);
    
    x = 16;
    y = 12;
    timeoutCharacter = 0;
    timeoutObstacle = 0;

    int i;
    T2CON = 0x0;
    TMR2 = 0x0;
    PR2 = (80000000 / 256) / 15;

    //Set priority for interrupt
    IPCSET(2) = 0x1f;

    //enable interrupt
    IECSET(0) = 0x100;

    T2CON = 0x8070; //start the timer, reference to timer sheet

    for (i = 0; i < 4; i++)
    {
        r[i] = rand() % 10;
        timeoutInsertObstacle[i] = 0;
        xObstacle[i] = 128;
        surpassedObstacle[i] = 0;
    }

    insert_sprite((uint8_t *)character, 16, 12, 10, 7);

    enable_interrupt();
}

void update(void)
{
    display_gameupdate();
}