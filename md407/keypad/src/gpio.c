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
 
#include "gpio.h"

void set8(int* p, bool high, uint8_t fix) {
	*p = (*p & (0xFF00 >> 2*4*high)) | (fix << 2*4*high);
}

void set16(int* p, bool high, uint16_t fix) {
	*p = (*p & (0xFFFF0000 >> 4*4*high)) | (fix << 4*4*high);
}

void gpio_set_moder(GPIO* port, bool high, uint16_t moder) {
	set16(&port->moder, high, moder);
}

void gpio_set_pupdr(GPIO* port, bool high, uint16_t pupdr) {
	set16(&port->pupdr, high, pupdr);
}

void gpio_set_otyper(GPIO* port, bool high, uint8_t otyper) {
	set8(&port->otyper, high, otyper);
}
