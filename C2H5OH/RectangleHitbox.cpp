#include "RectangleHitbox.hpp"

Vector2f RectangleHitbox::getPosition() {
	return this->position;
}

void RectangleHitbox::setPosition(Vector2f newPosition) {
	this->position = newPosition;
}

Vector2f RectangleHitbox::getSize() {
	return this->size;
}

void RectangleHitbox::setSize(Vector2f newSize) {
	this->size = newSize;
}