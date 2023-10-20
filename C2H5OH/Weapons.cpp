#include "Weapons.h"

void Ranged::setRangedInfo(int damage, int clipSize, float bulletSpread, float maxDistance, float cooldown){
	this->damage = damage;
	this->clipSize = clipSize;
	this->bulletSpread = bulletSpread;
	this->maxDistance = maxDistance;
	this->cooldown = cooldown;
}

void Melee::setMeleeInfo(int damage, float range, float cooldown){
	this->damage = damage;
	this->range = range;
	this->cooldown = cooldown;
}
