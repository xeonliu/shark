#pragma once
#include <SDL2/SDL.h>

class GameObject;

class Component{
public:
    Component(GameObject*, int update_order = 100);
    ~Component();  
    virtual void Update();

    int GetUpdateOrder();
protected:
    GameObject* mGameObject;
    int updateOrder;
};

class SpriteComponent : public Component {
public:
    SpriteComponent(GameObject*, int draw_order, int update_order = 100);
    ~SpriteComponent();

    int GetDrawOrder();

    virtual void Draw(SDL_Renderer*);
    virtual void SetTexture(SDL_Texture*);
    virtual void SetSrcRect(const SDL_Rect&);

protected:
    SDL_Texture* mTexture;
    int mDrawOrder;
    SDL_Rect srcRect;
};