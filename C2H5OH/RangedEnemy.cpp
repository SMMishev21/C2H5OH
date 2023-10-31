#include "RangedEnemy.hpp"
#include <iostream>

RangedEnemy::RangedEnemy() {
    this->bulletTexture.loadFromFile("./assets/bullet.png");
}

void RangedEnemy::aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets) {
    Vector2f distanceFromPlayer = plr->getPosition() - this->getPosition();
    float hypotenuse = sqrt(distanceFromPlayer.x * distanceFromPlayer.x + distanceFromPlayer.y * distanceFromPlayer.y);
    bool shouldMove = true;

    if (hypotenuse < 200) {
        shouldMove = false;
    }

    if (shouldMove) {
        if (hypotenuse > 47) {
            this->move(((distanceFromPlayer / hypotenuse * 155.f) * dt) / 20.f);
        }
        else {
            if (iFrames.getElapsedTime().asSeconds() > 0.4 && dash) {
                iFrames.restart();
                plr->health -= 10;
            }
            this->move((distanceFromPlayer * dt * -100.f) / 20.f);
        }
    }
    else {
        shoot(plr, renderObjects, bullets);
    }

    Vector2f distanceFromOthers;
    for (Enemy* enemy : enemies) {
        distanceFromOthers = enemy->getPosition() - this->getPosition();
        hypotenuse = sqrt(distanceFromOthers.x * distanceFromOthers.x + distanceFromOthers.y * distanceFromOthers.y);
        if (hypotenuse < 65) {
            this->move((distanceFromOthers * dt * -15.f) / 20.f);
        }
    }
}

void RangedEnemy::shoot(Player* plr, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets) {
    if (shootTimer.getElapsedTime().asSeconds() >= 3.0f) {
        shootTimer.restart();

        Vector2f gunPosition = this->getPosition();
        Vector2f playerPosition = plr->getPosition();

        Vector2f direction = gunPosition - playerPosition;
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);

        direction /= length;
        std::cout << direction.x << " " << direction.y << std::endl;

        Bullet* bullet = new Bullet(10, 2500, 'e');
        bullet->setTexture(bulletTexture);
        bullet->setOrigin(Vector2f(4, 4));
        bullet->setPosition(gunPosition);
        bullet->direction = direction;

        bullets.push_back(bullet);
        renderObjects.push_back(bullet);
    }
}