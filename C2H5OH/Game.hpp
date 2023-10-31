#pragma once
#include "precompile.hpp"
#include "Player.hpp"
#include "Square.hpp"
#include "Walker.hpp"
#include "Weapons.hpp"
#include <thread>

#define FLAGS_MULTITHREADING

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
	Texture bulletTexture;
	View view;
	Clock clock;
	Vector2f plrVelocity;
	Vector2f dir;
	Vector2f dashed;
	Clock dashClock;
	Clock iFrames;
	Clock attackCD;

	Ranged* ak;
	Player* plr;
	
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;
	std::vector<RenderObject*> renderObjects;
	std::vector<RenderObject*> garbage;

	void mainLoop();
	void handleInput(float dt);
	void draw();
	void handleMovement();
	void handleEnemies();
	std::vector<int> resolveCollisionsEnemy(Bullet& bullet, float size);

public:
	Game();
	~Game();
	void update();

};