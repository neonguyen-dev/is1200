/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "flappybird.h"  /* Declatations for these labs */

/* Declare a helper function which is local to this file */
static void num32asc( char * s, int ); 

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

/* display_debug
   A function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
/*Code from Labwork*/
void display_debug( volatile int * const addr )
{
  display_string( 1, "Addr" );
  display_string( 2, "Data" );
  num32asc( &textbuffer[1][6], (int) addr );
  num32asc( &textbuffer[2][6], *addr );
  display_textupdate();
}

/*Code from Labwork*/
uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

/*Code from Labwork*/
void display_init(void) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

/*Code from Labwork*/
void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	
	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}

/*Code modified from Labwork*/
void display_marker(int line, char *s) {
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	textbuffer[line][15] = *s;
}

/*Code modified from Labwork*/
void display_score(char *s){
	int i;

	for(i = 0; i < 16; i++)
	if(*s) {
		textbuffer[1][10 + i] = *s;
		s++;
	}
}

/*Code from Labwork*/
void display_image(int x, const uint8_t *data) {
	int i, j;
	
	for(i = 0; i < 2; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 16; j++)
			spi_send_recv(~data[i*16 + j]);
	}
}

/*Code from Labwork*/
void display_textupdate(void) {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;
			
			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}

//Written by N Nguyen
void display_gameupdate(){
	int i, j, k;
	int display;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);	
		DISPLAY_CHANGE_TO_DATA_MODE;
		for (j = 0; j < 128; j++)
		{
			display = displaypixels[i*8][j];
			for (k = 0; k < 8; k++)
			{
				display |= displaypixels[i*8+k][j] << k;	
			}
			spi_send_recv(display);
		}
	}
}

/*Function to insert sprite in display pixels*/
//Written by N Nguyen
void insert_sprite(uint8_t * sprite, int x, int y, int lengthX, int lengthY){
	int i, j;
	int originalY = y;
	int originalX = x;
	for (i = 0; i < lengthY; i++, x = originalX)
	{
		y = originalY + i;
		for (j = 0; j < lengthX; j++, x++)
		{
			if(y < 0  || y > 32 || x < 0 || x >= 128){
				continue;
			}
			displaypixels[y][x] |= *((sprite+i*lengthX) + j);
		}
	}
}

//Written by N Nguyen
int collision_check(int x, int y, uint8_t const character[7][10]){
	int i, j;
	int originalY = y;
	int originalX = x;
	for (i = 0; i < 10; i++, x = originalX)
	{
		y = originalY + i;
		for (j = 0; j < 7; j++, x++)
		{
			if(y < 0  || y > 32 || x < 0 || x > 128){
				continue;
			}
			if (displaypixels[y][x] & character[i][j]){
				return 1;
			}
		}
	}
	return 0;
}

//Written by N Nguyen and P Patranik
void clear_display(){
	int i,j;
	for (i = 0; i < 32; i++)
	{
		for ( j = 0; j < 128; j++)
		{
			displaypixels[i][j] = 0;
		}
	}
	
}

//Written by N Nguyen and P Patranika
int OnButtonEnter(int button){
    static int onkey[3] = {0,0,0};
    int getbutton = getbtns();

	//BTN2
	if(getbutton & 0b001 && button == 2 && !onkey[0]){
        onkey[0] = 1;
        return 1;
    }
    else if(!(getbutton & 0b001) && button == 2 && onkey[0]){
        onkey[0] = 0;
    }

	//BTN3
	if(getbutton & 0b010 && button == 3 && !onkey[1]){
        onkey[1] = 1;
        return 1;
    }
    else if(!(getbutton & 0b010) && button == 3 && onkey[1]){
        onkey[1] = 0;
    }

	//BTN4
    if(getbutton & 0b100 && button == 4 && !onkey[2]){
        onkey[2] = 1;
        return 1;
    }
    else if(!(getbutton & 0b100) && button == 4 && onkey[2]){
        onkey[2] = 0;
    }

    return 0;
}

//Written by N Nguyen
void fill_pixels(uint8_t obstacle[32][11], int y){
	int i;
	for (i = 0; i < 11; i++)
	{
		obstacle[y][i] = 1;
	}
	
}

//Written by N Nguyen
void shrink_obstacles(int currentObstacles[]){
	int i,j,k;
	for (i = 0; i < 10; i++)
	{
		//if(i == currentObstacles[0] ||
		//   i == currentObstacles[1] || 
		//   i == currentObstacles[2] ||
		//   i == currentObstacles[3]){
		//	continue;
		//   }
		j = 0;
		int filledobstacle = 0;

		while (j < 32 && !filledobstacle)
		{
			switch (i)
			{
			case 0:
        	    if(obstacle1[j][0] == 0){
					fill_pixels(obstacle1, j);
					filledobstacle = 1;
				}
        	    break;
        	case 1:
        	    if(obstacle2[j][0] == 0){
					fill_pixels(obstacle2, j);
					filledobstacle = 1;
				}
        	    break;        
        	case 2:
        	    if(obstacle3[j][0] == 0){
					fill_pixels(obstacle3, j);
					filledobstacle = 1;
				}
        	    break;        
        	case 3:
        	    if(obstacle4[j][0] == 0){
					fill_pixels(obstacle4, j);
					filledobstacle = 1;
				}
        	    break;        
        	case 4:
        	    if(obstacle5[j][0] == 0){
					fill_pixels(obstacle5, j);
					filledobstacle = 1;
				}
        	    break;        
        	case 5:
        	    if(obstacle6[j][0] == 0){
					fill_pixels(obstacle6, j);
					filledobstacle = 1;
				}
        	    break;        
        	case 6:
        	    if(obstacle7[j][0] == 0){
					fill_pixels(obstacle7, j);
					filledobstacle = 1;
				}
        	    break;        
        	case 7:
        	    if(obstacle8[j][0] == 0){
					fill_pixels(obstacle8, j);
					filledobstacle = 1;
				}
        	    break;        
        	case 8:
        	    if(obstacle9[j][0] == 0){
					fill_pixels(obstacle9, j);
					filledobstacle = 1;
				}
        	    break;        
        	case 9:
        	    if(obstacle10[j][0] == 0){
					fill_pixels(obstacle10, j);
					filledobstacle = 1;
				}
        	    break;
			}
			j++;
		}
		
	}
	
}

/*Following code is taken from Labwork*/
static void num32asc( char * s, int n ) 
{
  int i;
  for( i = 28; i >= 0; i -= 4 )
    *s++ = "0123456789ABCDEF"[ (n >> i) & 15 ];
}

#define ITOA_BUFSIZ ( 24 )
char * itoaconv( int num )
{
  register int i, sign;
  static char itoa_buffer[ ITOA_BUFSIZ ];
  static const char maxneg[] = "-2147483648";
  
  itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
  sign = num;                           /* Save sign. */
  if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
  {
    for( i = 0; i < sizeof( maxneg ); i += 1 )
    itoa_buffer[ i + 1 ] = maxneg[ i ];
    i = 0;
  }
  else
  {
    if( num < 0 ) num = -num;           /* Make number positive. */
    i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
    do {
      itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
      num = num / 10;                   /* Remove digit from number. */
      i -= 1;                           /* Move index to next empty position. */
    } while( num > 0 );
    if( sign < 0 )
    {
      itoa_buffer[ i ] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return( &itoa_buffer[ i + 1 ] );
}

