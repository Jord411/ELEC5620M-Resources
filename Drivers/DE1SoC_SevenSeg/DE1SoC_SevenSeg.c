/*
 * DE1SoC_SevenSeg.c
 *
 *  Created on: 12 Feb 2021
 *      Author: Harry Clegg
 *  Updated on: 24 Feb 2024
 *      Author: David Cowell
 *      		You!
 */

#include "DE1SoC_SevenSeg.h"

// ToDo: Add the base addresses of the seven segment display peripherals.
volatile unsigned char *sevenseg_base_lo_ptr = (unsigned char *) 0xFF200020;
volatile unsigned char *sevenseg_base_hi_ptr = (unsigned char *) 0xFF200030;

// There are four HEX displays attached to the low (first) address.
#define SEVENSEG_N_DISPLAYS_LO 4

// Define each of the possible digits 0-9 and A-F
#define ZERO 0b0111111;
#define ONE 0b0000110;
#define TWO 0b1011011;
#define THREE 0b1001111;
#define FOUR 0b1100110;
#define FIVE 0b1101101;
#define SIX 0b1111101;
#define SEVEN 0b0000111;
#define EIGHT 0b1111111;
#define NINE 0b1101111;
#define LETTERA 0b1110111;
#define LETTERB 0b1111100;
#define LETTERC 0b0111001;
#define LETTERD 0b1011110;
#define LETTERE 0b1111001;
#define LETTERF 0b1110001;
#define DASH 0b1000000;

// There are two HEX displays attached to the high (second) address.
#define SEVENSEG_N_DISPLAYS_HI 2

void DE1SoC_SevenSeg_Write(unsigned int display, unsigned char value) {
    // Select between the two addresses so that the higher level functions
    // have a seamless interface.
    if (display < SEVENSEG_N_DISPLAYS_LO) {
        // If we are targeting a low address, use byte addressing to access
        // directly.
        sevenseg_base_lo_ptr[display] = value;
    } else {
        // If we are targeting a high address, shift down so byte addressing
        // works.
        display = display - SEVENSEG_N_DISPLAYS_LO;
        sevenseg_base_hi_ptr[display] = value;
    }
}

void DE1SoC_SevenSeg_SetSingle(unsigned int display, unsigned int value) {
    // ToDo: Write the code for driving a single seven segment display here.
    // Your function should turn a real value 0-F into the correctly encoded
    // bits to enable the correct segments on the seven segment display to
    // illuminate. Use the DE1SoC_SevenSeg_Write function you created earlier
    // to set the bits of the display.

	// Convert the input value from hexadecimal to the predefined digit binary values
	unsigned int digit = DASH;
	if (value == 0x0) {
		digit = ZERO;
	}
	else if (value == 0x1) {
		digit = ONE;
	}
	else if (value == 0x2) {
			digit = TWO;
		}
	else if (value == 0x3) {
			digit = THREE;
		}
	else if (value == 0x4) {
			digit = FOUR;
		}
	else if (value == 0x5) {
			digit = FIVE;
		}
	else if (value == 0x6) {
			digit = SIX;
		}
	else if (value == 0x7) {
			digit = SEVEN;
		}
	else if (value == 0x8) {
			digit = EIGHT;
		}
	else if (value == 0x9) {
			digit = NINE;
		}
	else if (value == 0xA) {
			digit = LETTERA;
		}
	else if (value == 0xB) {
			digit = LETTERB;
		}
	else if (value == 0xC) {
			digit = LETTERC;
		}
	else if (value == 0xD) {
			digit = LETTERD;
		}
	else if (value == 0xE) {
			digit = LETTERE;
		}
	else if (value == 0xF) {
			digit = LETTERF;
		}

	// Actually set the 7SEG display to the value assigned
	DE1SoC_SevenSeg_Write(display, digit);
}

void DE1SoC_SevenSeg_SetDoubleHex(unsigned int display, unsigned int value) {
    // ToDo: Write the code for setting a pair of seven segment displays
    // here. Good coding practice suggests your solution should call
    // DE1SoC_SevenSeg_SetSingle() twice.
    // This function should show the first digit of a HEXADECIMAL number on
    // the specified 'display', and the second digit on the display to
    // the left of the specified display.

    /** Some examples:
     *
     *    input | output | HEX(N+1) | HEX(N)
     *    ----- | ------ | -------- | ------
     *        5 |     05 |        0 |      5
     *       30 |     1E |        1 |      E
     *     0x60 |     60 |        6 |      0
     */

	// Set default state for out of range
	unsigned int least_significant_digit = DASH;
	unsigned int most_significant_digit = DASH;

	// Check to make sure value isn't out of range
	if (value <= 0xFF) {
		// Set most significant digit to floor division of value, and least significant digit to modulo division of value
		most_significant_digit = value/16;
		least_significant_digit = value%16;
	}

	// Write digits to display and display+1
	DE1SoC_SevenSeg_SetSingle(display, least_significant_digit);
	DE1SoC_SevenSeg_SetSingle(display + 1, most_significant_digit);
}

void DE1SoC_SevenSeg_SetDoubleDec(unsigned int display, unsigned int value) {
    // ToDo: Write the code for setting a pair of seven segment displays
    // here. Good coding practice suggests your solution should call
    // DE1SoC_SevenSeg_SetSingle() twice.
    // This function should show the first digit of a DECIMAL number on
    // the specified 'display', and the second digit on the display to
    // the left of the specified display.

    /** Some examples:
     *
     *	  input | output | HEX(N+1) | HEX(N)
     *    ----- | ------ | -------- | ------
     *        5 |     05 |        0 |      5
     *       30 |     30 |        3 |      0
     *     0x60 |     96 |        9 |      6
     */

	// Set default state for out of range
	unsigned int least_significant_digit = DASH;
	unsigned int most_significant_digit = DASH;

	// Check to make sure value isn't out of range
		if (value <= 99) {
			// Set most significant digit to floor division of value, and least significant digit to modulo division of value
			most_significant_digit = value/10;
			least_significant_digit = value%10;
		}

	// Write digits to display and display+1
		DE1SoC_SevenSeg_SetSingle(display, least_significant_digit);
		DE1SoC_SevenSeg_SetSingle(display + 1, most_significant_digit);
}
