#include "EllipseHitbox.hpp"

Vector2f EllipseHitbox::getPosition() {
	return this->position;
}

void EllipseHitbox::setPosition(Vector2f newPosition) {
	this->sprite.setPosition(newPosition);
	this->position = newPosition;
}

Vector2f EllipseHitbox::getRadius() {
	return this->radius;
}

void EllipseHitbox::setRadius(Vector2f newRadius) {
	this->radius = newRadius;
}

Vector2f EllipseHitbox::checkOverlapRectangle(Vector2f rectanglePosition, Vector2f rectangleSize) {
	Vector2f closestPoint(clampMax(this->position.x, rectanglePosition.x, rectanglePosition.x + rectangleSize.x), clampMax(this->position.y, rectanglePosition.y, rectanglePosition.y + rectangleSize.y));

	float inEllipse = (((closestPoint.x - this->position.x) * (closestPoint.x - this->position.x)) / std::max(this->radius.x, this->radius.y)) + (((closestPoint.y - this->position.y) * (closestPoint.y - this->position.y)) / (std::min(this->radius.x, this->radius.y)));

	if (inEllipse <= 1) {
		return closestPoint - this->position;
	}

	return Vector2f(0,0);

}