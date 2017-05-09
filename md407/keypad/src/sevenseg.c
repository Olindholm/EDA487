/*
 * Copyright 2017 (C) Osvald Lindholm
 *
 * This file is the result of the lab excercises provided
 * for the Maskinorienterad programmering (EDA407)
 * course at Chalmers. The lab exercises can be found at:
 * http://www.cse.chalmers.se/edu/year/2017/course/EDA482_7/Documents/LabPM-MOP-2017-02-18.pdf
 *
 * This file is written for the MD407 lab computer
 * using an ARM V6-m processor.
 * Detailed specficiations can be found at:
 * http://www.cse.chalmers.se/edu/resources/mop/documents/MD407_beskrivning.pdf
 * http://www.cse.chalmers.se/edu/year/2017/course/EDA482_7/Documents/quickguide-mop.pdf
 *
 */
 
#include "sevenseg.h"

/**
 * Inits a sevenseg at the given port and index.
 * 
 * @param port the port which the sevenseg is to be initated on.
 * @param index the port which the index is to be initated on.
 * @param display_error whether the sevenseg should display an E. (error) when given a fauly value.
 * @return the sevenseg.
 */
SEVENSEG sevenseg_create(GPIO* port, bool index, bool display_error) {
	SEVENSEG sevenseg = {
		port,
		index,
		display_error,
		sevenseg_init,
		sevenseg_display
	};
	
	sevenseg.init(&sevenseg);
	return sevenseg;
}

void sevenseg_init(SEVENSEG* sevenseg) {
	
	// Configure the all 8 bits to output
	gpio_set_moder(sevenseg->port, sevenseg->index, 0x5555);
}

 /**
  * Displays the given number on the sevenseg.
  * 
  * Numbers out of range will either display an E. (error)
  * or nothing at all, depending on the sevenseg's specifications.
  * 
  * @param sevenseg the sevenseg to display the byte.
  * @param b a number from 0-15 (0-F hexadecimal).
  */
void sevenseg_display(SEVENSEG* sevenseg, unsigned char b) {
	sevenseg->port->odr[sevenseg->index] = sevenseg_get_code(b, sevenseg->display_error);
}

static const unsigned char sevenseg_codes[] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x67, // 9
	0x77, // A
	0x7C, // b
	0x39, // C
	0x5E, // d
	0x79, // E
	0x71, // F
};

/**
 * Returns the sevenseg code for a number.
 * 
 * @param b a number from 0-15 (0-F hexadecimal).
 * @param displayError whether to return E. (error) when given a fauly value.
 * @return a code for a sevenseg display, representing the number provided.
 */
unsigned char sevenseg_get_code(unsigned char b, bool displayError) {
	if (b > 15) {
		if (displayError) {
			return 0xF9; // code for E. (error)
		}
		else {
			return 0x00;
		}
	}
	
	return sevenseg_codes[b];
}