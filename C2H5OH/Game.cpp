#include "Game.hpp"
#include <thread>
#include <iostream>
#include <chrono>
#include <ppl.h>

float clamp(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}

template<typename T>
void deleteObjects(std::vector<T*>& objects, std::vector<RenderObject*> garbage)
{
	for (auto it = objects.begin(); it != objects.end(); )
	{
		auto obj = *it;
		auto garbageIt = std::find(garbage.begin(), garbage.end(), obj);

		if (garbageIt != garbage.end())
		{
			it = objects.erase(it);
		}
		else
		{
			++it;
		}
	}
}

Game::Game() {
	this->window.create(VideoMode(1280, 720), "Title");
	this->window.setFramerateLimit(240);
	this->shouldClose = false;

	this->enemyTexture.loadFromFile("./assets/enemy.png");
	this->plrTexture.loadFromFile("./assets/plr.png");
	this->squareTexture.loadFromFile("./assets/square.png");
	this->akTexture.loadFromFile("./assets/ak.png");
	this->bulletTexture.loadFromFile("./assets/bullet.png");
	this->chestTexture.loadFromFile("./assets/chest.png");
	this->keyTexture.loadFromFile("./assets/key.png");
	this->carbonTexture.loadFromFile("./assets/carbon.png");
	this->oxygenTexture.loadFromFile("./assets/oxygen.png");
	this->nitrogenTexture.loadFromFile("./assets/nitrogen.png");
	this->hydrogenTexture.loadFromFile("./assets/hydrogen.png");
	
	this->enemyTexture.setSmooth(true);
	this->plrTexture.setSmooth(true);
	this->squareTexture.setSmooth(true);
	this->bulletTexture.setSmooth(true);
	this->chestTexture.setSmooth(true);
	this->keyTexture.setSmooth(true);
	this->carbonTexture.setSmooth(true);
	this->oxygenTexture.setSmooth(true);
	this->nitrogenTexture.setSmooth(true);
	this->hydrogenTexture.setSmooth(true);

	this->elementTextureMap = {
		{"carbon", this->carbonTexture},
		{"hydrogen", this->oxygenTexture},
		{"nitrogen", this->nitrogenTexture},
		{"oxygen", this->oxygenTexture}
	};

	this->plr = new Player;
	this->plr->init(this->plrTexture, Vector2f(0, 0), 'p');
	this->dashDistance = 1300;

	this->ak = new Ranged;
	this->ak->setRangedInfo(20, 8, 1, 2500, 0.0001);
	this->ak->setTexture(this->akTexture);

	this->chest = new Chest;
	this->chest->setTexture(this->chestTexture);
	this->chest->setOrigin(Vector2f(48, 37.5));
	this->chest->setPosition(Vector2f(-100, 100));

	this->key = new RenderObject;
	this->key->setTexture(this->keyTexture);

	for (int i = 0; i < 100; i++) {
		Square* square = new Square;
		square->init(this->squareTexture, Vector2f(64 * i, 0), 'b');
		this->renderObjects.push_back(square);
	}

	for (int i = 0; i < 2; i++) {
		RangedEnemy* enemy = new RangedEnemy;
		enemy->init(this->enemyTexture, Vector2f(rand() % 300 + i, rand() % 300 + i), 'e');
		this->enemies.push_back(enemy);
		this->renderObjects.push_back(enemy);
	}

	this->renderObjects.push_back(this->chest);
	this->renderObjects.push_back(this->key);

	this->chests.push_back(this->chest);

	this->view.setCenter(this->plr->getPosition());
	this->view.setSize(Vector2f(1920, 1080));

	this->mainLoop();
}

void Game::mainLoop() {
#ifdef FLAGS_MULTITHREADING
	std::jthread* updateThread = new std::jthread(&Game::update, this);
#endif
	std::jthread* garbageThread = new std::jthread(&Game::collectGarbage, this);

	this->dt = 0.f;
	while (this->window.isOpen()) {
		this->drawReady.acquire();
		while (this->window.pollEvent(this->ev)) {
			if (this->ev.type == Event::Closed) {
				this->window.close();
				this->shouldClose = true;
			}
		}

		this->handleInput(this->dt);

		this->handleMovement();

		this->spawnElements();

		this->view.move((this->plr->getPosition() - this->view.getCenter()) * 3.f * this->dt);

		#ifndef FLAGS_MULTITHREADING
				this->update();
		#endif

		this->draw();

		this->drawReady.release();

		this->dt = this->clock.restart().asSeconds();
	}

#ifdef FLAGS_MULTITHREADING
	updateThread->request_stop();
	delete updateThread;
#endif

	garbageThread->request_stop();
	delete garbageThread;

	Concurrency::parallel_for_each(std::begin(this->renderObjects), std::end(this->renderObjects), [](RenderObject* renderObject) {
		delete renderObject;
	});
	
	this->renderObjects.clear();
	this->enemies.clear();
	this->bullets.clear();
}

