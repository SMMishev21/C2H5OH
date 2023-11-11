#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"

class RectangleHitbox : public RenderObject {
private:
	Vector2f position;
	Vector2f size;

public:

	void setPosition(Vector2f newPosition);
	Vector2f getPosition();
	void setSize(Vector2f newSize);
	Vector2f getSize();
};