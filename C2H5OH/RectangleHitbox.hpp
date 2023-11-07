#include "precompile.hpp"

class RectangleHitbox {
private:
	Vector2f position;
	Vector2f size;

public:

	void setPosition(Vector2f newPosition);
	Vector2f getPosition();
	void setSize(Vector2f newSize);
	Vector2f getSize();
};