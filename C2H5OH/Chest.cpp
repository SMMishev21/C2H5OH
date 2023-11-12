#include "precompile.hpp"
#include "Chest.hpp"

std::pair<std::string, int> Chest::getRandomElement() {
	this->opened = true;
	return std::make_pair(this->elements[rand() % this->elements.size()], 1 + rand() % 5);
}