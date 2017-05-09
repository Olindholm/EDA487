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

#include "keypad.h"
#include "sevenseg.h"

void startup(void) __attribute__((naked)) __attribute__( (section(".start_section")) );

void startup ( void ) {
	asm volatile(
		" LDR R0,=0x2001C000\n"		/* set stack */
		" MOV SP,R0\n"
		" BL main\n"				/* call main */
		".L1: B .L1\n"				/* never return */
	) ;
}

int main() {
	
	// Setting the sevenseg and keypad to opposite indicies (high / low)
	bool sevenseg_index = INDEX_LOW;
	bool keypad_index = negate(sevenseg_index);
	
	// Setting both the sevenseg display and keypad to the same GPIO port
	KEYPAD keypad = keypad_create(&GPIO_D, keypad_index);
	SEVENSEG sevenseg = sevenseg_create(&GPIO_D, sevenseg_index, false);
	
	while (true) {
		char c = keypad.scan(&keypad);
		sevenseg.display(&sevenseg, c);
	}
}
