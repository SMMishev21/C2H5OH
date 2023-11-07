#include "precompile.hpp"

class CircleHitbox {
private:
	Vector2f position;
	float radius;

public:
	Vector2f getPosition();
	void setPosition(Vector2f newPosition);
	float getRadius();
	void setRadius(float newRadius);
};