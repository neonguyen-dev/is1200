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

int OnButtonEnter(int button){
    static int onkey = 0;
    int getbutton = getbtns();

    if((getbutton & 0b100) == 4 && button == 4 && onkey == 0){
        onkey = 1;
        return 1;
    }
    else if(!((getbutton & 0b100) == 4) && button == 4 && onkey == 1){
        onkey = 0;
    }

    return 0;
}

void user_isr(void)
{
    //User inputs
    if(OnButtonEnter(4)){
        y-=6;
    }
    
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
<<<<<<< Updated upstream
            insert_sprite(xObstacle[0], 0, 17, 32, obstacle1);
            break;
        case 1:
            insert_sprite(xObstacle[0], 0, 17, 32, obstacle2);
            break;        
        case 2:
            insert_sprite(xObstacle[0], 0, 17, 32, obstacle3);
            break;        
        case 3:
            insert_sprite(xObstacle[0], 0, 17, 32, obstacle4);
            break;        
        case 4:
            insert_sprite(xObstacle[0], 0, 17, 32, obstacle5);
            break;        
        case 5:
            insert_sprite(xObstacle[0], 0, 17, 32, obstacle6);
            break;        
        case 6:
            insert_sprite(xObstacle[0], 0, 17, 32, obstacle7);
            break;        
        case 7:
            insert_sprite(xObstacle[0], 0, 17, 32, obstacle8);
            break;        
        case 8:
            insert_sprite(xObstacle[0], 0, 17, 32, obstacle9);
            break;        
        case 9:
            insert_sprite(xObstacle[0], 0, 17, 32, obstacle10);
=======
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
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
            insert_sprite(xObstacle[1], 0, 17, 32, obstacle1);
            break;
        case 1:
            insert_sprite(xObstacle[1], 0, 17, 32, obstacle2);
            break;        
        case 2:
            insert_sprite(xObstacle[1], 0, 17, 32, obstacle3);
            break;        
        case 3:
            insert_sprite(xObstacle[1], 0, 17, 32, obstacle4);
            break;        
        case 4:
            insert_sprite(xObstacle[1], 0, 17, 32, obstacle5);
            break;        
        case 5:
            insert_sprite(xObstacle[1], 0, 17, 32, obstacle6);
            break;        
        case 6:
            insert_sprite(xObstacle[1], 0, 17, 32, obstacle7);
            break;        
        case 7:
            insert_sprite(xObstacle[1], 0, 17, 32, obstacle8);
            break;        
        case 8:
            insert_sprite(xObstacle[1], 0, 17, 32, obstacle9);
            break;        
        case 9:
            insert_sprite(xObstacle[1], 0, 17, 32, obstacle10);
=======
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
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
            insert_sprite(xObstacle[2], 0, 17, 32, obstacle1);
            break;
        case 1:
            insert_sprite(xObstacle[2], 0, 17, 32, obstacle2);
            break;        
        case 2:
            insert_sprite(xObstacle[2], 0, 17, 32, obstacle3);
            break;        
        case 3:
            insert_sprite(xObstacle[2], 0, 17, 32, obstacle4);
            break;        
        case 4:
            insert_sprite(xObstacle[2], 0, 17, 32, obstacle5);
            break;        
        case 5:
            insert_sprite(xObstacle[2], 0, 17, 32, obstacle6);
            break;        
        case 6:
            insert_sprite(xObstacle[2], 0, 17, 32, obstacle7);
            break;        
        case 7:
            insert_sprite(xObstacle[2], 0, 17, 32, obstacle8);
            break;        
        case 8:
            insert_sprite(xObstacle[2], 0, 17, 32, obstacle9);
            break;        
        case 9:
            insert_sprite(xObstacle[2], 0, 17, 32, obstacle10);
=======
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
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
            insert_sprite(xObstacle[3], 0, 17, 32, obstacle1);
            break;
        case 1:
            insert_sprite(xObstacle[3], 0, 17, 32, obstacle2);
            break;        
        case 2:
            insert_sprite(xObstacle[3], 0, 17, 32, obstacle3);
            break;        
        case 3:
            insert_sprite(xObstacle[3], 0, 17, 32, obstacle4);
            break;        
        case 4:
            insert_sprite(xObstacle[3], 0, 17, 32, obstacle5);
            break;        
        case 5:
            insert_sprite(xObstacle[3], 0, 17, 32, obstacle6);
            break;        
        case 6:
            insert_sprite(xObstacle[3], 0, 17, 32, obstacle7);
            break;        
        case 7:
            insert_sprite(xObstacle[3], 0, 17, 32, obstacle8);
            break;        
        case 8:
            insert_sprite(xObstacle[3], 0, 17, 32, obstacle9);
            break;        
        case 9:
            insert_sprite(xObstacle[3], 0, 17, 32, obstacle10);
=======
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
>>>>>>> Stashed changes
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
        return;
    }

    insert_sprite(x, y, 10, 7,character);
    }
}

void start(void)
{
    distanceBetweenObstacles += obstaclewidth;

    srand((unsigned)12345);
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
    }

    insert_sprite(16, 12, 17, 12,character);

    enable_interrupt();
}

void update(void)
{
    display_gameupdate();
}