void Game::draw() {
	this->window.setView(this->view);
	this->window.clear(Color(45, 75, 118, 255));

	for (int i = 0; i < this->renderObjects.size(); ++i) {
		if (this->renderObjects.at(i)->shouldDraw) {
			this->renderObjects.at(i)->draw(this->window);
		}
	}

	this->plr->draw(this->window);

	this->window.display();
}

void Game::handleMovement() {
	if (this->dash) {
		this->plr->move((this->plrVelocity * this->dt));

		this->plrVelocity *= (1.f - this->dt * 0.99f);

		if (abs(this->plrVelocity.x) < this->dashDistance && abs(this->plrVelocity.y) < this->dashDistance) {
			this->plrVelocity *= 0.f;
			this->dash = false;
			this->dashDistance = 1300;
			this->dashed -= this->plr->getPosition();
		}
	}

	for (Chest* chest : this->chests) {
		if (hypotf((this->plr->getPosition() - chest->getPosition()).x, (this->plr->getPosition() - chest->getPosition()).y) <= 65 && !chest->opened) {
			if (!this->key->shouldDraw) {
				this->key->setPosition(chest->getPosition() - Vector2f(48, 76));
				this->key->shouldDraw = true;
				this->selected = chest;
				break;
			}
		}
		else {
			if (this->key->shouldDraw) {
				this->key->shouldDraw = false;
				this->selected = nullptr;
			}
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

	this->ak->setPosition(this->plr->getPosition());

	if (Keyboard::isKeyPressed(Keyboard::LShift) && this->dashClock.getElapsedTime().asSeconds() >= 1 && !this->dash) {
		this->dashClock.restart();
		this->dash = true;

		if (dir.x != 0 && dir.y != 0) {
			this->dashDistance = 1358.5;
		}
		this->plrVelocity = Vector2f(1500 * dir.x, 1500 * dir.y);
		this->dashed = this->plr->getPosition();
	}

	if (Mouse::isButtonPressed(Mouse::Button::Left)) {
		this->ak->shoot(this->bullets, this->renderObjects, this->window, this->plr, this->bulletTexture, this->attackCD);
	}

	if (Keyboard::isKeyPressed(Keyboard::E)) {
		if (this->selected != nullptr && !this->selected->opened) {
			std::pair<std::string, int> elementPair = this->selected->getRandomElement();
			for (int i = 0; i < elementPair.second; ++i) {
				float angle = rand() % 180;
				Element* element = new Element;
				element->shouldDraw = false;
				element->spawnTime = float(i) / 10;
				Vector2f direction(cos(angle * 3.14159265359 / 180), sin(angle * 3.14159265359 / 180));
				element->direction = direction / hypotf(direction.x, direction.y);
				element->element = elementPair.first;
				element->setPosition(this->selected->getPosition());
				element->setTexture(this->elementTextureMap[elementPair.first]);
				this->elementsToSpawn.push_back(element);
				this->renderObjects.push_back(element);
			}
		}
	}
}

std::vector<int> Game::resolveCollisionsEnemy(Bullet& bullet, float size) {
	std::vector<int> hitIndexes;

	for (size_t i = 0; i < this->enemies.size(); i++) {
		if (this->enemies[i]->shouldDraw) {
			Vector2f pointOnRect;

			pointOnRect.x = clamp(bullet.getPosition().x, this->enemies[i]->getPosition().x - 32, this->enemies[i]->getPosition().x + 32);
			pointOnRect.y = clamp(bullet.getPosition().y, this->enemies[i]->getPosition().y - 32, this->enemies[i]->getPosition().y + 32);

			float length = sqrt((pointOnRect - bullet.getPosition()).x * (pointOnRect - bullet.getPosition()).x + (pointOnRect - bullet.getPosition()).y * (pointOnRect - bullet.getPosition()).y);

			if (length < size) {
				hitIndexes.push_back(i);
			}
		}
	}

	return hitIndexes;
}

// return true if bullet hit player
bool Game::resolveCollisionsPlr(Bullet& bullet, float size) {
	Vector2f pointOnRect;

	pointOnRect.x = clamp(bullet.getPosition().x, this->plr->getPosition().x - 32, this->plr->getPosition().x + 32);
	pointOnRect.y = clamp(bullet.getPosition().y, this->plr->getPosition().y - 32, this->plr->getPosition().y + 32);

	float length = sqrt((pointOnRect - bullet.getPosition()).x * (pointOnRect - bullet.getPosition()).x + (pointOnRect - bullet.getPosition()).y * (pointOnRect - bullet.getPosition()).y);

	if (length < size) {
		return true;
	}
	return false;
}

void Game::update() {
	#ifdef FLAGS_MULTITHREADING
		this->window.setActive(false);
		Clock clockU;

		while (!this->shouldClose) {
			this->updateReady.acquire();

			if (clockU.getElapsedTime().asMicroseconds() > 10000) {
				for (int i = 0; i < 20; ++i) {
					Concurrency::parallel_for_each(std::begin(this->enemies), std::end(this->enemies), [this, clockU](Enemy* enemy) {
						if (enemy->shouldDraw) {
							enemy->aiMove(this->plr, this->iFrames, clockU.getElapsedTime().asSeconds(), this->enemies, this->dash, this->renderObjects, this->bullets);
						}
					});
				}

				for (int i = this->bullets.size() - 1; i >= 0; i--) {
					if (bullets[i]->shouldDraw) {
						this->bullets[i]->move(this->bullets[i]->direction * -600.f * clockU.getElapsedTime().asSeconds());
						this->bullets[i]->distance += hypotf((this->bullets[i]->direction * -600.f * clockU.getElapsedTime().asSeconds()).x, (this->bullets[i]->direction * -600.f * clockU.getElapsedTime().asSeconds()).y);

						if (this->bullets[i]->owner == 'p') {
							std::vector<int> indexes = this->resolveCollisionsEnemy(*this->bullets[i], 2);

							if (!indexes.empty()) {
								if (i < this->bullets.size()) {
									this->garbage.push_back(this->bullets[i]);
									this->bullets[i]->shouldDraw = false;
									std::cout << this->garbage.size() << '\n';
								}
							}
							else if (this->bullets[i]->distance > this->bullets[i]->maxDistance) {
								if (i < this->bullets.size()) {
									this->garbage.push_back(this->bullets[i]);
									this->bullets[i]->shouldDraw = false;
									std::cout << this->garbage.size() << '\n';
								}
							}

							if (!indexes.empty()) {
								for (int j = 0; j < indexes.size(); j++) {
									this->enemies[indexes[j]]->takeDamage(this->bullets[i]->damage);
									if (this->enemies[indexes[j]]->getHp() <= 0) {
										this->garbage.push_back(this->enemies[indexes[j]]);
										this->enemies[indexes[j]]->shouldDraw = false;
										std::cout << this->garbage.size() << '\n';
									}
								}
							}
						}
						else {
							bool hit = this->resolveCollisionsPlr(*this->bullets[i], 2);
							if (hit) {
								if (i < this->bullets.size()) {
									this->garbage.push_back(this->bullets[i]);
									this->bullets[i]->shouldDraw = false;
									std::cout << this->garbage.size() << '\n';
								}
							}
							else if (this->bullets[i]->distance > this->bullets[i]->maxDistance) {
								if (i < this->bullets.size()) {
									this->garbage.push_back(this->bullets[i]);
									this->bullets[i]->shouldDraw = false;
									std::cout << this->garbage.size() << '\n';
								}
							}

							if (hit) {
								this->plr->takeDamage(this->bullets[i]->damage);
								if (this->plr->health <= 0) {
									this->window.close();
									this->shouldClose = true;
								}
							}
						}
					}
				}

				for (Element* element : this->elements) {
					if (element->shouldDraw) {
						Vector2f elementToPlayer = element->getPosition() - this->plr->getPosition();
						if (hypotf(elementToPlayer.x, elementToPlayer.y) <= 57 && element->timeAlive.getElapsedTime().asSeconds() >= 0.2) {
							this->garbage.push_back(element);
							element->shouldDraw = false;
							continue;
						}
						element->direction += clamp(hypotf(elementToPlayer.x, elementToPlayer.y), 0, 100) * (elementToPlayer / hypotf(elementToPlayer.x, elementToPlayer.y) * clockU.getElapsedTime().asSeconds() * clamp(element->timeAlive.getElapsedTime().asSeconds(), 0, 2));

						element->move(element->direction * -300.f * clockU.getElapsedTime().asSeconds());
					}
				}

				clockU.restart();
			}
			this->updateReady.release();
		}
	#else
		for (int i = 0; i < 20; ++i) {
			Concurrency::parallel_for_each(std::begin(this->enemies), std::end(this->enemies), [this](Enemy* enemy) {
				enemy->aiMove(this->plr, this->iFrames, this->dt, this->enemies, this->dash);
			});
		}
	#endif
}

void Game::spawnElements() {
	for (int i = 0; i < this->elementsToSpawn.size(); ++i) {
		if (this->elementsToSpawn.at(i)->spawnClock.getElapsedTime().asSeconds() >= this->elementsToSpawn.at(i)->spawnTime) {
			this->elementsToSpawn.at(i)->shouldDraw = true;
			this->elementsToSpawn.at(i)->timeAlive.restart();
			this->elements.push_back(this->elementsToSpawn.at(i));
			this->elementsToSpawn.erase(std::begin(this->elementsToSpawn));
			break;
		}
	}
}

void Game::collectGarbage() {
	while (!this->shouldClose) {
		if (this->garbage.size() > 2000) {

			this->drawReady.acquire(); // spinlock until free
			this->updateReady.acquire(); // spinlock until free #2


			// delete all objects found in garbage
			deleteObjects(this->renderObjects, this->garbage);
			deleteObjects(this->enemies, this->garbage);
			deleteObjects(this->bullets, this->garbage);
			deleteObjects(this->elements, this->garbage);


			// Delete all objects in the garbage vector and clear the garbage vector
			for (auto obj : this->garbage) {
				delete obj;
			}
			this->garbage.clear();

			this->updateReady.release();
			this->drawReady.release();
		}
	}
}

int Game::randomLevel() {
	srand((unsigned)time(NULL));
	int random = rand() % 4;
	return random;
}