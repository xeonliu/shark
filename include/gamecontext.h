#pragma once
#include <SDL2/SDL.h>
class GameState;

class GameContext {
public:
    GameContext();
    ~GameContext();
    void initialize();

    /// @brief Can only be called by GameState during construction.
    /// @param state 
    void setState(GameState *state);
    
    /// @brief Can only be called by GameState during deconstruction.
    /// @param state 
    void removeState(GameState *state);

    /// @brief Start the currentState.
    void play();
    SDL_Renderer* getRenderer();
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    GameState *currentState;
};