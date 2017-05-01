#include "renderer.h"
#include <stdio.h>

SDL_Window*   gWindow    = NULL; //The window we'll be rendering to
SDL_Renderer* gRenderer  = NULL; //The window renderer
TTF_Font *gFont          = NULL; //Used font. Documentation of TTF_Font can be found here:  
                                 //  https://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf.html#SEC6


void renderGfxObject(GfxObject* gfx, int x, int y, double angle, float scale )
{
	//Render gfx object to screen
	SDL_Rect srcRect = { 0, 0, gfx->textureWidth, gfx->textureHeight }; // select the whole image
    
    // Use scale to compute new output width, height and x,y. 
    // Note on scaling: integer-discretized output positions means that width and height should be modified 
    // an equal amount on left/right/top/bottom sides to look good (i.e., in steps of two).
    int w = gfx->outputWidth*scale + 0.5; // round to nearest
    if ( ((w - gfx->outputWidth) % 2) == 1)
        w--;
    int h = gfx->outputHeight*scale + 0.5; // round to nearest
    if ( ((h - gfx->outputHeight) % 2) == 1)
        h--;        

    float dstX = x - w/2;
    float dstY = y - h/2;
	SDL_Rect dstRect = { dstX, dstY, w,  h };  // output position and width/height
    
	//Render to screen
    SDL_RenderCopyEx(gRenderer, gfx->mTexture, &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE);
    // NULL here specifies that rotation will be done around the center of the image. 
    // See here for details: https://wiki.libsdl.org/SDL_RenderCopyEx
}

GfxObject createGfxObject(  const char* filename )
{
    GfxObject gfx;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( filename );
    if( loadedSurface == NULL )
        printf( "Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError() );
    else 
    {
        //Create texture from surface pixels
        gfx.mTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( gfx.mTexture == NULL )
            printf( "Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError() );
        else {
            //Get image dimensions
            gfx.textureWidth  = loadedSurface->w;
            gfx.textureHeight = loadedSurface->h;
            // Set some default output size
            gfx.outputWidth  = gfx.textureWidth;
            gfx.outputHeight = gfx.textureHeight;
            
        }
        SDL_FreeSurface( loadedSurface ); //Get rid of old loaded surface
    }
    return gfx;
}

void freeGfxObject(GfxObject* gfx)
{
	//Free texture if it exists
	if( gfx->mTexture != NULL )
		SDL_DestroyTexture( gfx->mTexture );
    gfx->mTexture = NULL; // good way to mark that the pointer is now invalid
}

bool initRenderer(int windowWidth, int windowHeight)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}

void closeRenderer()
{
    	
    // free the font
    TTF_CloseFont(gFont);
    gFont=NULL; // to be safe...

    //Destroy window	
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


// Render Text
void renderText(const char* str, int x, int y)
{
    SDL_Color color={0xff, 0xff, 0x00}; // yellow 
    renderTextWithColor(color, str, x, y);
}
void renderTextWithColor(SDL_Color color, const char* str, int x, int y)
{
    static bool bFirstTime = true;
    if(bFirstTime)
    {
        bFirstTime = false;
        gFont = TTF_OpenFont( "../freefonts/FreeSans.ttf", 28 );
        if( gFont == NULL )
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        }        
    }
    
    SDL_Surface *surface;
    if(!(surface=TTF_RenderText_Blended(gFont, str, color))) {
        printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
    } 
    else 
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
        SDL_Rect dstRect = {x, y, surface->w, surface->h}; // x,y,w,h
        SDL_RenderCopy(gRenderer, texture, NULL, &dstRect);
        
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }  
}
