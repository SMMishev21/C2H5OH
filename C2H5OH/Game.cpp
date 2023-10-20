#include "Game.h"
#include <thread>
#include <iostream>

Game::Game() {
	this->window.create(VideoMode(1280, 720), "Title");
	this->shouldClose = false;
	this->mainLoop();
}

void Game::mainLoop() {
	//std::jthread updateThread(&Game::update, this, &this->shouldClose);

	while (this->window.isOpen()) {
		while (this->window.pollEvent(this->ev)) {
			if (this->ev.type == Event::Closed) {
				this->window.close();
				this->shouldClose = true;
			}
		}


		this->draw();
	}
}

void Game::draw() {
	this->window.clear(Color(45, 75, 118, 255));
	// TODO: vector<RenderObject>
	this->window.display();
}

void Game::update(bool* shouldClose) {
	while (!shouldClose) {
		std::cout << "s\n";
	}
}