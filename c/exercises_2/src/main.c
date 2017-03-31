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
#define PI 3.14
#define TO_DEGREES (180/PI)
#define TO_RADIANS (PI/180)

#define ACCELERATE	state[SDL_SCANCODE_UP]
#define BREAK		state[SDL_SCANCODE_DOWN]
#define TURN_RIGHT	state[SDL_SCANCODE_RIGHT]
#define TURN_LEFT	state[SDL_SCANCODE_LEFT]

#define WIDTH 800
#define HEIGHT 600
#define CENTER_WIDTH (WIDTH/2)
#define CENTER_HEIGHT (HEIGHT/2)

#define MAX_SCALE (sqrt(WIDTH*WIDTH+HEIGHT*HEIGHT)/HEIGHT)

#define TICK_RATE 0.25
#define SHIP_ACC 0.1
#define SHIP_DEC 0.05
#define SHIP_ROTATION_ACC 0.1
#define SHIP_ROTATION_DEC 0.05

// Global resources
GfxObject ship, background;

int backgroundRotation = 0;

double shipX = CENTER_WIDTH;
double shipY = CENTER_HEIGHT;
double shipXSpeed = 0;
double shipYSpeed = 0;
double shipRotationSpeed = 0;
double shipAngle = 90;

int main( int argc, char* args[] ) {
	// If you want the program to not launch the terminal, then go to
	// Project->Settings->General->"This program is a GUI application" and uncheck that flag.
	
	// Start up SDL and create window of width=800, height = 600
	initRenderer(WIDTH, HEIGHT);
	
	// Obtain keyboard pointer
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	
	// Create an object
	ship = createGfxObject(  "../ship.png" );
	ship.outputWidth  = 100;
	ship.outputHeight = 100;
	
	// Loading background resource
	background = createGfxObject(  "../background.jpg" );
	background.outputWidth  = WIDTH;
	background.outputHeight = HEIGHT;
	
	// The real-time loop
	while (true) {
		// Handle events on the inqueue (e.g., mouse events)
		SDL_Event e;  //Event handler
		while ( SDL_PollEvent( &e ) != 0 ) {
			if ( e.type == SDL_QUIT ) {
				close();
				exit(0);
			}
		}
		
		// Clear screen with a grey background color, red=0x33, blue=0x33, green=0x33, alpha=0xff. 0=minimum, 0xff=maximum.
		// Alpha is transparency: 0 = fully transparent, 0xFF = fully opaque. However, actual use of transparency requires further settings.
		SDL_SetRenderDrawColor( gRenderer, 0x33, 0x33, 0x33, 0xFF );
		SDL_RenderClear( gRenderer );
		
		// Register keyboard inputs
		
		// Ship calculations
		shipRotationSpeed -= SHIP_ROTATION_ACC * (TURN_RIGHT - TURN_LEFT) + shipRotationSpeed/3 * SHIP_ROTATION_DEC;
		
		shipAngle = fmod(shipAngle + shipRotationSpeed, 360);
		
		shipXSpeed += SHIP_ACC * (ACCELERATE - BREAK) * cos(shipAngle * TO_RADIANS) - shipXSpeed/4 * SHIP_DEC;
		shipYSpeed += SHIP_ACC * (ACCELERATE - BREAK) * sin(shipAngle * TO_RADIANS) - shipYSpeed/4 * SHIP_DEC;;
		
		shipX += shipXSpeed;
		shipY -= shipYSpeed;
		
		// Calculations (such as rotation of background etc.)
		backgroundRotation = (backgroundRotation+1) % (int) (360/TICK_RATE);
		int angle = backgroundRotation*TICK_RATE;
		
		/*
		 * quadrant is either 0 or 1, whether we are in an even or odd quadrant
		 * criticalAngle determines the angle at what MAX_SCALE occurs (in relation to the quadrant)
		 * cosAngle is the angle between the background and the criticalAngle
		 */
		int quadrant = (angle % 180) / 90;
		int criticalAngle = 180*quadrant + pow(-1, quadrant) * atan((float) WIDTH/HEIGHT) * TO_DEGREES;
		int cosAngle = (angle % 180) - criticalAngle;
		float scale = MAX_SCALE * cos(cosAngle * TO_RADIANS);
		
		// Render our object(s) - background objects first, and then forward objects (like a painter)
		renderGfxObject(&background, CENTER_WIDTH, CENTER_HEIGHT, angle, scale);
		renderGfxObject(&ship, shipX, shipY, 90 - shipAngle, 1.0f);
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
