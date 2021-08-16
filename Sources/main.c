/* Header file with all the essential definitions for a given type of MCU */
#include "MK60D10.h"
#include <string.h>

/* Macros for bit-level registers manipulation */
#define GPIO_PIN_MASK		0x1Fu
#define GPIO_PIN(x)			(((1)<<(x & GPIO_PIN_MASK)))

/* Constants specifying delay loop duration */
#define	DELAY_PIXEL_1		5
#define	DELAY_PIXEL_2		1
#define	DELAY_SHIFT_1		100
#define	DELAY_SHIFT_2		1
#define SHOW_DISPLAY_NUM	200					// Show same "picture" 100 times

/* Message limitation */
#define TEXT_MAX_LEN		100					// Maximal text lenght, spaces included
#define LETTER_WIDTH		5					// Width of each letter as display pixels
#define LETTER_HEIGHT		7					// Height of each letter as display pixels
#define LETTER_SPACING		1					// Letter space width as display pixels
#define PIXEL_MAP_MAX_LEN	TEXT_MAX_LEN * (LETTER_WIDTH + LETTER_SPACING)

/* Display constants */
#define DISPLAY_ROW_NUM		8					// Display height
#define DISPLAY_COL_NUM		16					// Display width
#define LETTER_COL_NUM		5					// Maximum letter width

/* Mapping buttons to specific port pins */
#define BTN_SW3 0x1000							// Port E, bit 12
#define BTN_SW5 0x4000000						// Port E, bit 26

/* Signals for 4-to-16 decoder to select column*/
#define A_SIGNAL_NUM		4					// Number of display coulumns activators
enum A_signals {
	A0 = 0,
	A1 = 1,
	A2 = 2,
	A3 = 3
};

/* Index of particular letter in letters matrix */
enum letters_index {
	A = 0,
	B = 7,
	C = 14,
	D = 21,
	E = 28,
	F = 35,
	G = 42,
	H = 49,
	I = 56,
	J = 63,
	K = 70,
	L = 77,
	M = 84,
	N = 91,
	O = 98,
	P = 105,
	Q = 112,
	R = 119,
	S = 126,
	T = 133,
	U = 140,
	V = 147,
	W = 154,
	X = 161,
	Y = 168,
	Z = 175,
	space = 182,
	dot = 189,
	exclamation = 196,
	question = 203,
	comma = 210
};

/* Pixel representation of each letter */
int pixel_letters[][LETTER_WIDTH] = {
	{0, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	
	{1, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 0},

	{0, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0},

	{1, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 0},
	
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 1, 1, 1, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 1, 1, 1, 1},

	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 1, 1, 1, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},

	{0, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 1, 1},
	{1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0},

	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},

	{0, 1, 1, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 1, 1, 0},

	{1, 1, 1, 1, 1},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0},

	{1, 0, 0, 0, 1},
	{1, 0, 0, 1, 0},
	{1, 0, 1, 0, 0},
	{1, 1, 0, 0, 0},
	{1, 0, 1, 0, 0},
	{1, 0, 0, 1, 0},
	{1, 0, 0, 0, 1},

	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 1, 1, 1, 1},

	{1, 0, 0, 0, 1},
	{1, 1, 0, 1, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},

	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 0, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 0, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},

	{0, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0},

	{1, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},

	{0, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 0, 1, 1},
	{0, 1, 1, 1, 1},

	{1, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},

	{0, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0},

	{1, 1, 1, 1, 1},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},

	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0},

	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},

	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 1, 0, 1, 1},
	{1, 0, 0, 0, 1},

	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},

	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},

	{1, 1, 1, 1, 1},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 1, 1, 1, 1},

	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	
	{1, 1, 1, 0, 0},
	{0, 0, 0, 1, 0},
	{0, 0, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0},
		
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0}
};

/* Row pin numbers */
unsigned int ROW[8] = { 26, 24, 9, 25, 28, 7, 27, 29 };

/* Matrix holds actual value of each pixel of display, whether is turned on or not */
int display[DISPLAY_ROW_NUM][DISPLAY_COL_NUM];

