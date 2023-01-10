
// Using SDL and standard IO
#include <SDL2/SDL.h> //#include <SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL; // window we'll render to
SDL_Surface* gScreenSurface = NULL; // surface contained by the window
SDL_Surface* gHelloWorld = NULL; // image we'll load and display

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

bool init()
{
    bool success = true;
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
    	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    	success = false;
    }
    else
    {
	    // Create window
	    gWindow = SDL_CreateWindow(
	        "SDL Tutorial",
	        SDL_WINDOWPOS_UNDEFINED,
	        SDL_WINDOWPOS_UNDEFINED,
	        SCREEN_WIDTH,
	        SCREEN_HEIGHT,
	        SDL_WINDOW_SHOWN
	    );
        if (gWindow==NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    // Load splash image
    const char* imgFilepath = "image.bmp";
    gHelloWorld = SDL_LoadBMP(imgFilepath);
    if (gHelloWorld==NULL)
    {
        printf("Unable to load image %s! SDL Error %s\n", imgFilepath, SDL_GetError());
        success = false;
    }
    return success;
}

void close()
{
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL; // pointer to NULL once freed
    // Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    if (!init())
        printf("Failed to initialize!\n");
    else
    {
        if (!loadMedia())
            printf("Failed to load media!\n");
        else
        {
            // Blitting stamps one surface onto another. Renders to back buffer.
            // blit loaded surface onto the screen surface
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            // Update the surface
            // (put back buffer to front after all blits are done)
            SDL_UpdateWindowSurface(gWindow);
        }
    }

    //Hack to get window to stay up
    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

    close();

    return 0;
}
