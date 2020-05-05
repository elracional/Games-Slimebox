#include "Game.h"
#include "TextureManager.h"
//#include "GameObject.h"
#include "Map.h"
//#include "ECS.h"

#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

//GameObject* player;
//GameObject* enemy;

Map* map;

/*
SDL_Texture *playerTex;
SDL_Rect srcR, destR;
*/
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& goodbox(manager.addEntity());
auto& badbox(manager.addEntity());
auto& badbox1(manager.addEntity());
auto& badbox2(manager.addEntity());

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

/*
//prueba tiles
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());
*/

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	//player = new GameObject("assets/player.png", 0,0);
	//enemy = new GameObject("assets/player2.png", 50, 50);
	map = new Map();

	Map::LoadMap("assets/p16x16.map", 16, 16);

	/*
	//Prueba Tiles
	tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
	tile1.addComponent<TileComponent>(250,250,32,32,1);
	tile1.addComponent<ColliderComponent>("dirt");
	tile2.addComponent<TileComponent>(150, 150, 32, 32, 2);
	tile2.addComponent<ColliderComponent>("grass");
	*/

	player.addComponent<TransformComponent>(2); //Se le pueden pasar las posiciones iniciales
	player.addComponent<SpriteComponent>("assets/slimeIDLE2.png", 3, 200);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	/*
	//PRUEBA PARED
	wall.addComponent<TransformComponent>(300.0f, 300.0f, 70, 49, 1);
	wall.addComponent<SpriteComponent>("assets/box.png");
	wall.addComponent<ColliderComponent>("box");
	wall.addGroup(groupMap);*/

	//GOOD BOX
	goodbox.addComponent<TransformComponent>(200.0f, 200.0f, 70, 49, 1);
	goodbox.addComponent<SpriteComponent>("assets/box.png");
	goodbox.addComponent<ColliderComponent>("goodbox");
	goodbox.addComponent<BoxController>(); //Para que actue como caja 
	goodbox.addGroup(groupMap);


	//BAD BOX
	badbox.addComponent<TransformComponent>(300.0f, 300.0f, 70, 49, 1);
	badbox.addComponent<SpriteComponent>("assets/badbox.png");
	badbox.addComponent<ColliderComponent>("badbox");
	badbox.addComponent<BoxController>(); //Para que actue como caja
	badbox.addGroup(groupMap);

	//BAD BOX
	badbox1.addComponent<TransformComponent>(300.0f, 300.0f, 70, 49, 1);
	badbox1.addComponent<SpriteComponent>("assets/badbox.png");
	badbox1.addComponent<ColliderComponent>("badbox");
	badbox1.addComponent<BoxController>(); //Para que actue como caja
	badbox1.addGroup(groupMap);

	//BAD BOX
	badbox2.addComponent<TransformComponent>(300.0f, 300.0f, 70, 49, 1);
	badbox2.addComponent<SpriteComponent>("assets/badbox.png");
	badbox2.addComponent<ColliderComponent>("badbox");
	badbox2.addComponent<BoxController>(); //Para que actue como caja
	badbox2.addGroup(groupMap);

	

	//newPlayer.addComponent<PositionComponent>();
	//newPlayer.getComponent<PositionComponent>().setPos(500,500);

	//playerTex = TextureManager::LoadTexture("assets/player.png", renderer);

	/*
	SDL_Surface *tmpSurface = IMG_Load("assets/player.png");
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);*/
}

void Game::handleEvents()
{
	

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	for (auto cc : colliders) {
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);

	}

	/*
	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		wall.getComponent<ColliderComponent>().collider)) {
		//player.getComponent<TransformComponent>().scale = 1;
		player.getComponent<TransformComponent>().velocity * -1;

		std::cout <<" Wall Hit! "<< std::endl;
	}*/

	/*
	player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));


	if (player.getComponent<TransformComponent>().position.x > 100) {
		player.getComponent<SpriteComponent>().setTex("assets/player.png");
	}*/

	/*
	player->Update();
	enemy->Update();
	std::cout << newPlayer.getComponent<PositionComponent>().x() << "," <<
		newPlayer.getComponent<PositionComponent>().y() << std::endl;
	*/

	/*
	cnt++;
	destR.h = 80;
	destR.w = 80;
	destR.x = cnt;
	std::cout << cnt << std::endl;*/
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));


void Game::render()
{
	SDL_RenderClear(renderer);
	/////////////map->DrawMap();
	//player->Render();
	//enemy->Render();
	//SDL_RenderCopy(renderer, playerTex, NULL,&destR);
	/////////manager.draw();
	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& p : players) {
		p->draw();
	}

	for (auto& e : enemies) {
		e->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}