#pragma once

#include "Components.h"
#include "Vector2D.h"

class OwnerComponent : public Component {
public:
	Entity* owner;
	bool isHeld;

	void giveTo(Entity* entity) {
		owner = entity;
	}

	void makeHeld() {
		isHeld = true;
	}

	void freeHeld() {
		isHeld = false;
	}

	OwnerComponent(Entity* entity, bool hold = false) {
		giveTo(entity);
		if (hold) { makeHeld(); }
		else { freeHeld(); }
	}

	//Could actually have a whole history of ownership kept if you wanted
};