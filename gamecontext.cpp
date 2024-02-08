#include "include/gamecontext.h"
#include "include/gamestate.h"
GameContext::GameContext() : mWindow(nullptr), mRenderer(nullptr), currentState(nullptr){

}

GameContext::~GameContext(){}

void GameContext::setState(GameState* state){
    if(currentState!=nullptr){
        state->exit();
        delete currentState;
    }
    currentState = state;
}

/// @brief Only called by its child. Remove the reference of child.
/// @param state 
void GameContext::removeState(GameState* state){
    currentState = nullptr;
}

void GameContext::play(){
    currentState->enter();
    currentState->play();
}

void GameContext::initialize(){
    SDL_Init(SDL_INIT_EVERYTHING);
    mWindow = SDL_CreateWindow("window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,480,272,0);
    mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED);   
}

SDL_Renderer* GameContext::getRenderer(){
    return mRenderer;
}
