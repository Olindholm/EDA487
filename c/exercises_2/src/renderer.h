#ifndef RENDER_H
#define RENDER_H

// Example on how to check the operating system at compile time.
// We need this to include SDL, SDL_image, and SDL_ttf using the correct path.
#ifdef _WIN32 
    //define something for Windows (32-bit and 64-bit, this part is common)
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
   #ifdef _WIN64 //define something for Windows (64-bit only)
   #endif
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
        #include <SDL2/SDL.h>
        #include <SDL2_image/SDL_image.h>
        #include <SDL2_ttf/SDL_ttf.h>
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    // linux
#elif __unix__ // all unices not caught above
    // Unix
#else
#   error "Unknown compiler"
#endif


typedef enum { false, true } bool;

// define globals here so that they could be accessed from files that include renderer.h
extern SDL_Window*   gWindow;     //The window we'll be rendering to
extern SDL_Renderer* gRenderer;   //The window renderer
extern TTF_Font *gFont;           //Globally used font

// define our GfxObject struct
typedef struct {
    int outputWidth, outputHeight;      // size of object when rendered to the screen
    int textureWidth, textureHeight;    // original size of the loaded image.
    SDL_Texture* mTexture;
} GfxObject;

bool initRenderer(int windowWidth, int windowHeight);   // creates an SDL window and an SDL renderer
void closeRenderer();                                   // deallocate resources on exit
GfxObject createGfxObject(  const char* imagefilename );// creates a GfxObject from an image file  
void renderGfxObject(GfxObject* gfx, int x, int y,      // draws the object to the screen at pos x,y
                     double angle, float scale );       //    default: angle=0, scale=1.0f
void freeGfxObject(GfxObject* gfx);                     // free the object's allocated SDL resources 


// Render text
void renderText(const char* str, int x, int y);                  // x,y are output positions
void renderTextWithColor(SDL_Color color, const char* str, int x, int y); // color is text color

#endif // RENDER_H