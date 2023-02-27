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
void display_debug( volatile int * const addr )
{
  display_string( 1, "Addr" );
  display_string( 2, "Data" );
  num32asc( &textbuffer[1][6], (int) addr );
  num32asc( &textbuffer[2][6], *addr );
  display_textupdate();
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

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

void display_marker(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	textbuffer[line][15] = *s;
}

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
void insert_sprite(int x, int y, int lengthX, int lengthY, uint8_t const sprite[lengthY][lengthX]){
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
			displaypixels[y][x] |= sprite[i][j];
		}
	}
}

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

static void num32asc( char * s, int n ) 
{
  int i;
  for( i = 28; i >= 0; i -= 4 )
    *s++ = "0123456789ABCDEF"[ (n >> i) & 15 ];
}
