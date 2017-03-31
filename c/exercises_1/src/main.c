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
#include <windows.h>
#include <math.h>

// Function summary
void printManyTimes(char str[], unsigned int n);
void printBackwards(char str[]);
void printByte(unsigned char b);
void printBytes(unsigned long long l, int n);
void printShort(unsigned short s);
void printInt(unsigned int i);
unsigned char binaryToDecimal(char str[]);
unsigned long long rotateRight(unsigned long long l, int n);
unsigned long long rotateLeft(unsigned long long l, int n);
void clearScreen();
void printSpaces(int x);
void printLinebreaks(int y);

// Constant Variables
#define WIDTH 6						// The width of window is 2^(WIDTH-1);
#define HEIGHT 4					// -- || --

#define MILLIS_SLEEP_PER_TICK 100	// Sleep (milliseconds) per tick
#define TICKS_PER_SHIFT 4
#define TICKS_PER_MOVE 2			// Good idea is to name these TICKS_PER_X_MOVE
#define TICKS_PER_JUMP 3			// and TICKS_PER_Y_MOVE respectively

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
	//printByte(128);		printf("\n");
	//printShort(30345);	printf("\n");
	//printInt(65987);	printf("\n");
	 
	/* 
	 * Exercise_1_3b
	 * Create a function printing a binary number as a decimal.
	 */
	 //printf("%i", binaryToDecimal("10010001"));
	 
	/* 
	 * Exercise_1_3f
	 * Create a program rendering a bit pattern.
	 * 
	 * Exercise_1_3h
	 * Render the bit pattern left and right.
	 * 
	 * Exercise_1_3i
	 * Render the bit pattern up and down.
	 */
	unsigned short a = 0b1000000000000000;
	unsigned short b = 0b0000000000000001;
	unsigned int x = 0, y = 0;
	
	unsigned long currentTick = 0;
	
	// Run program forever
	while (1) {
		clearScreen();
		
		// Perform operations (such as patterns)
		if (currentTick % TICKS_PER_SHIFT == 0) {
			a = rotateRight(a, sizeof(a));
			b = rotateLeft(b, sizeof(b));
		}
		
		// Calculate position
		if (currentTick % TICKS_PER_MOVE == 0) x = (x+1) % (int) pow(2, WIDTH);
		if (currentTick % TICKS_PER_JUMP == 0) y = (y+1) % (int) pow(2, HEIGHT);
		
		/* 
		 * *Sign is the first bit of the x/y position.
		 * It determines the direction we're moving,
		 * similiarly how the first bit determines if
		 * a number is negative or not in a signed number.
		 */
		char xSign = x >> (WIDTH-1);
		int widthOffset = pow(2, WIDTH) * xSign;
		
		char ySign = y >> (HEIGHT-1);
		int heightOffset = pow(2, HEIGHT) * ySign;
		
		// Render
		printLinebreaks(heightOffset + (y * (int) pow(-1, ySign)));
		printSpaces(widthOffset + (x * (int) pow(-1, xSign)));
		printShort(a | b);
		
		// Wait
		Sleep(MILLIS_SLEEP_PER_TICK);
	}
	 
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

/* 
 * Interprets a string as a byte and returns it.
 * If the string provided is shorter or longer
 * than a byte, zero will be returned.
 * 
 * Interprets the zero character a LOW bit
 * and all others as a HIGH bit.
 * 
 * @param str the string of bits to be interpreted.
 * 
 * @return a byte equal to the bits of the string.
 */
unsigned char binaryToDecimal(char str[]) {
	unsigned char byte = 0;
	
	// Confirms the length of the string.
	if (strlen(str) == BYTE_LENGTH) {
		
		/* 
		 * Interprets the character as LOW bit if
		 * it's equal to zero, otherwise HIGH.
		 * 
		 * Performing an OR operation with the byte
		 * after shifting all it's bits one step to
		 * the left, garantueeing no overrides as well
		 * as the right position for each bit after
		 * full operation has compelted.
		 */
		for (int i = 0; i < BYTE_LENGTH; i++) {
			byte = (byte << 1 | (str[i] != '0'));
		}
	}
	
	return byte;
}

/* 
 * Rotates all bits to the right, given a size.
 * 
 * @param l the bits to be rotated.
 * @param n the number of bytes to be rotated.
 * 
 * @return the bits (now rotated to the right)
 */
unsigned long long rotateRight(unsigned long long l, int n) {
	/* 
	 * Shifts the bits to the left, followed by
	 * an OR operation with the bit that has
	 * been shifted out (called carry).
	 * 
	 * The bit shifted out is calculated by
	 * performing an AND operation on the bits
	 * (before shifted), saving the carry only
	 * if the carry position was HIGH.
	 * 
	 * Carry position would be the first or the
	 * last bit, depending on the direction rotating.
	 * (see rotateLeft(..) )
	 */
	return (l >> 1) | ((l & 1) << (n*8-1));
}

/* 
 * Rotates all bits to the left, given a size.
 * 
 * @param l the bits to be rotated.
 * @param n the number of bytes to be rotated.
 * 
 * @return the bits (now rotated to the left)
 */
unsigned long long rotateLeft(unsigned long long l, int n) {
	/* 
	 * Shifts the bits to the left, followed by
	 * an OR operation with the bit that has
	 * been shifted out (called carry).
	 * 
	 * The bit shifted out is calculated by
	 * performing an AND operation on the bits
	 * (before shifted), saving the carry only
	 * if the carry position was HIGH.
	 * 
	 * Carry position would be the first or the
	 * last bit, depending on the direction rotating.
	 * (see rotateRight(..) )
	 */
	return (l << 1) | ((l & (1 << (n*8-1))) >> (n*8-1));
}

/* 
 * Clears the console window.
 * Seems only to work on Windows and Linux.
 */
void clearScreen() {
	system("@cls||clear");
}

/* 
 * Prints a number of spaces into the console.
 * (good for offsets)
 * (see printLinebreaks(..) )
 * 
 * @param x number of spaces to printed.
 */
void printSpaces(int x) {
	while (x-- > 0) {
		printf(" ");
	}
}

/* 
 * Prints a number of linebreaks into the console.
 * (good for offsets)
 * (see printSpaces(..) )
 * 
 * @param y number of linebreaks to printed.
 */
void printLinebreaks(int y) {
	while (y-- > 0) {
		printf("\n");
	}
}
