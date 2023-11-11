#include "precompile.hpp"
#include "clamp.hpp"
#include "RenderObject.hpp"

class EllipseHitbox : public RenderObject {
private:
	Vector2f position;
	Vector2f radius;

public:
	Vector2f getPosition();
	void setPosition(Vector2f newPosition);
	Vector2f getRadius();
	void setRadius(Vector2f newRadius);

	Vector2f checkOverlapRectangle(Vector2f rectanglePosition, Vector2f rectangleSize);
};