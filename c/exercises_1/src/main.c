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
#include <string.h>

// Function summary
void printManyTimes(char str[], unsigned int n);
void printBackwards(char str[]);

/* 
 * Start of program!
 */
int main(int argc, char **argv) {
	
	/* 
	 * Exercise_1_1
	 * Create a foor-loop printing "I am an awesome C programmer" 10 times.
	 */
	//printManyTimes("I am an awesome C programmer\n", 10);
	
	/* 
	 * Exercise_1_2
	 * Create a string and print it backawards.
	 */
	 printBackwards("This text is pretty hard to read");
	 
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

/* 
 * Prints a string backwards to the console.
 * 
 * @param str the string to be printed.
 */
void printBackwards(char str[]) {
	int length = strlen(str);
	
	/* 
	 * strlen(str) returns only the length of the string.
	 * The string also needs to be exited with a null character
	 * at the end. Thus, (length + 1).
	 */
	char rts[length + 1];
	rts[length] = '\0';
	
	/*
	 * Loops through the str, inserting each character
	 * into rts, backwards of course.
	 */
	for (int i = 0; i < length; i++) {
		rts[length - (i+1)] = str[i];
	}
	
	printf("%s\n", rts);
}
