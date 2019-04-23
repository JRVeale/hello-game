#pragma once

#include "Components.h"
#include "Vector2D.h"

//Position, rotation and scale

class TransformComponent : public Component {

public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;
	
	int speed = 3;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(int sc) {
		position.x = 400;
		position.y = 320;
		scale = sc;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(Vector2D pos) {
		position = pos;
	}

	TransformComponent(float x, float y, int w, int h, int sc) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = sc;
	}

	TransformComponent(Vector2D pos, int w, int h, int sc) {
		position = pos;
		width = w;
		height = h;
		scale = sc;
	}

	void init() override {
		velocity.Zero();
	}

	void update() override {
		
		//back in as scrolling now dealt with by camera
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	Vector2D getVectorTo(Vector2D point) {
		return point - position;
	}
};