#include "Game.hpp"
#include <thread>
#include <iostream>
#include <chrono>
#include <ppl.h>

Game::Game() {
	this->window.create(VideoMode(1280, 720), "Title");
	this->window.setFramerateLimit(240);
	this->shouldClose = false;

	this->enemyTexture.loadFromFile("./assets/enemy.png");
	this->plrTexture.loadFromFile("./assets/plr.png");
	this->plr = new Player;
	this->plr->init(this->plrTexture, Vector2f(500, 300), 'p');

	this->squareTexture.loadFromFile("./assets/square.png");

	for (int i = 0; i < 100; i++) {
		Square* square = new Square;
		square->init(this->squareTexture, Vector2f(64 * i, 0), 'b');
		this->renderObjects.push_back(square);
	}

	this->renderObjects.push_back(this->plr);

	for (int i = 0; i < 10; i++) {
		Enemy* enemy = new Enemy;
		enemy->init(this->enemyTexture, Vector2f(rand() % 300 + i, rand() % 300 + i), 'e');
		this->enemies.push_back(enemy);
		this->renderObjects.push_back(enemy);
	}

	this->hp = 100;

	this->view.setCenter(this->plr->getPosition());
	this->view.setSize(Vector2f(1920, 1080));

	this->mainLoop();
}

void Game::mainLoop() {
	std::jthread updateThread(&Game::update, this);
	dt = 0.f;
	while (this->window.isOpen()) {
		while (this->window.pollEvent(this->ev)) {
			if (this->ev.type == Event::Closed) {
				this->window.close();
				this->shouldClose = true;
			}
		}

		this->handleInput(this->dt);

		this->handleMovement();

		this->view.move((this->plr->getPosition() - this->view.getCenter()) * 3.f * this->dt);

		this->draw();

		this->dt = clock.restart().asSeconds();
	}
}

void Game::draw() {
	this->window.setView(this->view);
	this->window.clear(Color(45, 75, 118, 255));
	
	for (int i = 0; i < this->renderObjects.size(); ++i) {
		this->renderObjects[i]->draw(this->window);
	}

	this->window.display();
}

void Game::handleMovement() {
	if (this->dash) {
		this->plr->move((this->plrVelocity * this->dt));
		
		this->plrVelocity *= (1.f - this->dt * 0.99f);
		
		if (abs(this->plrVelocity.x) < 1300 && abs(this->plrVelocity.y) < 1300) {
			this->plrVelocity *= 0.f;
			this->dash = false;
		}
	}
}

void Game::handleInput(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		this->plr->move(Vector2f(-200, 0) * dt);
		this->dir.x = -1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		this->plr->move(Vector2f(200, 0) * dt);
		this->dir.x = 1;
	}
	else {
		this->dir.x = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->plr->move(Vector2f(0, -200) * dt);
		this->dir.y = -1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		this->plr->move(Vector2f(0, 200) * dt);
		this->dir.y = 1;
	}
	else {
		this->dir.y = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::LShift) && this->dashClock.getElapsedTime().asSeconds() >= 1 && !this->dash) {
		this->dashClock.restart();
		this->dash = true;
		this->plrVelocity = Vector2f(1500 * dir.x, 1500 * dir.y);
	}
}

void Game::update() {
	Clock clockU;
	Time dtU;

	while (!this->shouldClose) {
		dtU = clockU.restart();

		/*if (dtU.asMilliseconds() < 20) {
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(20 - dtU.asMilliseconds())));
		}*/

		for (auto enemy : this->enemies) {
			Vector2f distanceFromPlayer = this->plr->getPosition() - enemy->getPosition();
			float hypotenuse = sqrt(distanceFromPlayer.x * distanceFromPlayer.x + distanceFromPlayer.y * distanceFromPlayer.y);

			if (hypotenuse < 600) {
				if (hypotenuse > 47) {
					enemy->move(distanceFromPlayer / hypotenuse * 155.f, dtU.asSeconds());
				}
				else {
					if (this->iFrames.getElapsedTime().asSeconds() > 0.4 && !this->dash) {
						this->iFrames.restart();
						//this->healthBar.setSize(this->healthBar.getSize() - Vector2f(40, 0));
						this->hp -= 10;
					}
				}
			}
		}
	}
}