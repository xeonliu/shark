#pragma once
#include <vector>
#include <cstdint>
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

    void ProcessInput(const uint8_t &button_state);


    

    void AddComponent(Component*);
    void RemoveComponent(Component*);

    // For Compositor Design Pattern Interface.
    // virtual void AddChildObject(GameObject*);
    // virtual void RemoveChildObject(GameObject*);

    template<typename T>
    T* GetComponent();

protected:
    std::vector<Component*> mComponents;
private:
    GameState* mGameState;
    State mState;
    Vector2 mPosition;
    Vector2 mScale;
    float mRotation;
};

// class CompositeGameObject : public GameObject {
// public:
//     CompositeGameObject(GameState*);

//     void AddChildObject(GameObject*) override;
//     void RemoveChildObject(GameObject*) override;
// protected:
//     std::vector<GameObject*> mGameObjects;
// };