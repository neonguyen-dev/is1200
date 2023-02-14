#include <pic32mx.h>
#include <stdint.h>
#include "flappybird.h"

#define TMR2PERIOD ((80000000 / 256))

int main(){
    /*
      Following code is written 2015 by Axel Isaksson,
      modified 2015, 2017 by F Lundevall

	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

    display_init();
    display_update();

    /*
    Following code is written by N Nguyen and P Patranika   
    */

    //Start timer
    T2CON = 0x0;
    TMR2 = 0x0;
    PR2 = TMR2PERIOD;

    T2CON = 0x8070; //start the timer, reference to timer sheet
    
    //Enable interrupts with highest priority
    IPCSET(2) = 0x1f;
    IECSET(0) = 0x100;

    start();

    while (1)
    {
        if(IFS(0) & 0x100){
            IFSCLR(0) = 0x100;
            update();
            display_update();
        }
    }
    

    return 0;
}