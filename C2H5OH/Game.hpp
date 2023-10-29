#pragma once
#include "precompile.hpp"
#include "Player.hpp"
#include "Square.hpp"
#include "Walker.hpp"

using namespace sf;

class Game {
private:
	float dt;
	bool shouldClose;
	bool dash;
	float dashDistance;

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
	Vector2f dashed;
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