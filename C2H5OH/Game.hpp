#pragma once
#include "precompile.hpp"
#include "Player.hpp"
#include "Square.hpp"
#include "Walker.hpp"
#include "Weapons.hpp"
#include <thread>

//#define FLAGS_MULTITHREADING

using namespace sf;

class Game {
private:
	float dt;
	bool shouldClose;
	bool dash;
	float dashDistance;

	RenderWindow window;
	Event ev;
	Texture plrTexture;
	Texture squareTexture;
	Texture enemyTexture;
	Texture akTexture;
	View view;
	Clock clock;
	Vector2f plrVelocity;
	Vector2f dir;
	Vector2f dashed;
	Clock dashClock;
	Clock iFrames;

	Ranged* ak;
	Player* plr;
	
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;
	std::vector<RenderObject*> renderObjects;

	void mainLoop();
	void handleInput(float dt);
	void draw();
	void handleMovement();
	void handleEnemies();

public:
	Game();
	~Game();
	void update();

};