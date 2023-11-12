#include "precompile.hpp"
#include "RangedBoss.hpp"

RangedBoss::RangedBoss() {
    this->bulletTexture.loadFromFile("./assets/bullet.png");
    this->damage = 10.f;
    this->attackStepSize[0] = 1;
    this->attackStepSize[1] = 36;
    this->attackStepSize[2] = 3;
    this->attack = rand() % 3;
    this->timeBetweenShots = 1.f;
    this->hp = 50000;
}

void RangedBoss::init(Texture& texture, Vector2f position, char type) {
    this->sprite.setTexture(texture);
    this->sprite.setOrigin(Vector2f((float)(texture.getSize().x) / 2, (float)(texture.getSize().y) / 2));
    this->sprite.setPosition(position);
    this->type = type;
    this->hitbox->setRadius(this->getSize());
    this->hitbox->setPosition(this->getPosition());
    this->healthBar.setSize(Vector2f(100, 15));
    this->healthBar.setPosition(this->sprite.getPosition() - Vector2f(50, 40));
    this->healthBar.setFillColor(ColorFromHSV((100 * (this->hp * (this->hp / this->hp))) / 50000, 1, 1));
}

void RangedBoss::takeDamage(float damage) {
    this->hp -= damage;
    this->healthBar.setSize(Vector2f(100 * (this->hp / 50000), 15));
    this->healthBar.setFillColor(ColorFromHSV(100.f * (50000 * (this->hp / 50000)) / 50000, 1, 1));
}

void RangedBoss::aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets, std::mutex& m) {
    Vector2f distanceFromPlayer = plr->getPosition() - this->getPosition();
    float hypotenuse = sqrt(distanceFromPlayer.x * distanceFromPlayer.x + distanceFromPlayer.y * distanceFromPlayer.y);
    bool shouldMove = true;

    if (hypotenuse < 400) {
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
        shoot(plr, renderObjects, bullets, m);
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

void RangedBoss::shoot(Player* plr, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets, std::mutex& m) {
    if (shootTimer.getElapsedTime().asSeconds() >= this->timeBetweenShots) {
        Vector2f gunPosition = this->getPosition();
        Vector2f playerPosition = plr->getPosition();

        if (attackStepSize[attack] <= step) {
            attack = rand() % 3;
            this->step = 0;
        }

        if (attack == 0) {
            if (this->step == 0) {
                this->timeBetweenShots = 2.f;
            }
            for (angle = 0; angle < 360; angle += 30) {
                Vector2f direction(cos(angle * 3.14159265359 / 180), sin(angle * 3.14159265359 / 180));
                Bullet* bullet = new Bullet(10, 2500, 'e');
                bullet->setTexture(bulletTexture);
                bullet->setOrigin(Vector2f(4, 4));
                bullet->setPosition(gunPosition);
                bullet->direction = direction / hypotf(direction.x, direction.y);
                bullet->speed = -400.f;

                m.lock();
                    bullets.push_back(bullet);
                    renderObjects.push_back(bullet);
                m.unlock();
            }
        }
        else if (attack == 1) {
            if (this->step == 0) {
                this->angle = 0;
                this->timeBetweenShots = 0.02;
            }
            Vector2f direction(cos(angle * 3.14159265359 / 180), sin(angle * 3.14159265359 / 180));
            Bullet* bullet = new Bullet(10, 2500, 'e');
            bullet->setTexture(bulletTexture);
            bullet->setOrigin(Vector2f(4, 4));
            bullet->setPosition(gunPosition);
            bullet->direction = direction / hypotf(direction.x, direction.y);
            bullet->speed = -500.f;

            m.lock();
                bullets.push_back(bullet);
                renderObjects.push_back(bullet);
            m.unlock();

            angle += 10;

            if (this->attackStepSize[this->attack] - 1 == this->step) {
                this->timeBetweenShots = 1.4f;
            }
        }
        else if (attack == 2) {
            if (this->step == 0) {
                this->timeBetweenShots = 0.02;
            }
            Vector2f direction = gunPosition - playerPosition;
            Bullet* bullet = new Bullet(this->damage, 2500, 'e');
            bullet->setTexture(bulletTexture);
            bullet->setOrigin(Vector2f(4, 4));
            bullet->setPosition(gunPosition);
            bullet->direction = direction / hypotf(direction.x, direction.y);
            bullet->speed = -700.f;

            m.lock();
                bullets.push_back(bullet);
                renderObjects.push_back(bullet);
            m.unlock();

            if (this->attackStepSize[this->attack] - 1 == this->step) {
                this->timeBetweenShots = 2.f;
            }
        }
        step++;
        this->shootTimer.restart();
    }
}