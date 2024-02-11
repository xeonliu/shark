#include "include/gameobject.h"

#include <algorithm>
#include "include/gamestate.h"
#include "include/component.h"
#include "include/math.h"

GameObject::GameObject(GameState* game_state):mGameState(game_state),mState(State::EActive),mPosition({0,0}),mScale({1.0,1.0}),mRotation(0.0){
    mGameState->addGameObject(this);
}

GameObject::~GameObject(){
    mGameState->removeGameObject(this);
    while(!mComponents.empty()){
        delete mComponents.back();
    }
}

void GameObject::Update(){
    if(mState==State::EActive){
        for(auto component : mComponents){
            component->Update();
        }
    }
}

GameObject::State GameObject::GetState(){
    return mState;
}

/// @brief Using iterator to insert the component to the right place.
/// @param component 
void GameObject::AddComponent(Component* component){
    int order = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for(;iter!=mComponents.end();++iter){
        if(order<(*iter)->GetUpdateOrder()){
            break;
        }
    }
    mComponents.insert(iter,component);
}

void GameObject::RemoveComponent(Component* component){
    auto iter = std::find(mComponents.begin(),mComponents.end(),component);
    if(iter!=mComponents.end()){
        mComponents.erase(iter);
    }
}

float GameObject::GetRotation(){
    return mRotation;
}

GameState* GameObject::GetGameState(){
    return mGameState;
}

Vector2 GameObject::GetScale(){
    return mScale;
}

Vector2 GameObject::GetPosition(){
    return mPosition;
}

void GameObject::SetPosition(const Vector2 &vec){
    mPosition = vec;
}

void GameObject::SetRotation(float angle){
    mRotation = angle;
}

void GameObject::SetScale(const Vector2& vec){
    mScale = vec;
}


