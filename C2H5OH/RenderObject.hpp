#pragma once
#include "precompile.hpp"

float clampMax(float n, float lower, float upper);
float clampMin(float n, float lower, float upper);

class RenderObject {
protected:
	Sprite sprite;

public:
	virtual void init(Texture& texture, Vector2f position, char type);
	virtual void setPosition(Vector2f position);
	virtual void setOrigin(Vector2f origin);
	virtual void draw(RenderWindow& window);
	virtual void setScale(Vector2f scale);
	virtual void move(Vector2f offset);
	virtual Vector2f getPosition();
	Vector2f getSize();
	Sprite getSprite();

	void setTexture(Texture& texture);

	char type;
	bool shouldDraw{ true };
};