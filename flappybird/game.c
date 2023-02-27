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

void user_isr(void)
{
    //User inputs
    if(OnButtonEnter(4)){
        y-=6;
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
    //1st obstacle
    switch (r[0])
    {
        case 0:
            insert_sprite(xObstacle[0], 0, obstaclewidth, 32, obstacle1);
            break;
        case 1:
            insert_sprite(xObstacle[0], 0, obstaclewidth, 32, obstacle2);
            break;        
        case 2:
            insert_sprite(xObstacle[0], 0, obstaclewidth, 32, obstacle3);
            break;        
        case 3:
            insert_sprite(xObstacle[0], 0, obstaclewidth, 32, obstacle4);
            break;        
        case 4:
            insert_sprite(xObstacle[0], 0, obstaclewidth, 32, obstacle5);
            break;        
        case 5:
            insert_sprite(xObstacle[0], 0, obstaclewidth, 32, obstacle6);
            break;        
        case 6:
            insert_sprite(xObstacle[0], 0, obstaclewidth, 32, obstacle7);
            break;        
        case 7:
            insert_sprite(xObstacle[0], 0, obstaclewidth, 32, obstacle8);
            break;        
        case 8:
            insert_sprite(xObstacle[0], 0, obstaclewidth, 32, obstacle9);
            break;        
        case 9:
            insert_sprite(xObstacle[0], 0, obstaclewidth, 32, obstacle10);
            break;        
                
        default:
            break;
    }
    xObstacle[0]--;

    
    if(timeoutInsertObstacle[0] == (128 + obstaclewidth)){
        xObstacle[0] = 128;
        timeoutInsertObstacle[0] = 0;
        r[0] = rand() % 10;
    }

    //2nd obstacle
    if(timeoutInsertObstacle[1] >= (distanceBetweenObstacles)){
        switch (r[1])
        {
        case 0:
            insert_sprite(xObstacle[1], 0, obstaclewidth, 32, obstacle1);
            break;
        case 1:
            insert_sprite(xObstacle[1], 0, obstaclewidth, 32, obstacle2);
            break;        
        case 2:
            insert_sprite(xObstacle[1], 0, obstaclewidth, 32, obstacle3);
            break;        
        case 3:
            insert_sprite(xObstacle[1], 0, obstaclewidth, 32, obstacle4);
            break;        
        case 4:
            insert_sprite(xObstacle[1], 0, obstaclewidth, 32, obstacle5);
            break;        
        case 5:
            insert_sprite(xObstacle[1], 0, obstaclewidth, 32, obstacle6);
            break;        
        case 6:
            insert_sprite(xObstacle[1], 0, obstaclewidth, 32, obstacle7);
            break;        
        case 7:
            insert_sprite(xObstacle[1], 0, obstaclewidth, 32, obstacle8);
            break;        
        case 8:
            insert_sprite(xObstacle[1], 0, obstaclewidth, 32, obstacle9);
            break;        
        case 9:
            insert_sprite(xObstacle[1], 0, obstaclewidth, 32, obstacle10);
            break;        
                
        default:
            break;
        }
        xObstacle[1]--;
    }
    if(xObstacle[1] == -(obstaclewidth)){
        xObstacle[1] = 128;
        timeoutInsertObstacle[1] = distanceBetweenObstacles;
        r[1] = rand() % 10;
    }

    //3rd obstacle
    if(timeoutInsertObstacle[2] >= (distanceBetweenObstacles * 2)){
        switch (r[2])
        {
        case 0:
            insert_sprite(xObstacle[2], 0, obstaclewidth, 32, obstacle1);
            break;
        case 1:
            insert_sprite(xObstacle[2], 0, obstaclewidth, 32, obstacle2);
            break;        
        case 2:
            insert_sprite(xObstacle[2], 0, obstaclewidth, 32, obstacle3);
            break;        
        case 3:
            insert_sprite(xObstacle[2], 0, obstaclewidth, 32, obstacle4);
            break;        
        case 4:
            insert_sprite(xObstacle[2], 0, obstaclewidth, 32, obstacle5);
            break;        
        case 5:
            insert_sprite(xObstacle[2], 0, obstaclewidth, 32, obstacle6);
            break;        
        case 6:
            insert_sprite(xObstacle[2], 0, obstaclewidth, 32, obstacle7);
            break;        
        case 7:
            insert_sprite(xObstacle[2], 0, obstaclewidth, 32, obstacle8);
            break;        
        case 8:
            insert_sprite(xObstacle[2], 0, obstaclewidth, 32, obstacle9);
            break;        
        case 9:
            insert_sprite(xObstacle[2], 0, obstaclewidth, 32, obstacle10);
            break;        
                
        default:
            break;
        }
        xObstacle[2]--;
    }
    
    if(xObstacle[2] == -(obstaclewidth)){
        xObstacle[2] = 128;
        timeoutInsertObstacle[2] = distanceBetweenObstacles * 2;
        r[2] = rand() % 10;

    }

    //4th obstacle
    if(timeoutInsertObstacle[3] >= (distanceBetweenObstacles * 3)){
        switch (r[3])
        {
        case 0:
            insert_sprite(xObstacle[3], 0, obstaclewidth, 32, obstacle1);
            break;
        case 1:
            insert_sprite(xObstacle[3], 0, obstaclewidth, 32, obstacle2);
            break;        
        case 2:
            insert_sprite(xObstacle[3], 0, obstaclewidth, 32, obstacle3);
            break;        
        case 3:
            insert_sprite(xObstacle[3], 0, obstaclewidth, 32, obstacle4);
            break;        
        case 4:
            insert_sprite(xObstacle[3], 0, obstaclewidth, 32, obstacle5);
            break;        
        case 5:
            insert_sprite(xObstacle[3], 0, obstaclewidth, 32, obstacle6);
            break;        
        case 6:
            insert_sprite(xObstacle[3], 0, obstaclewidth, 32, obstacle7);
            break;        
        case 7:
            insert_sprite(xObstacle[3], 0, obstaclewidth, 32, obstacle8);
            break;        
        case 8:
            insert_sprite(xObstacle[3], 0, obstaclewidth, 32, obstacle9);
            break;        
        case 9:
            insert_sprite(xObstacle[3], 0, obstaclewidth, 32, obstacle10);
            break;        
                
        default:
            break;
        }
        xObstacle[3]--;
    }
    
    if(xObstacle[3] == -(obstaclewidth)){
        xObstacle[3] = 128;
        timeoutInsertObstacle[3] = distanceBetweenObstacles * 3;
        r[3] = rand() % 10;

    }

    //Checks for collision on character
    if(collision_check(x, y, character)){
        //Protocol for ending game if true
        endGame = 1;
        T2CONCLR = 0x8070;
        return;
    }

    insert_sprite(x, y, 10, 7,character);
    }
}

void start(void)
{
    clear_display();
    distanceBetweenObstacles = 24 + obstaclewidth;

    //Pseudo random, needs fixing, one option is to create a timer in menu and generate a seed in accordance to the timer value
    srand((unsigned)12345);
    
    x = 16;
    y = 12;
    obstaclewidth = 11;
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
    }

    insert_sprite(16, 12, 10, 7,character);

    enable_interrupt();
}

void update(void)
{
    display_gameupdate();
}