/* 
 * Copyright 2017 (C) Osvald Lindholm
 * 
 * This file is the result of the exercises provided
 * for the Maskinorienterad programmering (EDA487)
 * course at Chalmers. The exercises can be found at:
 * http://www.cse.chalmers.se/~uffe/MOP/hemuppgifter/hemuppgifter.html
 * 
 * This file is written on (and for) Windows, compiled
 * using the GCC with the language standard C99.
 * 
 */

#include <stdio.h>

// Function summary

/* 
 * Start of program!
 */
int main(int argc, char **argv) {
	
	/* 
	 * Exercise_1_1
	 * Create a foor-loop printing "I am an awesome C programmer" 10 times.
	 */
	printManyTimes("I am an awesome C programmer\n", 10);
	
}

/* 
 * Prints a message to the console multiple times.
 * 
 * @param str the message to be printed.
 * @param n the number of times to print the message.
 */
void printManyTimes(char str[], unsigned int n) {
	while (n > 0) {
		printf(str);
		n--;
	}
}
