#include "Initializer.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main()
{
  std::string path = "/Users/pankaj/Desktop/sdlImages";
  Initializer loader;
  if (!loader.isValid()) {
    std::cout << "Failed to initialize loader!!!\n";
    return 1;
  }
  for (const auto & entry : fs::directory_iterator(path)) {
    std::cout << "Loading image - " << entry.path() << std::endl;
    if (loader.loadImage(entry.path())) {
      loader.refresh();
    } else {
      std::cout << "Falied to load!!!\n";
    }
  }
}

// \g++ -std=c++17 -I/opt/local/include/SDL2 -L/opt/local/lib -lSDL2 -lSDL2_image -lstdc++fs -o imageCrawler imageCrawler.cpp
