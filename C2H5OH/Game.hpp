#pragma once
#include "precompile.hpp"
#include "Player.hpp"
#include "Square.hpp"
#include "Enemy.hpp"

using namespace sf;

class Game {
private:
	int hp;
	float dt;
	bool shouldClose;
	bool dash;

	RenderWindow window;
	Event ev;
	Player* plr;
	Texture plrTexture;
	Texture squareTexture;
	Texture enemyTexture;
	View view;
	Clock clock;
	Vector2f plrVelocity;
	Vector2f dir;
	Clock dashClock;
	Clock iFrames;

	std::vector<Enemy*> enemies;
	std::vector<RenderObject*> renderObjects;

	void mainLoop();
	void update();
	void handleInput(float dt);
	void draw();
	void handleMovement();

public:
	Game();
	~Game();

};