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
 
#include "bool.h"

/**
 * Returns true if false is passed, and false if true is passed.
 * This method is useful, as simply complimenting the bool like so, ~b.
 * might end in disasters.
 * 
 * False = 0; always. complimenting that will return 0xFF or a similiar value.
 * However, true = 1; complimenting that will return 0xFE or a similiar value.
 * Which is still interpreted as a true value, due it is not false.
 * 
 * @param b the bool to be negetad.
 * @return the opposite of the bool provided.
 */
bool negate(bool b) {
	return (b == false);
}
