/*
 * Copyright 2017 (C) Osvald Lindholm
 *
 * This file is the result of the exercises provided
 * for the Maskinorienterad programmering (EDA487)
 * course at Chalmers. The exercises can be found at:
 * http://www.cse.chalmers.se/~uffe/MOP/hemuppgifter/hemuppgifter-forel2.html
 *
 * This file is written on (and for) Windows, compiled
 * using the GCC with the language standard C99.
 *
 */

#include "renderer.h"
#include <stdio.h>
#include <math.h>

// Function summary
void close();

// Constant Variables
#define WIDTH 800
#define HEIGHT 600
#define CENTER_WIDTH (WIDTH/2)
#define CENTER_HEIGHT (HEIGHT/2)

#define TICK_RATE 0.25

// Global resources
GfxObject ship, background;

int backgroundRotation = 0;

int main( int argc, char* args[] ) {
	// If you want the program to not launch the terminal, then go to
	// Project->Settings->General->"This program is a GUI application" and uncheck that flag.
	
	// Start up SDL and create window of width=800, height = 600
	initRenderer(WIDTH, HEIGHT);
	
	// Create an object
	ship = createGfxObject(  "../ship.png" );
	ship.outputWidth  = 200;
	ship.outputHeight = 200;
	
	// Loading background resource
	background = createGfxObject(  "../background.jpg" );
	background.outputWidth  = WIDTH;
	background.outputHeight = HEIGHT;
	
	// The real-time loop
	while(true) {
		// Handle events on the inqueue (e.g., mouse events)
		SDL_Event e;  //Event handler
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {   //User requests quit
				close();
				exit(0);
			}
		}
		
		// Clear screen with a grey background color, red=0x33, blue=0x33, green=0x33, alpha=0xff. 0=minimum, 0xff=maximum.
		// Alpha is transparency: 0 = fully transparent, 0xFF = fully opaque. However, actual use of transparency requires further settings.
		SDL_SetRenderDrawColor( gRenderer, 0x33, 0x33, 0x33, 0xFF );
		SDL_RenderClear( gRenderer );
		
		// Calculations (such as rotation of background etc.)
		backgroundRotation = (backgroundRotation+1) % (int) (360/TICK_RATE);
		int angle = backgroundRotation*TICK_RATE;
		
		// Render our object(s) - background objects first, and then forward objects (like a painter)
		renderGfxObject(&background, CENTER_WIDTH, CENTER_HEIGHT, angle, 1.0f);
		renderGfxObject(&ship, CENTER_WIDTH, CENTER_HEIGHT, 0, 1.0f);
		renderText("Hello World!", 300, 150);
		
		// This function updates the screen and also sleeps ~16 ms or so (based on the screen's refresh rate),
		// because we used the flag SDL_RENDERER_PRESENTVSYNC in function initRenderer()
		SDL_RenderPresent( gRenderer );
	}
	
	close(); //Free allocated resources
	return 0;
}

void close() {
	//Preferably, you should free all your GfxObjects, by calls to freeGfxObject(GfxObject* obj), but you don't have to.
	freeGfxObject(&ship);
	freeGfxObject(&background);
	
	closeRenderer(); //Free resources and close SDL
}
