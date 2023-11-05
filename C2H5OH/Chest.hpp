#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"
#include <random>

class Chest : public RenderObject {
public:
	bool opened{ false };
	std::pair<std::string, int> getRandomElement();
private:
	std::vector<std::string> elements = {
		"carbon",
		"hydrogen",
		"nitrogen",
		"oxygen"
	};
};