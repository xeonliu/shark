#pragma once
#include <unordered_map>
#include "gameobject.h"
#include "component.h"

class Item;
class ItemCompoent;
class ItemList;
class ItemListInputComponent;

// The position is stored by GameObject. Not Component.
// define the position
class Item : public GameObject {
public:
    Item(ItemList*);
    ~Item();

    void Select();
    void DeSelect();
    bool isSelected();
private:
    bool is_seleted_;
    ItemList* mItemList;
};

// define how to draw.
class ItemCompoent : public SpriteComponent {
public:
    ItemCompoent(Item*);
    void Draw(SDL_Renderer*) override;
};

class ItemListInputComponent : Component {
public:
    ItemListInputComponent(ItemList*);
    void ProcessInput(const uint8_t &);
};

// Manage the items.
class ItemList : public GameObject {
public: 
    ItemList(GameState* game_state);
    ~ItemList();
    
    void SelectNextItem();
    
    void SelectItem(int);
    int GetCurrentSelection();

    /// @brief Never called outside the constructor of ItemComponent.
    /// @param  
    void AddItem(Item*);
    void RemoveItem(Item*);
private:
    int current_selection_;
    std::vector<Item*> mItems;
};



// How does item list process its input?

// Draw accoring to state?
// States are stores by components?

// ItemComponent : public SpriteComponent;

// Multiple ItemCompoent?