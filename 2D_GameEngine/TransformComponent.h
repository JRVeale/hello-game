#pragma once

#include "Components.h"
#include "Vector2D.h"

//Position, rotation and scale

class TransformComponent : public Component {

public:

	Vector2D position;
	Vector2D relative_position;	//position relative to owner, if no owner, relative to 0

	float facing_direction;		//angle in degrees, positive is anticlockwise, 0 is up
	float relative_direction;	//angle relative to owner, if no owner, relative to 0

	Vector2D relative_velocity;	//velocity relative to owner (also relative to direction of owner)

	int height = 32;
	int width = 32;
	int scale = 1;
	
	int speed = 3;

	TransformComponent() {
		relative_position.Zero();
	}

	TransformComponent(int sc) {
		relative_position.x = 400;
		relative_position.y = 320;
		scale = sc;
	}

	TransformComponent(float x, float y) {
		relative_position.x = x;
		relative_position.y = y;
	}

	TransformComponent(Vector2D pos) {
		relative_position = pos;
	}

	TransformComponent(float x, float y, int w, int h, int sc) {
		relative_position.x = x;
		relative_position.y = y;
		width = w;
		height = h;
		scale = sc;
	}

	TransformComponent(Vector2D pos, int w, int h, int sc) {
		relative_position = pos;
		width = w;
		height = h;
		scale = sc;
	}

	void init() override {
		relative_velocity.Zero();
	}

	void update() override {
		
		//back in as scrolling now dealt with by camera
		relative_position.x += relative_velocity.x * speed;
		relative_position.y += relative_velocity.y * speed;

		if (entity->hasComponent<OwnerComponent>()) {
			OwnerComponent* ownerComp = &entity->getComponent<OwnerComponent>();
			if (ownerComp->isHeld) {
				position = ownerComp->owner->getComponent<TransformComponent>().position + relative_position;
			}
			else {
				position = relative_position;
			}
		}
		else {
			position = relative_position;
		}
	}

	Vector2D getVectorTo(Vector2D point) {
		return point - position;
	}
};