#pragma once
#include "SDL.h"

class ColliderComponent;

class Collision {
public:
	//Axis Aligned Bounding Box collision?
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA,
					const ColliderComponent& colB);
	/*should I add an overload which takes in entities,
	and runs collision checking IF it has a ColliderComponent?*/

};