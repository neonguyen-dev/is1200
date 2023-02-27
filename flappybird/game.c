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

void insertObstacle(int obstacle){
    if(timeoutInsertObstacle[obstacle] >= (distanceBetweenObstacles * obstacle)){
        switch (r[obstacle])
        {
        case 0:
            insert_sprite(xObstacle[obstacle], 0, obstaclewidth, 32, obstacle1);
            break;
        case 1:
            insert_sprite(xObstacle[obstacle], 0, obstaclewidth, 32, obstacle2);
            break;        
        case 2:
            insert_sprite(xObstacle[obstacle], 0, obstaclewidth, 32, obstacle3);
            break;        
        case 3:
            insert_sprite(xObstacle[obstacle], 0, obstaclewidth, 32, obstacle4);
            break;        
        case 4:
            insert_sprite(xObstacle[obstacle], 0, obstaclewidth, 32, obstacle5);
            break;        
        case 5:
            insert_sprite(xObstacle[obstacle], 0, obstaclewidth, 32, obstacle6);
            break;        
        case 6:
            insert_sprite(xObstacle[obstacle], 0, obstaclewidth, 32, obstacle7);
            break;        
        case 7:
            insert_sprite(xObstacle[obstacle], 0, obstaclewidth, 32, obstacle8);
            break;        
        case 8:
            insert_sprite(xObstacle[obstacle], 0, obstaclewidth, 32, obstacle9);
            break;        
        case 9:
            insert_sprite(xObstacle[obstacle], 0, obstaclewidth, 32, obstacle10);
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

    }

}

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
    insertObstacle(0);
    insertObstacle(1);
    insertObstacle(2);
    insertObstacle(3);

    //Checks for collision on character
    if(collision_check(x, y, character)){
        //Protocol for ending game if true
        endGame = 1;
        T2CONCLR = 0x8070;
        return;
    }
    
    if(xObstacle[0] == 16 || xObstacle[1] == 16 ||xObstacle[2] == 16 || xObstacle[3] == 16){
        PORTE += 1;
    }
    
    insert_sprite(x, y, 10, 7,character);
    }
}

void start(void)
{
    clear_display();
    PORTE = 0;
    distanceBetweenObstacles = 24 + obstaclewidth;

    //Pseudo random, needs fixing, one option is to create a timer in menu and generate a seed in accordance to the timer value
    srand((unsigned)12345);
    
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
    }

    insert_sprite(16, 12, 10, 7,character);

    enable_interrupt();
}

void update(void)
{
    display_gameupdate();
}