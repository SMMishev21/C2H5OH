#include "Weapons.hpp"

void Ranged::setRangedInfo(int damage, int clipSize, float bulletSpread, float maxDistance, float cooldown){
	this->damage = damage;
	this->clipSize = clipSize;
	this->bulletSpread = bulletSpread;
	this->maxDistance = maxDistance;
	this->cooldown = cooldown;
}

void Ranged::shoot(std::vector<Bullet*>& bullets, Clock& attackCD) {
	if (attackCD.getElapsedTime().asSeconds() >= this->cooldown) {
		Bullet* bullet = new Bullet(this->damage, this->maxDistance, 'p');
		bullets.push_back(bullet);
	}
}

void Melee::setMeleeInfo(int damage, float range, float cooldown){
	this->damage = damage;
	this->range = range;
	this->cooldown = cooldown;
}
