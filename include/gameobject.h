#pragma once
#include <vector>
#include "math.h"
class GameState;
class Component;

class GameObject{
public:
    
    enum State
	{
		EActive,
		EDead
	};

    GameObject(GameState*);
    virtual ~GameObject();

    // Sprite Component?
    // void Draw();
    void Update();
    // Process Input;
    // void Event();
    
    /// @brief Return a object is dead or alive
    /// @return ture or false
    State GetState();
    Vector2 GetPosition();
    Vector2 GetScale();
    float GetRotation();

    /// @brief Return the Game State the object belongs to
    /// @return 
    GameState* GetGameState();

    void SetPosition(const Vector2&);
    void SetScale(const Vector2&);
    void SetRotation(float);


    

    void AddComponent(Component*);
    void RemoveComponent(Component*);

protected:
    std::vector<Component*> mComponents;
private:
    GameState* mGameState;
    State mState;
    Vector2 mPosition;
    Vector2 mScale;
    float mRotation;
};
