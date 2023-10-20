#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
public:
	void setPlayerInfo(int health, float speed);
private:
	int health;
	float speed;
};
