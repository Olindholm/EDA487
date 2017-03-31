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
void printByte(unsigned char b);
void printBytes(unsigned long long l, int n);
void printShort(unsigned short s);
void printInt(unsigned int i);

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
	 //printBackwards("This text is pretty hard to read");
	 
	 /* 
	 * Exercise_1_3a
	 * Create a function printing a byte, short and int bitwise to the console.
	 */
	printByte(128);		printf("\n");
	printShort(30345);	printf("\n");
	printInt(65987);	printf("\n");
	
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

#define BYTE_LENGTH 8

/* 
 * Prints a byte to the console bitwise in ones and zeroes.
 * 
 * @param b the byte to be printed.
 */
void printByte(unsigned char b) {
	
	/* 
	 * Shifts each bit of the byte to most-right bit position,
	 * starting with the most-left bit. Followed by nullifying
	 * all other bits and printing the result. Repeated for
	 * each bit.
	 */
	for (int i = 0; i < BYTE_LENGTH; i++) {
		int bit = (b >> (BYTE_LENGTH - (i+1))) & 0x01;
		printf("%d", bit);
	}
}

/* 
 * Prints to the console a number of bytes.
 * 
 * @param l the bytes consecutively.
 * @param n the number of bytes to be printed.
 */
void printBytes(unsigned long long l, int n) {
	
	/* 
	 * Shifting a byte of bits to the most-right position,
	 * allows printing for that specific byte.
	 * 
	 * We can thus print shorts, and ints easily by specifying
	 * their lengths by byte, that being 2 and 4 respectively.
	 * (see printShort(..) and printInt(..) )
	 */
	while (n > 0) {
		n--;
		printByte((l >> n * BYTE_LENGTH));
	}
}

/* 
 * Prints a short to the console bitwise in ones and zeroes.
 * 
 * @param s the short to be printed.
 */
void printShort(unsigned short s) {
	printBytes(s, sizeof(s));
}

/* 
 * Prints an int to the console bitwise in ones and zeroes.
 * 
 * @param i the int to be printed.
 */
void printInt(unsigned int i) {
	printBytes(i, sizeof(i));
}
