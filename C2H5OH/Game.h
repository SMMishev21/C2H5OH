#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Game {
private:
	bool shouldClose;
	RenderWindow window;
	Event ev;

	//TODO: vector<RenderObject>

	void mainLoop();
	void update(bool* shouldClose);
	void handleInput();
	void draw();

public:
	Game();
	~Game();

};