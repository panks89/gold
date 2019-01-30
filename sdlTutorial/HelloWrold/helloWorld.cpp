#include <SDL.h>
#include <iostream>

/* Screen Dimensions */
constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

int main()
{
  SDL_Window *window = nullptr;
  SDL_Surface *screen = nullptr;

  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    std::cout << "SDL could not initialize! SDL_Error: "
	      << SDL_GetError() << std::endl;
    return 1;
  } 
  window = SDL_CreateWindow("Hello World from SDL!!!", SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN);
  
  if (window == nullptr) {
    std::cout << "Window could not be created! SDL_Error: "
	      << SDL_GetError() << std::endl;
  } else {

    // Get the screen surface
    screen = SDL_GetWindowSurface(window);

    // Fill the surface white
    SDL_FillRect(screen, NULL,
    		 SDL_MapRGB(screen->format, 66, 244, 188));
    // Update the surface
    SDL_UpdateWindowSurface(window);
    // Wait two seconds
    //SDL_Delay(2000);
    /* 
       On OSX the title-bar only updates 
       each time the events are polled or pumped.
       This means that SDL_Delay() blocks the title-bar rendering process
       if it prevents you from pumping events.
    */
    for(int i = 0; i < 10000; i++){
      SDL_PumpEvents();
      SDL_Delay(1);
    }
  }

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystem
  SDL_Quit();
}

// g++ -I/opt/local/include/SDL2 -L/opt/local/lib -lSDL2 -o hellowWorld helloWorld.cpp
