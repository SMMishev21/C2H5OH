#include "Player.hpp"


void Player::setPlayerInfo(int health, float speed) {
	this->health = health;
	this->speed = speed;
}

void Player::takeDamage(int damage) {
	this->health -= damage;
}

void Player::move(Vector2f offset) {
	this->rectangleHitbox.setPosition(this->rectangleHitbox.getPosition() + offset);
	this->ellipseHitbox.setPosition(this->ellipseHitbox.getPosition() + offset);
}