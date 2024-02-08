#include "include/gamestate.h"
#include "include/gamecontext.h"
#include "include/loadimage.h"

GameState::GameState(GameContext* context) : mContext(context), isRunning(true){
    mContext->setState(this);
    mRenderer = context->getRenderer();
}

GameState::~GameState(){
    mContext->removeState(this);
}

void GameState::Event(){

}

void GameState::Update(){

}

void GameState::GameState::Draw(){

}

void GameState::play(){
    while(isRunning){
        Event();
        Update();
        Draw();
    }
    exit();
}

WelcomeState::WelcomeState(GameContext* context) : GameState(context){

}

void WelcomeState::enter(){
    // Load Texture
    logo = LoadTextureFromFile("images/shared-1-sheet3.png",mRenderer);
}

void WelcomeState::Draw(){
    SDL_SetRenderDrawColor(mRenderer,255,255,255,255);
    SDL_RenderClear(mRenderer);
    SDL_Rect imgSrc = {128,198,58,18};
    SDL_Rect imgDst = {0,0,58,18};
    SDL_RenderCopy(mRenderer,logo,&imgSrc,&imgDst);
    SDL_RenderPresent(mRenderer);
}

void WelcomeState::exit(){
    
}

WelcomeState::~WelcomeState(){

}
