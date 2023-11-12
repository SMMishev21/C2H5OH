#include "precompile.hpp"
#include "Weapons.hpp"

void Ranged::setRangedInfo(int damage, int clipSize, float bulletSpread, float maxDistance, float cooldown){
	this->damage = damage;
	this->clipSize = clipSize;
	this->bulletSpread = bulletSpread;
	this->maxDistance = maxDistance;
	this->cooldown = cooldown;
}

void Ranged::shoot(std::vector<Bullet*>& bullets, std::vector<RenderObject*>& renderObjects, RenderWindow& window, Player* plr, Texture& bulletTexture, Clock& attackCD, float speedBuff) {
	if (attackCD.getElapsedTime().asSeconds() >= this->cooldown * speedBuff) {
		attackCD.restart();
		Vector2f gunPosition = this->getPosition(), mousePosition = window.mapPixelToCoords(Mouse::getPosition(window)), playerPosition = plr->getPosition();
		Vector2f mouseToGun = gunPosition - mousePosition;
		Vector2f mouseToGunNorm = mouseToGun / hypotf(mouseToGun.x, mouseToGun.y);

		Bullet* bullet = new Bullet(this->damage, this->maxDistance, 'p');
		bullet->setTexture(bulletTexture);
		bullet->setOrigin(Vector2f(4, 4));
		bullet->setPosition(gunPosition);
		
		Vector2f distance = playerPosition - mousePosition;
		float angle = atan2(distance.y, distance.x);

		Vector2f start(playerPosition.x - 500 * cos(angle - this->bulletSpread * 3.14159265359 / 180), playerPosition.y - 500 * sin(angle - this->bulletSpread * 3.14159265359 / 180));
		Vector2f end(playerPosition.x - 500 * cos(angle + this->bulletSpread * 3.14159265359 / 180), playerPosition.y - 500 * sin(angle + this->bulletSpread * 3.14159265359 / 180));

		float percentage = (float)rand() / RAND_MAX;
		Vector2f spred(start.x * (1.0f - percentage) + end.x * percentage, start.y * (1.0f - percentage) + end.y * percentage);
		Vector2f distanceSpread = playerPosition - spred;

		Vector2f normalized = distanceSpread / hypotf(distanceSpread.x, distanceSpread.y);
		bullet->direction = normalized;
		bullet->speed = -600.f;

		bullets.push_back(bullet);
		renderObjects.push_back(bullet);
	}
}

void Melee::setMeleeInfo(int damage, float range, float cooldown){
	this->damage = damage;
	this->range = range;
	this->cooldown = cooldown;
}
