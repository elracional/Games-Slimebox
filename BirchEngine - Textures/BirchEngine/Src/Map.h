#pragma once
//#include "Game.h"
#include <string>

class Map {
public:

	Map();
	~Map();

	static void LoadMap(std::string path, int sizeX, int sizeY);
	//void LoadMap(int arr[20][25]);
	
	//Funcion de prueba antes de implementar TileMap
	//void DrawMap();

private:




	/*
	//Prueba dibujando mapa
	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][25];
	*/
};

