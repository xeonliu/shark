#pragma once
#include <vector>
#include <SDL2/SDL.h>
class GameContext;
class GameObject;
class SpriteComponent;

class GameState {
public:
    GameState(GameContext* context);
    virtual ~GameState();
    virtual void enter() = 0;
    virtual void play();
    virtual void exit() = 0;

    void addGameObject(GameObject*);
    void removeGameObject(GameObject*);

    void addSprite(SpriteComponent*);
    void removeSprite(SpriteComponent*);
    
protected:
    GameContext* mContext;
    SDL_Renderer* mRenderer;
    std::vector<GameObject*> mGameObjects;
    std::vector<GameObject*> mPendingObjects;
    std::vector<SpriteComponent*> mSprites;
    bool isRunning;
    bool isUpdating;
private:
    virtual void Event();
    virtual void Update();
    virtual void Draw();
};

class WelcomeState : public GameState {
public:
    WelcomeState(GameContext*);
    ~WelcomeState();
    void enter();
    void exit();
private:
    // void Event();
    // void Update();
    // void Draw() override;
    SDL_Texture* logo;
};

// class MainMenuState : public GameState {
// public:
//     MainMenuState(GameContext*);
//     ~MainMenuState();
//     void enter();
//     void play();
//     void exit();
// private:
//     void Event();
//     void Update();
//     void Draw();
// };