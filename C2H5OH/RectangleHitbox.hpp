#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"
#include "clamp.hpp"

class RectangleHitbox : public RenderObject {
private:
	Vector2f position;
	Vector2f size;
	RectangleShape wireMesh;

public:
	RectangleHitbox();
	RectangleHitbox(Vector2f position, Vector2f size);

	void setPosition(Vector2f newPosition);
	Vector2f getPosition();
	void setSize(Vector2f newSize);
	Vector2f getSize();

	Vector2f checkOverlapRectangle(Vector2f rectanglePosition, Vector2f rectangleSize);

	void draw(RenderWindow& window) override;
};