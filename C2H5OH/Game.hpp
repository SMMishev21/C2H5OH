#pragma once
#include "precompile.hpp"
#include "Player.hpp"
#include "Square.hpp"

using namespace sf;

class Game {
private:
	float dt;
	bool shouldClose;
	bool dash;

	RenderWindow window;
	Event ev;
	Player* plr;
	Texture plrTexture;
	Texture squareTexture;
	View view;
	Clock clock;
	Vector2f plrVelocity;
	Vector2f dir;
	Clock dashClock;

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