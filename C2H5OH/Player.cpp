#include "Player.hpp"

void Player::init(Texture& texture, Vector2f position, char type) {
	this->rectangleHitbox.setPosition(position + Vector2f(20, 5));
	this->rectangleHitbox.setSize(Vector2f(128, 355));
	this->ellipseHitbox = new EllipseHitbox;
	this->ellipseHitbox->setRadius(Vector2f(48, 22));
	this->ellipseHitbox->setOrigin(Vector2f(48/2, 0));
	this->ellipseHitbox->setPosition(position + Vector2f(0, 20));
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
	this->rectangleHitbox.setPosition(this->ellipseHitbox->getPosition() + offset);
	this->ellipseHitbox->setPosition(this->ellipseHitbox->getPosition() + offset);
}