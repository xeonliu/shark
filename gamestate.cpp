#include "include/gamestate.h"

#include <algorithm>
#include "include/loadimage.h"

#include "include/gamecontext.h"
#include "include/gameobject.h"
#include "include/component.h"
#include "include/itemlist.h"

GameState::GameState(GameContext* context) : mContext(context), isRunning(true){
    mContext->setState(this);
    mRenderer = context->getRenderer();
}

GameState::~GameState(){
    mContext->removeState(this);
}

void GameState::Event(){
    SDL_Event event;
    uint8_t button_state;
    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_CONTROLLERDEVICEADDED:
            SDL_GameControllerOpen(event.cdevice.which);    //index: 0
            SDL_Log("Open joy_stick_index: %d",event.cdevice.which);
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            button_state = event.cbutton.button;
            // Deal with input
            for (auto object : mGameObjects) {
                object->ProcessInput(button_state);
            }
            break;
        default:
            break;
        }
    }
}

void GameState::Update(){
    // Updating...
    isUpdating = true;
    for(auto game_object : mGameObjects){
        game_object->Update();
    }
    isUpdating = false;

    // Move the pending objects
    for(auto pending_object : mPendingObjects){
        mGameObjects.emplace_back(pending_object);
    }
    // remove its reference in mPendingObjects. Only one vector holds its reference.
    mPendingObjects.clear();

    // release the memory of dead objects.
    std::vector<GameObject*> deadObjects; // temporary vector.
    for(auto dead_object : mGameObjects){
        if(dead_object->GetState() == GameObject::State::EDead) {
            deadObjects.emplace_back(dead_object);
        }
    }

    for(auto dead_object : deadObjects){
        delete dead_object; // clear the memory and remove the reference in mGameObjects.
    }

}

void GameState::GameState::Draw(){
    SDL_SetRenderDrawColor(mRenderer,255,255,255,0);
    SDL_RenderClear(mRenderer);

    for(auto sprite : mSprites) {
        sprite->Draw(mRenderer);
    }

    SDL_RenderPresent(mRenderer);
}

void GameState::play(){
    while(isRunning){
        Event();
        Update();
        Draw();
    }
    exit();
}

void GameState::addGameObject(GameObject* object){
    if(isUpdating){
        mPendingObjects.emplace_back(object);
    }else{
        mGameObjects.emplace_back(object);
    }
}

void GameState::removeGameObject(GameObject* object){
    auto iter = std::find(mPendingObjects.begin(),mPendingObjects.end(),object);
    if(iter!=mPendingObjects.end()){
        std::iter_swap(iter,mPendingObjects.end()-1);
        mPendingObjects.pop_back();
    }

    iter = std::find(mGameObjects.begin(),mGameObjects.end(),object);
    if(iter!=mGameObjects.end()){
        std::iter_swap(iter,mGameObjects.end()-1);
        mGameObjects.pop_back();
    }
}

void GameState::addSprite(SpriteComponent* sprite){
    int order = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for(;iter!=mSprites.end();++iter){
        if(order<(*iter)->GetDrawOrder()){
            break;
        }
    }
    mSprites.insert(iter,sprite);
}

void GameState::removeSprite(SpriteComponent* sprite) {
    auto iter = std::find(mSprites.begin(),mSprites.end(),sprite);
    if(iter!=mSprites.end()){
        mSprites.erase(iter);
    }
}

WelcomeState::WelcomeState(GameContext* context) : GameState(context){

}

void WelcomeState::enter(){
    // Load Texture
    logo = LoadTextureFromFile("images/shared-1-sheet3.png",mRenderer);
    // // Create Game Objects
    // GameObject* button = new GameObject(this);
    // button->SetPosition({100,200});
    // // Create Sprites
    // SpriteComponent* sprite = new SpriteComponent(button,1);
    // // Setup Sprites
    // sprite->SetTexture(logo);
    SDL_Rect imgSrc = {128,198,58,18};
    // sprite->SetSrcRect(imgSrc);

    ItemList* list = new ItemList(this);
    
    Item* item_1 = new Item(list);
    item_1->SetPosition({100,100});
    ItemCompoent* comp = new ItemCompoent(item_1);
    comp->SetTexture(logo);
    comp->SetSrcRect(imgSrc);
    
    Item* item_2 = new Item(list);
    item_2->SetPosition({200,200});
    ItemCompoent* comp2 = new ItemCompoent(item_2);
    comp2->SetTexture(logo);
    comp2->SetSrcRect(imgSrc);
    
    ItemListInputComponent* input_comp = new ItemListInputComponent(list);


}

// void WelcomeState::Draw(){
//     SDL_SetRenderDrawColor(mRenderer,255,255,255,255);
//     SDL_RenderClear(mRenderer);
//     SDL_Rect imgSrc = {128,198,58,18};
//     SDL_Rect imgDst = {0,0,58,18};
//     SDL_RenderCopy(mRenderer,logo,&imgSrc,&imgDst);
//     SDL_RenderPresent(mRenderer);
// }

void WelcomeState::exit(){
    
}

WelcomeState::~WelcomeState(){

}
