#include "precompile.hpp"
#include "RenderObject.hpp"


float clampMax(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}

float clampMin(float n, float lower, float upper) {
	return std::min(upper, std::max(lower, n));
}

void RenderObject::init(Texture& texture, Vector2f position, char type) {
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(Vector2f((float)(texture.getSize().x) / 2, (float)(texture.getSize().y) / 2));
	this->sprite.setPosition(position);
	this->type = type;
}

void RenderObject::move(Vector2f offset) {
	this->sprite.move(offset);
}

void RenderObject::draw(RenderWindow& window) {
	window.draw(this->sprite);
}

void RenderObject::setOrigin(Vector2f origin) {
	this->sprite.setOrigin(origin);
}

void RenderObject::setPosition(Vector2f position) {
	this->sprite.setPosition(position);
}

Vector2f RenderObject::getPosition() {
	return this->sprite.getPosition();
}

void RenderObject::setTexture(Texture& texture) {
	this->sprite.setTexture(texture);
}

void RenderObject::setScale(Vector2f scale) {
	this->sprite.setScale(scale);
}

Vector2f RenderObject::getSize() {
	return Vector2f(this->sprite.getTexture()->getSize());
}

Sprite RenderObject::getSprite() {
	return this->sprite;
}