/* Matrix representing whole text as pixel values */
int pixel_text_matrix[DISPLAY_ROW_NUM][PIXEL_MAP_MAX_LEN];

/* Display shifting operational counters initialization */
int text_index = 0;								// Column index for pixel text matrix
int text_window_start = 0;						// Start column index of displaying window in pixel text matrix
int display_start_position = DISPLAY_COL_NUM;	// Actual colum pozition representing text begining(start from right)

/* Buttons controling variables */
int pressed_up = 0;								// Whether the button UP was pressed
int pressed_down = 0;							// Whether the button DOWN was pressed
int text_switched = 0;							// whether the text was switched

/* Array of text messages, index for array and Array for message from PuTTY */
char text[][TEXT_MAX_LEN] = {	
                    "DOBRY DEN,VITAM VAS!",
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ.",
                    "PRAVE STE NA SPAVE CISLO TRI.",
        	        "MATE DNES PEKNY DEN?"
                			};
int text_num = 0;

/* Configuration of the necessary MCU peripherals */
void system_config() {

	/* Turn on all port clocks */
	SIM->SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTE_MASK;

	/* Set corresponding PTA pins (column activators of 74HC154) for GPIO functionality */
	PORTA->PCR[8]  = ( 0|PORT_PCR_MUX(0x01) );	// A0
	PORTA->PCR[10] = ( 0|PORT_PCR_MUX(0x01) );	// A1
	PORTA->PCR[6]  = ( 0|PORT_PCR_MUX(0x01) );	// A2
	PORTA->PCR[11] = ( 0|PORT_PCR_MUX(0x01) );	// A3

	/* Set corresponding PTA pins (rows selectors of 74HC154) for GPIO functionality */
	PORTA->PCR[26] = ( 0|PORT_PCR_MUX(0x01) );	// R0
	PORTA->PCR[24] = ( 0|PORT_PCR_MUX(0x01) );	// R1
	PORTA->PCR[9]  = ( 0|PORT_PCR_MUX(0x01) );	// R2
	PORTA->PCR[25] = ( 0|PORT_PCR_MUX(0x01) );	// R3
	PORTA->PCR[28] = ( 0|PORT_PCR_MUX(0x01) );	// R4
	PORTA->PCR[7]  = ( 0|PORT_PCR_MUX(0x01) );	// R5
	PORTA->PCR[27] = ( 0|PORT_PCR_MUX(0x01) );	// R6
	PORTA->PCR[29] = ( 0|PORT_PCR_MUX(0x01) );	// R7

	/* Set corresponding PTE pins for GPIO functionality */
	PORTE->PCR[8]  = PORT_PCR_MUX(0x03);		// UART5_TX
    PORTE->PCR[9]  = PORT_PCR_MUX(0x03);		// UART5_RX
	PORTE->PCR[28] = ( 0|PORT_PCR_MUX(0x01) );	// #EN
    PORTE->PCR[12] = PORT_PCR_MUX(0x01);		// SW3 - Down	
    PORTE->PCR[26] = PORT_PCR_MUX(0x01);		// SW5 - Up

	/* Change corresponding PTA, PTE port pins as outputs */
	PTA->PDDR = GPIO_PDDR_PDD( 0x3F000FC0 );
	PTE->PDDR = GPIO_PDDR_PDD( GPIO_PIN(28) );

	/* Reset row values to 0 */
	PTA->PDOR = GPIO_PDOR_PDO( 0x00000000 );
}

/* Put value 0 to each position of the display matrix */
void display_init() {
	for (int r = 1; r < DISPLAY_ROW_NUM; r++) {
		for (int c = 0; c < DISPLAY_COL_NUM; c++) {
			display[r][c] = 0;					// 0 out whole matrix
		}
	}
}

/* Set default values to display shifting operational counters */
void animation_init() {
	text_index = 0;
	text_window_start = 0;
	display_start_position = DISPLAY_COL_NUM;
}

/* Variable delay loop */
void delay(int d1, int d2) {
	for(int i = 0; i < d1; i++) {
		for(int j = 0; j < d2; j++);
	}
}

