#include "include/itemlist.h"

#include <algorithm>

/** 
 * Item Definitions
*/

Item::Item(ItemList* item_list): GameObject(item_list->GetGameState()), mItemList(item_list), is_seleted_(false){
    // The memory of Item is still managed by GameState. NOT by item_list.
    mItemList->AddItem(this);
}

Item::~Item(){
    mItemList->RemoveItem(this);
}

void Item::Select(){
    is_seleted_ = true;
}

void Item::DeSelect() {
    is_seleted_ = false;
}

bool Item::isSelected(){
    return is_seleted_;
}

/**
 * ItemComponent Definitions
*/

ItemCompoent::ItemCompoent(Item* item) : SpriteComponent(item,0) {

}


void ItemCompoent::Draw(SDL_Renderer* renderer){
    Item* mItem = dynamic_cast<Item*>(mGameObject);

    SDL_Rect dstrect;
    dstrect.w = (srcRect.w * mGameObject->GetScale().x);
    dstrect.h = (srcRect.h * mGameObject->GetScale().y);
    dstrect.x = mGameObject->GetPosition().x;
    dstrect.y = mGameObject->GetPosition().y;

    if(mItem->isSelected()){
        SDL_SetRenderDrawColor(renderer,255,0,0,0);
        SDL_RenderDrawRect(renderer,&dstrect);
    }
    
    SpriteComponent::Draw(renderer);
}

/**
 * ItemList Definitions
*/

ItemList::ItemList(GameState* game_state) : GameObject(game_state), current_selection_(0) {

}

ItemList::~ItemList(){
    while(!mItems.empty()) {
        delete mItems.back();
    }
}

void ItemList::SelectItem(int index) {
    mItems[current_selection_]->DeSelect();
    mItems[index]->Select();
    current_selection_ = index;
}

int ItemList::GetCurrentSelection() {
    return current_selection_;
}

void ItemList::AddItem(Item* item) {
    mItems.emplace_back(item);
    if(mItems.size()==1){
        item->Select();
        current_selection_ = 0;
    }
};

void ItemList::RemoveItem(Item* item) {
    auto iter = std::find(mItems.begin(),mItems.end(),item);
    if(iter != mItems.end()) {
        mItems.erase(iter);
    }
}

void ItemList::SelectNextItem() {
    int size = mItems.size();
    SelectItem((current_selection_+1)%size);
}

ItemListInputComponent::ItemListInputComponent(ItemList* item_list) : Component(item_list) {

}

void ItemListInputComponent::ProcessInput(const uint8_t &button_state) {
    ItemList *mList = dynamic_cast<ItemList*>(mGameObject);
    
    if (button_state == SDL_CONTROLLER_BUTTON_DPAD_DOWN){
        mList->SelectNextItem();
    }
}
