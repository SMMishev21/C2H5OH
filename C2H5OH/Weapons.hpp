#include "precompile.hpp"
#include "RenderObject.hpp"
#include "Bullet.hpp"

class Ranged : public RenderObject {
public:
	void setRangedInfo(int damage, int clipSize, float bulletSpread, float maxDistance, float cooldown);
	void shoot(std::vector<Bullet*> &bullets, Clock& attackCD);
private:
	int damage;
	int clipSize;
	float bulletSpread;
	float maxDistance;
	float cooldown;
};

class Melee : public RenderObject {
public:
	void setMeleeInfo(int damage, float range, float cooldown);
	void swing();
private:
	int damage;
	float range;
	float cooldown;
};
