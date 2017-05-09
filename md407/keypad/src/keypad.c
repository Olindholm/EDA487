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

/**
 * Inits a keypad at the given port and index.
 * 
 * OBS! GPIO_D port with INDEX_LOW will not work properly.
 * After extended debugging no reason was found.
 * 
 * @param port the port which the keypad is to be initated on.
 * @param index the port which the index is to be initated on.
 * @return the keypad.
 */
KEYPAD keypad_create(GPIO* port, bool index) {
	KEYPAD keypad = {
		port,
		index,
		keypad_init,
		keypad_scan
	};
	
	keypad.init(&keypad);
	return keypad;
}

void keypad_init(KEYPAD* keypad) {
	
	// Configure the first 4 bits (b0-b3) to input and the rest (b4-b7) to ouput
	gpio_set_moder(keypad->port, keypad->index, 0x5500);
	
	// Configure the first 4 bits (b0-b3) to pull-down
	gpio_set_pupdr(keypad->port, keypad->index, 0x00AA);
	
	// Configure the bits to push-pull
	gpio_set_otyper(keypad->port, keypad->index, 0x00);
	
}

static const unsigned char keypad_values[] = {
	1, 2, 3, 10,
	4, 5, 6, 11,
	7, 8, 9, 12,
	14, 0, 15, 13
};

/**
 * Scans the keypad for any presses.
 * 
 * @param keypad the keypad to be scanned.
 * @return the value of the key pressed, or -1 if no key is pressed.
 */
char keypad_scan(KEYPAD* keypad) {
	for (int r = 0; r < 4; r++) {
		
		keypad_enable_row(keypad, r);
		int c = keypad_detect_column(keypad);
		
		if (c != -1) {
			return keypad_values[4*r+c];
		}
	}
	
	return -1;
}

void keypad_enable_row(KEYPAD* keypad, int r) {
	keypad->port->odr[keypad->index] = (0x10 << r);
}

int keypad_detect_column(KEYPAD* keypad) {
	unsigned char byte = keypad->port->idr[keypad->index];
	
	for (int c = 0; c < 4; c++) {
		unsigned char d = (byte & (1 << c));
		
		if (d != 0) {
			return c;
		}
	}
	
	return -1;
}
