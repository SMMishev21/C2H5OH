#include "precompile.hpp"

class Ranged {
public:
	void setRangedInfo(int damage, int clipSize, float bulletSpread, float maxDistance, float cooldown);
private:
	int damage;
	int clipSize;
	float bulletSpread;
	float maxDistance;
	float cooldown;
};

class Melee {
public:
	void setMeleeInfo(int damage, float range, float cooldown);
private:
	int damage;
	float range;
	float cooldown;
};
