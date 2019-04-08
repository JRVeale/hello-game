#pragma once

#include "Components.h"
#include "TextureManager.h"
#include <list>

class InventoryComponent : public Component {
private:
	unsigned int slots;
	std::list<Entity*> heldItems;
	int slotsFilled;

	SDL_Texture* tex;			//For frame
	SDL_Rect srcRect, destRect;

	bool couldStack(Entity*) {
		/*Not to be confused with whether an entity is stackable...*/
		//TODO figure out if more of same item already held, and how to stack
		//Perhaps just by entity name!
		return false;
	}
	int getSlotsNeeded(std::list<Entity*> i) {
		//TODO account for stacking (if stacking by name, can count unique names
		//temp
		return i.size();
	}

public:
	InventoryComponent(int s){
		slots = s;
	}

	InventoryComponent(int s, std::list<Entity*> i) {
		slots = s;
		heldItems = i;

	}

	void init() override {}
	void update() override {
		/*TODO: Should we update items' transform to match container?*/
	}

	void draw() override {
		//Allows drawing the UI
		/*If don't always want inventory UI can add and remove
		from rendering group as necessary*/

		//TODO: Draw UI frame

		//TODO: Draw icons within frame, in right pos, with size of stack
	}

	bool addItem(Entity* e){
		if (slotsFilled >= slots && !couldStack(e)) {
			return false;
		}
		heldItems.push_back(e);
		/*TODO: Should we remove components from entity (i.e. transform)
		when they're held in an inventory?*/
		return true;
	}

	void removeItem(Entity* e){
		heldItems.remove(e);
	}

	void sort(){
		//TODO
	}

	void adjustSize(int i) {
		slots = slots + i;
	}

	void setSize(int s) {
		slots = s;
	}
};