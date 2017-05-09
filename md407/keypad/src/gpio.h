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
 
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "bool.h"

typedef volatile struct {
	uint32_t moder;
	uint16_t otyper;		// +0x4
	uint16_t otReserved;
	uint32_t ospeedr;		// +0x8
	uint32_t pupdr;			// +0xc
	union {
		uint8_t  idr[2];	// +0x10 +0x11
		struct {
			uint8_t idr_low;	// +0x10
			uint8_t idr_high;	// +0x11
		};
	};
	uint16_t idrReserved;
	union {
		uint8_t  odr[2];	// +0x14 +0x15
		struct {
			uint8_t odr_low;	// +0x14
			uint8_t odr_high;	// +0x15
		};
	};
	uint16_t odrReserved;
} GPIO;

#define GPIO_D (*((GPIO*) 0x40020C00))
#define GPIO_E (*((GPIO*) 0x40021000))

#define INDEX_LOW false
#define INDEX_HIGH true

void set8(int* p, bool index, uint8_t fix);
void set16(int* p, bool index, uint16_t fix);
void setModer(GPIO* port, bool index, uint16_t moder);
void setPupdr(GPIO* port, bool index, uint16_t pupdr);
void setOtyper(GPIO* port, bool index, uint8_t otyper);

#endif
