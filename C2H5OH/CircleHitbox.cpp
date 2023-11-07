#include "CircleHitbox.hpp"

Vector2f CircleHitbox::getPosition() {
	return this->position;
}

void CircleHitbox::setPosition(Vector2f newPosition) {
	this->position = newPosition;
}

float CircleHitbox::getRadius() {
	return this->radius;
}

void CircleHitbox::setRadius(float newRadius) {
	this->radius = newRadius;
}