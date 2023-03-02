#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "flappybird.h"  /* Declatations for these labs */

void store_highscore(char name[], int value){
    int i,j,k;
    int highscoreValue = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 14; j > 3; j--)
        {
            int power = 1;
            int digit = highscores[i][j] - '0';
            if(digit < 0){
                break;
            }

            for (k = 0; k < 14 - j; k++)
            {
                power *= 10;
            }
            highscoreValue += (digit * power);
        }
        if(highscoreValue < value){
            for (j = 0; j < 3; j++)
            {
                highscores[i][j] = name[j];
            }
            for (j = 14; j > 4; j--)
            {
                int digit = value % 10;
                value /= 10;
                highscores[i][j] = digit + '0';
            }
            return;
        }
        highscoreValue = 0;
    }
}