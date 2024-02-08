#pragma once
#include <SDL2/SDL.h>
class GameContext;

class GameState {
public:
    GameState(GameContext* context);
    virtual ~GameState();
    virtual void enter() = 0;
    virtual void play();
    virtual void exit() = 0;
protected:
    GameContext* mContext;
    SDL_Renderer* mRenderer;
    bool isRunning;
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
    void Draw() override;
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