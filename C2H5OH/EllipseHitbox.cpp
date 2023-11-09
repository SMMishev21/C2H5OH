#include "EllipseHitbox.hpp"

Vector2f EllipseHitbox::getPosition() {
	return this->position;
}

void EllipseHitbox::setPosition(Vector2f newPosition) {
	this->position = newPosition;
}

Vector2f EllipseHitbox::getRadius() {
	return this->radius;
}

void EllipseHitbox::setRadius(Vector2f newRadius) {
	this->radius = newRadius;
}

Vector2f EllipseHitbox::checkOverlapRectangle(Vector2f rectanglePosition, Vector2f rectangleSize) {
	Vector2f closestPoint = Vector2f(clampMax(this->position.x, rectanglePosition.x, rectanglePosition.x + rectangleSize.x), clampMax(this->position.y, rectanglePosition.y, rectanglePosition.y + rectangleSize.y));
	
	Vector2f distance = this->position - closestPoint;

	if ((distance.x * distance.x / (this->radius.x * this->radius.x) + distance.y * distance.y / (this->radius.y * this->radius.y)) <= 1) {
		Vector2f overlap = Vector2f(clampMin(rectanglePosition.x + rectangleSize.x - closestPoint.x, 0.f, this->radius.x), clampMin(rectanglePosition.y + rectangleSize.y - closestPoint.y, 0.f, this->radius.y));
		return overlap;
	}
	return Vector2f(-1,-1);

}