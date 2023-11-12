#include "precompile.hpp"
#include "Enemy.hpp"

void Enemy::init(Texture& texture, Vector2f position, char type) {
    this->sprite.setTexture(texture);
    this->sprite.setOrigin(Vector2f((float)(texture.getSize().x) / 2, (float)(texture.getSize().y) / 2));
    this->sprite.setPosition(position);
    this->type = type;
    this->hitbox->setRadius(this->getSize());
    this->hitbox->setPosition(this->getPosition());
    std::cout << this->hitbox->getRadius().x << " " << this->hitbox->getRadius().y << '\n';
}

void Enemy::move(Vector2f offset) {
    this->sprite.move(offset);
    this->hitbox->move(offset);
    this->hitbox->setPosition(this->hitbox->getPosition() + offset);
}

void Enemy::aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets) {

}

void Enemy::takeDamage(float damage) {
    this->hp -= damage;
}

float Enemy::getHp() {
    return this->hp;
}