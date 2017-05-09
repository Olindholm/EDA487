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
 
#ifndef SEVENSEG_H
#define SEVENSEG_H

#include "gpio.h"
#include "bool.h"

typedef struct SEVENSEG_STRUCT {
	GPIO* port;
	bool index; // low (0) or high (1) byte
	bool display_error;
	void (*init) (struct SEVENSEG_STRUCT* sevenseg);
	void (*display) (struct SEVENSEG_STRUCT* sevenseg, unsigned char b);
} SEVENSEG;

SEVENSEG sevenseg_create(GPIO* port, bool index, bool display_error);

void sevenseg_init(SEVENSEG* sevenseg);
void sevenseg_display(SEVENSEG* sevenseg, unsigned char b);

unsigned char sevenseg_get_code(unsigned char b, bool displayError);

#endif
