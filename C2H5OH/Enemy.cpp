#include "precompile.hpp"
#include "Enemy.hpp"

void Enemy::init(Texture& texture, Vector2f position, char type) {
    this->sprite.setTexture(texture);
    this->sprite.setOrigin(Vector2f((float)(texture.getSize().x) / 2, (float)(texture.getSize().y) / 2));
    this->sprite.setPosition(position);
    this->type = type;
    this->hitbox->setRadius(this->getSize());
    this->hitbox->setPosition(this->getPosition());
    this->healthBar.setSize(Vector2f(100, 15));
    this->healthBar.setPosition(this->sprite.getPosition() - Vector2f(50, 40));
    this->healthBar.setFillColor(Color::Green);
    std::cout << this->hitbox->getRadius().x << " " << this->hitbox->getRadius().y << '\n';
}

void Enemy::move(Vector2f offset) {
    this->sprite.move(offset);
    this->hitbox->move(offset);
    this->hitbox->setPosition(this->hitbox->getPosition() + offset);
    this->healthBar.move(offset);
}

void Enemy::draw(RenderWindow& window) {
    window.draw(this->sprite);
    window.draw(this->healthBar);
}

void Enemy::aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets) {

}

void Enemy::takeDamage(float damage) {
    this->hp -= damage;
    this->healthBar.setSize(Vector2f(this->hp, 15));
    if (this->hp < 35) {
        this->healthBar.setFillColor(Color::Red);
    }
    else if (this->hp < 75) {
        this->healthBar.setFillColor(Color::Yellow);
    }
}

float Enemy::getHp() {
    return this->hp;
}