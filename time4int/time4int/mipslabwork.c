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

int mytime = 0x5957;

int count = 0;

char textstring[] = "text, more text, and even more text!";


/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  T2CON = 0x0;
  TMR2 = 0x0;
  PR2 = (80000000 / 256) / 10;

  T2CON = 0x8070; //start the timer, reference to timer sheet

  volatile int * trise = (volatile int *) 0xbf886100;
  *trise &= 0x0; //1111 1111 1111 0001
  
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  TRISD |= 0x2; 
  volatile int * porte = (volatile int *) 0xbf886110;
  int button = getbtns();
  int switches = getsw();

  if(IFS(0) & 0x100){
    count += 1;
    IFSCLR(0) = 0x100; //reset the interupt condition
  }
  
  if(count == 10){
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    *porte += 1;
    count = 0;
  }

  display_image(96, icon);

  //delay( 1000 );


  //check b2
  if((button & 0b001) == 1){
    mytime &= 0xff0f;
    mytime |= (switches << 4); 
  }

  if((button & 0b010) == 2){
    mytime &= 0xf0ff;
    mytime |= (switches << 8); 
  }

  if((button & 0b100) == 4){
    mytime &= 0x0fff;
    mytime |= (switches << 12); 
  }

}
