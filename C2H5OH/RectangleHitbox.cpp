#include "precompile.hpp"
#include "RectangleHitbox.hpp"

RectangleHitbox::RectangleHitbox() {

}

RectangleHitbox::RectangleHitbox(Vector2f position, Vector2f size) {
	this->setPosition(position);
	this->setSize(size);
	this->setOrigin(size / 2.f);
	this->wireMesh.setOutlineColor(Color::Green);
	this->wireMesh.setOutlineThickness(1);
	this->wireMesh.setOrigin(size / 2.f);
	this->wireMesh.setPosition(position);
	this->wireMesh.setSize(size);
}

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

Vector2f RectangleHitbox::checkOverlapRectangle(Vector2f rectanglePosition, Vector2f rectangleSize) {
	Vector2f closestPoint(clampMax(this->position.x, rectanglePosition.x, rectanglePosition.x + rectangleSize.x), clampMax(this->position.y, rectanglePosition.y, rectanglePosition.y + rectangleSize.y));

	Vector2f clamped(clampMax(closestPoint.x, this->position.x - this->size.x / 2, this->position.x + this->size.y / 2), clampMax(closestPoint.y, this->position.y - this->size.y / 2, this->position.y + this->size.y / 2));
	
	if (clamped.x == closestPoint.x && clamped.y == closestPoint.y) {
		return closestPoint - this->position;
	}
	return Vector2f(0, 0);
}

void RectangleHitbox::draw(RenderWindow& window) {
	window.draw(this->wireMesh);
}