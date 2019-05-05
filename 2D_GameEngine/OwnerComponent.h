#pragma once

#include "Components.h"

class OwnerComponent : public Component {
public:
	Entity* owner;

	void giveTo(Entity* entity) {
		owner = entity;
	}

	OwnerComponent(Entity* entity) {
		giveTo(entity);
	}

	//Could actually have a whole history of ownership kept if you wanted
};