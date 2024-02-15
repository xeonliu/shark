#include "include/component.h"

#include "include/gameobject.h"
#include "include/gamestate.h"

Component::Component(GameObject* object, int update_order):mGameObject(object),updateOrder(update_order){
    mGameObject->AddComponent(this);
}

Component::~Component(){
    mGameObject->RemoveComponent(this);
}

void Component::Update(){

}

int Component::GetUpdateOrder(){
    return updateOrder;
}

void Component::ProcessInput(const uint8_t &button_state) {
    return;
}

SpriteComponent::SpriteComponent(GameObject* object, int draw_order, int update_order) : Component(object,update_order), mDrawOrder(draw_order){
    mGameObject->GetGameState()->addSprite(this);
}

SpriteComponent::~SpriteComponent(){
    mGameObject->GetGameState()->removeSprite(this);
}

int SpriteComponent::GetDrawOrder(){
    return mDrawOrder;
}

void SpriteComponent::SetTexture(SDL_Texture* tex){
    mTexture = tex;
    int width,height;
    SDL_QueryTexture(mTexture,NULL,NULL,&width,&height);
    SetSrcRect({0,0,width,height});
};

void SpriteComponent::SetSrcRect(const SDL_Rect& rect) {
    srcRect = rect;
}

void SpriteComponent::Draw(SDL_Renderer* renderer) {
    if(!mTexture){
        return;
    }

    SDL_Rect dstrect;
    dstrect.w = (srcRect.w * mGameObject->GetScale().x);
    dstrect.h = (srcRect.h * mGameObject->GetScale().y);
    dstrect.x = mGameObject->GetPosition().x;
    dstrect.y = mGameObject->GetPosition().y;

    SDL_RenderCopyEx(renderer,mTexture,&srcRect,&dstrect,mGameObject->GetRotation(),nullptr,SDL_FLIP_NONE);
}