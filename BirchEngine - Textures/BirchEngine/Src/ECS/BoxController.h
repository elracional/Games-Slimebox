#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class BoxController : public Component {
public:
	TransformComponent *transform;
	int contador = 0;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		srand(time(NULL));
	}

	void update() override {
		
		contador++;
		
		if (contador == 100) {
			contador = 0;
			transform->position.x = rand() % 430+70;
			transform->position.y = rand() % 430+70;
		}
	}
};