/* Return pixel value of appropriate letter on appropriate position */
int letter_pixel_value(char letter, int row, int col) {
	switch(letter) {
		case 'A':	
			return pixel_letters[row + A][col];

		case 'B':	
			return pixel_letters[row + B][col];
		
		case 'C':	
			return pixel_letters[row + C][col];
		
		case 'D':	
			return pixel_letters[row + D][col];
		
		case 'E':	
			return pixel_letters[row + E][col];
		
		case 'F':	
			return pixel_letters[row + F][col];
		
		case 'G':	
			return pixel_letters[row + G][col];
		
		case 'H':	
			return pixel_letters[row + H][col];
		
		case 'I':	
			return pixel_letters[row + I][col];
		
		case 'J':	
			return pixel_letters[row + J][col];
		
		case 'K':	
			return pixel_letters[row + K][col];

		case 'L':	
			return pixel_letters[row + L][col];
		
		case 'M':	
			return pixel_letters[row + M][col];
		
		case 'N':	
			return pixel_letters[row + N][col];
		
		case 'O':	
			return pixel_letters[row + O][col];
		
		case 'P':	
			return pixel_letters[row + P][col];
		
		case 'Q':	
			return pixel_letters[row + Q][col];
		
		case 'R':	
			return pixel_letters[row + R][col];
		
		case 'S':	
			return pixel_letters[row + S][col];
		
		case 'T':	
			return pixel_letters[row + T][col];
		
		case 'U':	
			return pixel_letters[row + U][col];
		
		case 'V':	
			return pixel_letters[row + V][col];
		
		case 'W':	
			return pixel_letters[row + W][col];

		case 'X':	
			return pixel_letters[row + X][col];
		
		case 'Y':	
			return pixel_letters[row + Y][col];
		
		case 'Z':	
			return pixel_letters[row + Z][col];
		
		case ' ':	
			return pixel_letters[row + space][col];
		
		case '.':	
			return pixel_letters[row + dot][col];
		
		case '!':	
			return pixel_letters[row + exclamation][col];
		
		case '?':	
			return pixel_letters[row + question][col];
		
		case ',':	
			return pixel_letters[row + comma][col];
	}
}

/* Convert text message to pixel matrix and return lenght of pixel text matrix */
int text_to_pixel_map(char *text, int lenght) {
	int col_index = 0;
	
	/* Loop throught all characters in text */
	for (int i = 0; i < lenght; i++) {
		/* Loop throught all rows except row 0 */
		for (int r = 1; r < DISPLAY_ROW_NUM; r++) {
			/* Set column index value for next row of the same letter*/
			col_index = i * (LETTER_WIDTH + LETTER_SPACING);

			/* Copy one letter row into pixel matrix row */
			for (int c = 0; c < LETTER_WIDTH; c++) {
				pixel_text_matrix[r][col_index++] = letter_pixel_value(*text, r - 1, c);	// Letter starts from row 1
			}
			pixel_text_matrix[r][col_index++] = 0;	// Space after letter
		}
		text += sizeof(char);						// Pointer to next char
	}
	/* Return matrix lenght */
	return col_index;
}

/* 0 out all pixels */
void clear_pixel_text_matrix() {
	for(int r = 1; r < DISPLAY_ROW_NUM; r++) {
		for (int c = 0; c < PIXEL_MAP_MAX_LEN; c++) {
			pixel_text_matrix[r][c] = 0;
		}
	}
}

/* Set one display "picture" from text pixel map */
void set_display(int pixel_map_len) {
	for(int r = 1; r < DISPLAY_ROW_NUM; r++) {
		for (int i = 0; i < DISPLAY_COL_NUM; i++) {
			/* Whether the letters should be started displaying */
			if (i >= display_start_position) {
				/* Offset to text window start index */
				text_index = i - display_start_position;
				display[r][i] = pixel_text_matrix[r][text_window_start + text_index];
			}
		}
	}
	(display_start_position == 0) ? text_window_start++ : display_start_position--;
	
	/* End of text, counters reset */
	if (text_window_start == pixel_map_len) {
		text_window_start = 0;
		display_start_position = DISPLAY_COL_NUM;
	}
}

