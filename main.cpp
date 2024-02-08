#include <iostream>

#include <SDL2/SDL.h>

#ifdef PSP
#include <pspkernel.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspmoduleinfo.h>
#include <psputility.h>
#include <pspgu.h>
#include <pspgum.h>
#include <string.h>
#define printf pspDebugScreenPrintf
#endif

#include "include/gamecontext.h"
#include "include/gamestate.h"
#include "include/loadimage.h"

int main(int argc, char* argv[]){
#ifdef PSP
    pspDebugScreenInit();
    pspDebugScreenSetXY(0, 0);
#endif
    GameContext context;
    context.initialize();

    GameState* welcome_state = new WelcomeState(&context);
    context.play();

    // SDL_Init(SDL_INIT_EVERYTHING);
    // SDL_Window *window = SDL_CreateWindow("window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,480,272,0);
    // SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // SDL_Texture *tex = LoadTextureFromFile("images/shared-1-sheet3.png",renderer);

    // if(!tex){
    //     SDL_Log("failed to load texture");
    // }

    // int textureW,textureH;
    // SDL_QueryTexture(tex,NULL,NULL,&textureW,&textureH);

    // std::cerr << "width: " << textureW << "height: " << textureH << std::endl;
    
    // while (1)
    // {
    //     // Use the selected color to clear the renderer.
    //     SDL_SetRenderDrawColor(renderer,255,255,255,0);
    //     SDL_RenderClear(renderer);
    //     // Draw whatever you want here.
    //     SDL_Rect imgSrc = {128,198,58,18};
    //     SDL_Rect imgDst = {0,0,58,18};
    //     SDL_RenderCopy(renderer,tex,&imgSrc,&imgDst);
    //     SDL_RenderPresent(renderer);
    //     SDL_Delay(10);
    // }

    
}
