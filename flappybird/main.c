#include <pic32mx.h>
#include <stdint.h>
#include "flappybird.h"

#define EEPROM_W 0b10100000
#define EEPROM_R 0b10100001

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
    display_textupdate();

    /*
    Following code is written by N Nguyen and P Patranika   
    */
	TRISDSET = 0xFE0;
	TRISECLR = 0xFF;

	PORTASET = 0xC000;
	
	T2CON = 0x0;
    TMR2 = 0x0;
	T2CON = 0x8070;

	//I2C
	double baud;

	I2C1CON = 0;
	I2C1BRG = 0xC2*2; //Baud Rate
	I2C1STAT = 0;

	I2C1CONSET = 0xA000; //1010 0000 0000 0000

    while (1)
    {
		T2CON = 0x8070;
		endGame = 1;
		while(endGame)
		{
			//Menu
			static int select = 0;
			display_string(0, "PLAY GAME");
			display_string(1, "SCOREBOARD");
			display_string(2, "HOW TO PLAY");
			display_string(3, "CREDITS");
			display_marker(select, "<");
			display_textupdate();

			if(OnButtonEnter(3)){
				select++;
				if(select == 4){
					select = 0;
				}
			}
			if(OnButtonEnter(2)){
				select--;
				if(select == -1){
					select = 3;
				}
			}
			if(OnButtonEnter(4)){
				if(select == 0){
					endGame = 0;
				}
				if(select == 1){
					//High Score
					uint8_t data;
					I2C_start();
					I2C_Write(EEPROM_W);
					I2C_Write(0x00);
					I2C_Write(0x00);
					I2C_Write(100);
					I2C_stop();

					I2C_start();
					I2C_Write(EEPROM_W);
					I2C_Write(0x00);
					I2C_Write(0x00);
					I2C_restart();
					I2C_Write(EEPROM_R);
					display_string(1, "999999999999");
					display_textupdate();
					data = I2C_Read();
					I2C_nack();
					I2C_stop();
					
					while(1){
						display_string(0, itoaconv(data));
						display_string(1, "999999999999");
						display_string(2, "999999999999");
						display_string(3, "999999999999");
						display_textupdate();
						if(OnButtonEnter(4)){
							break;
						}
					}
				}
				if(select == 2){
					while(1){
						display_string(0, "PRESS BUTTON 4");
						display_string(1, "TO FLAP AND");
						display_string(2, "AVOID OBSTACLES");
						display_string(3, "HAVE FUN!");
						display_textupdate();
						if(OnButtonEnter(4)){
							break;
						}
					}
				}
				if(select == 3){
					while(1){
						display_string(0, "MADE BY");
						display_string(1, "NEO NGUYEN");
						display_string(2, "AND");
						display_string(3, "PETER PATRANIKA");
						display_textupdate();
						if(OnButtonEnter(4)){
							break;
						}
					}
				}
			}
		}

		start(TMR2);
		while (!endGame)
		{
        	update();	
		}
		
		//Endgame screen
		char name[4] = "___\0";
		int nameCharacterSelect = 0;
		int characterSelect = 0;
		while(1){
			name[nameCharacterSelect] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[characterSelect];
			
			display_string(0, "   GAME OVER");
			display_string(1, "    SCORE:");
			display_score(itoaconv(PORTE));
			display_string(2, "ENTER YOUR NAME");
			display_string(3, name);

			display_textupdate();

			if(OnButtonEnter(3)){
				characterSelect++;
				if(characterSelect == 26){
					characterSelect = 0;
				}
			}
			if(OnButtonEnter(2)){
				characterSelect--;
				if(characterSelect == -1){
					characterSelect = 25;
				}
			}

			if(OnButtonEnter(4)){
				nameCharacterSelect++;
				characterSelect = 0;
				if(nameCharacterSelect == 3)
					break;
			}
		}
    }

    return 0;
}