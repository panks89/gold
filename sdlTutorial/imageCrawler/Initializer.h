#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Initializer {
  /* Screen Dimensions */
  int SCREEN_WIDTH = 800;
  int SCREEN_HEIGHT = 400;

  bool success = true;
  
  /* Window to be rendered */
  SDL_Window *gWindow = nullptr;
  /* The surface contained by the window */
  SDL_Surface *gScreenSurface = nullptr;
  /* The image will load and show on the screen */
  SDL_Surface *gImageSurface = nullptr;

 public:
  bool isValid() { return success; }
  
  Initializer() {
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cout << "Window could not be created! SDL_Error: "
		<< SDL_GetError() << std::endl;
      success = false;
    } else {
      // For JPEG/JPG support
      IMG_Init(IMG_INIT_JPG);
      gWindow = SDL_CreateWindow("And You were doomed!!!",
				 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				 SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if (gWindow == nullptr) {
	std::cout << "Window could not be created! SDL_Error: "
		  << SDL_GetError() << std::endl;
	success = false;
      } else {
	// Get the screen surface
	gScreenSurface = SDL_GetWindowSurface(gWindow);
      }
    }
  }
  
  ~Initializer() {
    //Deallocate surface
    SDL_FreeSurface( gImageSurface );
    gImageSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    IMG_Quit();
    //Quit SDL subsystems
    SDL_Quit();
  }
  
  bool loadImage(const std::string &imageName) {
    bool success = true;
    // Load image
    //gImageSurface = SDL_LoadBMP(imageName.c_str());
    gImageSurface = IMG_Load(imageName.c_str());
    if (!gImageSurface) {
      std::cout << "Unable to load image " << imageName << std::endl;
      success = false;
    }
    return success;
  }
  
  void refresh() {
    // Apply the image
    SDL_BlitSurface(gImageSurface, nullptr, gScreenSurface, nullptr);
    // Update the surface
    SDL_UpdateWindowSurface(gWindow);
    // refresh
    for(int i = 0; i < 4000; i++){
      SDL_PumpEvents();
      SDL_Delay(1);
    }
  }
};

#endif /* INITIALIZER_H */
