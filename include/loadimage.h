#pragma once
#include <SDL2/SDL.h>
#include "stblib/stb_image.h"

SDL_Texture* LoadTextureFromFile(const char* filepath, SDL_Renderer* renderer);

void flipVertically(unsigned char* data, int width, int height, int channels);