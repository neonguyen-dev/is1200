/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */

void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_textupdate(void);
void display_gameupdate(void);
uint8_t spi_send_recv(uint8_t data);

/*Display debug*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
extern uint8_t displaypixels[32][128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of asm lab: delay, time2string */
void delay(int);
void time2string( char *, int );
char * itoaconv( int num );

/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);

/*The following header info is written by N Nguyen and P Patranika*/
/*Essential game functions*/
void insert_sprite(uint8_t * sprite, int x, int y, int lengthX, int lengthY);
void clear_display(void);
int collision_check(int x, int y, uint8_t const sprite[7][10]);
int OnButtonEnter(int button);
void shrink_obstacles(int currentObstacles[]);

/*Menu functions*/
void display_marker(int line, char *s);
void display_score(char *s);

/*Sprites*/
extern uint8_t const character[7][10];

extern uint8_t obstacle1[32][11];
extern uint8_t obstacle2[32][11];
extern uint8_t obstacle3[32][11];
extern uint8_t obstacle4[32][11];
extern uint8_t obstacle5[32][11];
extern uint8_t obstacle6[32][11];
extern uint8_t obstacle7[32][11];
extern uint8_t obstacle8[32][11];
extern uint8_t obstacle9[32][11];
extern uint8_t obstacle10[32][11];

/*Control variables*/
int endGame;
int currentGap;
int filledobstacle;

/*I2C functions*/
void I2C_idle(void);
void I2C_start(void);
void I2C_stop(void);
void I2C_restart(void);
void I2C_ack(void);
void I2C_nack(void);
int I2C_Write(uint8_t data);
uint8_t I2C_Read();

/*highscores*/
char highscores[4][16];
void store_highscore(char * name, int value);