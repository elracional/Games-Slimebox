#include "Collision.h"
#include "ECS\ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y)
	{
		return true;
	}

	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB) {
	if (AABB(colA.collider, colB.collider)) {

		if (colB.tag == "goodbox" || colB.tag == "badbox") {
			std::cout << colA.tag << " hit: " << colB.tag << std::endl;
			colA.transform->position.x = 0;
			colA.transform->position.y = 0;
		}
		
		return true;
	}
	else {
		return false;
	}
}