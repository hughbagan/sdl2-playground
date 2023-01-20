
// Using SDL and standard IO
#include <SDL2/SDL.h> //#include <SDL.h>
#include <stdio.h>
#include <string>

// Key press surfaces constants
enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL; // window we'll render to
SDL_Surface* gScreenSurface = NULL; // surface contained by the window
SDL_Surface* gHelloWorld = NULL; // image we'll load and display
// images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

bool init(); // Starts up SDL and creates window
bool loadMedia(); // Loads media
void close(); // Frees media and shuts down SDL
SDL_Surface* loadSurface(std::string path); // Loads individual image

bool init()
{
    bool success = true;
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    	success = false;
    }
    else {
	    // Create window
	    gWindow = SDL_CreateWindow(
	        "SDL Tutorial",
	        SDL_WINDOWPOS_UNDEFINED,
	        SDL_WINDOWPOS_UNDEFINED,
	        SCREEN_WIDTH,
	        SCREEN_HEIGHT,
	        SDL_WINDOW_SHOWN
	    );
        if (gWindow==NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    // Load splash image
    const char* imgFilepath = "image.bmp";
    gHelloWorld = SDL_LoadBMP(imgFilepath);
    if (gHelloWorld==NULL) {
        printf("Unable to load image %s! SDL Error %s\n", imgFilepath, SDL_GetError());
        success = false;
    }
    return success;
}

SDL_Surface* loadSurface(std::string path) {
	// Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	return loadedSurface;
}

void close() {
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL; // pointer to NULL once freed
    // Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] ) {
    if (!init())
        printf("Failed to initialize!\n");
    else {
        if (!loadMedia())
            printf("Failed to load media!\n");
        else {
			bool quit = false; // main loop flag
			SDL_Event e; // event handler

			while (!quit) {
				// Handle events on a queue
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT)
						quit = true;
				}
				
				// Blitting stamps one surface onto another. Renders to back buffer.
				// blit loaded surface onto the screen surface
				SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
				// Update the surface
				// (put back buffer to front after all blits are done)
				SDL_UpdateWindowSurface(gWindow);
			}			
        }
    }

    close();

    return 0;
}
