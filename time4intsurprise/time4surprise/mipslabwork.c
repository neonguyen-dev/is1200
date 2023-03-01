/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
 
int prime = 1234567;

int mytime = 0x5957;

int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";


/* Interrupt Service Routine */
void user_isr( void )
{
  //check interrupt status for SW1
  if(IFS(0) & 0x080){
    PORTE += 1;
    IFSCLR(0) = 0x080;
  }

  if(IFS(0) & 0x100){
    timeoutcount += 1;
    IFSCLR(0) |= 0x100; //reset the interupt condition
  }
  
  if(timeoutcount == 10){
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    timeoutcount = 0;
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  TRISE = 0;
  T2CON = 0x0;
  TMR2 = 0x0;
  PR2 = (80000000 / 256) / 10;
  
  INTCONSET = 0x2; //new line 0010

  T2CON = 0x8070;
  
  //Set priority for interrupt
  IPCSET(2) = 0x1f;
  IPCSET(1) = 0x1f000000; //new line //0001 1111 0000 0000 0000 0000 0000 0000

  //enable interrupt
  IECSET(0) = 0x180; // 0001 1000 0000
  
  IFSCLR(0) = 0x180; // new line

  volatile int * trise = (volatile int *) 0xbf886100;
  *trise &= 0xFFFFFF00;

  enable_interrupt();

  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  prime = nextprime( prime );
  display_string( 0, itoaconv( prime ) );
  display_update();
}