/* For corresponding row set output to 1  */
void activate_row(unsigned int row_selected) {
	for (int i = 0; i < DISPLAY_ROW_NUM; i++) {
		if (i == row_selected) {
			PTA->PDOR |= GPIO_PDOR_PDO( GPIO_PIN(ROW[i]));
			continue;
		}
		PTA->PDOR &= ~GPIO_PDOR_PDO( GPIO_PIN(ROW[i]));
	}
}

/* For corresponding row set output to 0  */
void deacticate_row(unsigned int row_selected) {
	PTA->PDOR &= ~GPIO_PDOR_PDO( GPIO_PIN(ROW[row_selected]));
}

/* Conversion of requested column number into the 4-to-16 decoder control */
void column_select(unsigned int col_num) {
	unsigned i, result, col_sel[4];

	for (i = 0; i < A_SIGNAL_NUM; i++) {
		result = col_num / 2;	  // Whole-number division of the input number
		col_sel[i] = col_num % 2;
		col_num = result;
		// Signal selection
		switch(i) {
		    case A0:
				((col_sel[i]) == 0) ? (PTA->PDOR &= ~GPIO_PDOR_PDO( GPIO_PIN(8))) : (PTA->PDOR |= GPIO_PDOR_PDO( GPIO_PIN(8)));
				break;

			case A1:
				((col_sel[i]) == 0) ? (PTA->PDOR &= ~GPIO_PDOR_PDO( GPIO_PIN(10))) : (PTA->PDOR |= GPIO_PDOR_PDO( GPIO_PIN(10)));
				break;

			case A2:
				((col_sel[i]) == 0) ? (PTA->PDOR &= ~GPIO_PDOR_PDO( GPIO_PIN(6))) : (PTA->PDOR |= GPIO_PDOR_PDO( GPIO_PIN(6)));
				break;

			case A3:
				((col_sel[i]) == 0) ? (PTA->PDOR &= ~GPIO_PDOR_PDO( GPIO_PIN(11))) : (PTA->PDOR |= GPIO_PDOR_PDO( GPIO_PIN(11)));
				break;
		}
	}
}

/* Turn on appropriate pixels based on actual values in matrix "display" */
void show_display() {
	/* Increase text intensity by showing the same "picture" more times */
	for (int i = 0; i < SHOW_DISPLAY_NUM; i++) {
		/* Lighting up columns */
		for (int c = 0; c < DISPLAY_COL_NUM; c++) {
			column_select(c);
			/* Lighting up appropriate rows of actual collum */
			for (int r = 1; r < DISPLAY_ROW_NUM; r++) {
				if (display[r][c] == 1) {
					activate_row(r);
					delay(DELAY_PIXEL_1, DELAY_PIXEL_2);
					deacticate_row(r);
				}
			} 
		}
	}
	delay(DELAY_SHIFT_1, DELAY_SHIFT_2);					// Wait before display shifting
}

/* Main function */
int main(void) {

	system_config();
	display_init();
	
	int pixel_map_len = text_to_pixel_map(text[text_num], strlen(text[text_num]));

	/* Infinity loop */
    for (;;) {

		/* Implicitly show first text message*/
		if (!text_switched) {
			set_display(pixel_map_len);
			show_display();
		}
		else {
			display_init();
			clear_pixel_text_matrix();
			pixel_map_len = text_to_pixel_map(text[text_num], strlen(text[text_num]));
			set_display(pixel_map_len);
			show_display();
		}

		/* Pressing the UP button decrease the text message index */
		if (!pressed_up && !(GPIOE_PDIR & BTN_SW5)) {
            pressed_up = 1;
            text_num == 0 ? text_num = 3 : text_num--;		// Create index loop
			text_switched = 1;
			animation_init();
        }
        else if (GPIOE_PDIR & BTN_SW5) {
			pressed_up = 0;
		}

        /* Pressing the down button increases the text message index */
        if (!pressed_down && !(GPIOE_PDIR & BTN_SW3)) {
            pressed_down = 1;
            text_num == 3 ? text_num = 0 : text_num++;		// Create index loop
			text_switched = 1;
			animation_init();
        }
        else if (GPIOE_PDIR & BTN_SW3) {
			pressed_down = 0;
		}
    }
}
