#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"

class Element : public RenderObject {
public:
	float spawnTime;
	Vector2f direction;
	std::string element;
	Clock timeAlive;
	Clock spawnClock;
};