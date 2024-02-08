#include "include/loadimage.h"

// Define this in one file only.
#define STB_IMAGE_IMPLEMENTATION
#include "include/stblib/stb_image.h"


void flipVertically(unsigned char* data, int width, int height, int channels) {
    int rowSize = width * channels;

    for (int i = 0; i < height / 2; ++i) {
        int oppositeRow = height - 1 - i;
        for (int j = 0; j < rowSize; ++j) {
            unsigned char temp = data[i * rowSize + j];
            data[i * rowSize + j] = data[oppositeRow * rowSize + j];
            data[oppositeRow * rowSize + j] = temp;
        }
    }
}

SDL_Texture* LoadTextureFromFile(const char* filepath, SDL_Renderer* renderer) {
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;
    unsigned char* data = stbi_load(filepath, &width, &height, &orig_format, req_format);
    if (data == NULL) {
        SDL_Log("Loading image failed: %s", stbi_failure_reason());
        return NULL;
    }

    #ifdef PSP
    // Flip the image vertically
    flipVertically(data, width, height, req_format);
    #endif
    
    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    int shift = (req_format == STBI_rgb) ? 8 : 0;
    rmask = 0xff000000 >> shift;
    gmask = 0x00ff0000 >> shift;
    bmask = 0x0000ff00 >> shift;
    amask = 0x000000ff >> shift;
    #else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = (req_format == STBI_rgb) ? 0 : 0xff000000;
    #endif

    int depth, pitch;
    if (req_format == STBI_rgb) {
        depth = 24;
        pitch = 3 * width;
    } else {
        depth = 32;
        pitch = 4 * width;
    }

    SDL_Surface* surf = SDL_CreateRGBSurfaceFrom((void*)data, width, height, depth, pitch,
                            rmask, gmask, bmask, amask);
    if (surf == NULL) {
        SDL_Log("Creating surface failed");
        return NULL;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);
    stbi_image_free(data);

    return tex;
}
