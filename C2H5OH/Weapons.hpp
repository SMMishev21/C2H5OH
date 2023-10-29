#include "precompile.hpp"
#include "RenderObject.hpp"

class Weapon : public RenderObject {

};

class Ranged : public Weapon {
public:
	void setRangedInfo(int damage, int clipSize, float bulletSpread, float maxDistance, float cooldown);
private:
	int damage;
	int clipSize;
	float bulletSpread;
	float maxDistance;
	float cooldown;
};

class Melee : public Weapon {
public:
	void setMeleeInfo(int damage, float range, float cooldown);
private:
	int damage;
	float range;
	float cooldown;
};
