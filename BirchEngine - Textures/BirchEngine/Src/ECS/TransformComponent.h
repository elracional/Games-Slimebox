#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {


public:
	//int xpos;
	//int ypos;

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 2;

	TransformComponent() {
		//xpos = 0;
		//ypos = 0;
		//position.x = 0.0f;
		//position.y = 0.0f;
		position.Zero();
	}

	TransformComponent(int sc) {

		//position.x = 0.0f;
		//position.y = 0.0f;
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y) {
		
		position.x = x;
		position.y = y;
		//xpos = x;
		//ypos = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc) {

		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	
	}

	void init() override {
		//velocity.x = 0;
		//velocity.y = 0;
		velocity.Zero();
	}

	void update() override {

		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		//xpos++;
		//ypos++;
	}

	/*
	int x() { return xpos; }
	void x(int x) { xpos = x; }
	int y() { return ypos; }
	void y(int y) { ypos = y; }
	void setPos(int x, int y) { xpos = x; ypos = y; }
	*/
};


/*

	int x() { return xpos; }
	int y() { return ypos; }

	void init() override {
		xpos = 0;
		ypos = 0;
	}

	void update() override {
		xpos++;
		ypos++;
	}

	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}
*/