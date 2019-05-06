#pragma once

#include "Components.h"
#include "Vector2D.h"

class OwnerComponent : public Component {
public:
	Entity* owner;
	bool isHeld;
	Vector2D heldOffset = { 0, 0 };
	//Later this will be relative to facing direction of owner

	void giveTo(Entity* entity) {
		owner = entity;
	}

	void makeHeld(Vector2D offset = Vector2D(0,0)) {
		isHeld = true;
		heldOffset = offset;
	}

	void freeHeld() {
		isHeld = false;
		heldOffset = Vector2D(0, 0);
	}

	OwnerComponent(Entity* entity, bool hold = false, Vector2D offset = Vector2D(0,0)) {
		giveTo(entity);
		if (hold) {
			makeHeld(offset);
		}
	}

	void update() override {
		if (entity->hasComponent<TransformComponent>() && isHeld) {
			/*std::cout << "owner is " << owner->name
				<< " " << owner->getComponent<TransformComponent>().position
				<< std::endl;*/
			entity->getComponent<TransformComponent>().position.x
				= owner->getComponent<TransformComponent>().position.x + heldOffset.x;
			entity->getComponent<TransformComponent>().position.y
				= owner->getComponent<TransformComponent>().position.y + heldOffset.y;
		}
		//TODO: Probably better to do this inside transform component (considering will later have offset pos AND offset vel)
		//TransformC can do motion as if it were not attached and then just add on owner transform if has owner and is held...
		//YES MUCH BETTER
	}

	//Could actually have a whole history of ownership kept if you wanted
};