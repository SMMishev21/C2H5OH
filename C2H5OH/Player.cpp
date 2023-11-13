#include "precompile.hpp"
#include "Player.hpp"

void Player::init(Texture& texture, Vector2f position, char type) {
	this->hitbox = new EllipseHitbox;
	this->hitbox->setRadius(Vector2f(124 / 2, 354 / 2));
	this->hitbox->setPosition(position);
	this->collisionHitbox = new EllipseHitbox;
	this->collisionHitbox->setRadius(Vector2f(48, 22));
	this->collisionHitbox->setOrigin(Vector2f(48/2, 0));
	this->collisionHitbox->setPosition(position + Vector2f(0, 50));
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(Vector2f((float)(texture.getSize().x) / 2, (float)(texture.getSize().y) / 2));
	this->sprite.setPosition(position);
	this->type = type;
}

void Player::setPlayerInfo(int health, float speed) {
	this->health = health;
	this->speed = speed;
}

void Player::takeDamage(int damage) {
	this->health -= damage;
}

void Player::move(Vector2f offset) {
	this->sprite.move(offset);
	this->hitbox->setPosition(this->hitbox->getPosition() + offset);
	this->collisionHitbox->setPosition(this->collisionHitbox->getPosition() + offset);
}

void Player::setPosition(Vector2f newPosition) {
	this->sprite.setPosition(newPosition);
	this->hitbox->setPosition(newPosition);
	this->collisionHitbox->setPosition(newPosition + Vector2f(0, 50));
}