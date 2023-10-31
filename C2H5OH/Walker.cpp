#include "Walker.hpp"

void Walker::aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash) {
	Vector2f distanceFromPlayer = plr->getPosition() - this->getPosition();
	float hypotenuse = sqrt(distanceFromPlayer.x * distanceFromPlayer.x + distanceFromPlayer.y * distanceFromPlayer.y);
	
	if (hypotenuse < 60000) {
		if (hypotenuse > 47) {
			this->move(((distanceFromPlayer / hypotenuse * 155.f) * dt) / 20.f);
		}
		else {
			if (iFrames.getElapsedTime().asSeconds() > 0.4 && dash) {
				iFrames.restart();
				//this->healthBar.setSize(this->healthBar.getSize() - Vector2f(40, 0));
				plr->health -= 10;
			}

			this->move((distanceFromPlayer * dt * -100.f) / 20.f);
		}
	}

	Vector2f distanceFromOthers;

	// move by overlap * dt * speed
	for (Enemy* enemy : enemies) {
		if (enemy->shouldDraw) {
			distanceFromOthers = enemy->getPosition() - this->getPosition();
			hypotenuse = sqrt(distanceFromOthers.x * distanceFromOthers.x + distanceFromOthers.y * distanceFromOthers.y);
			if (hypotenuse < 50) {
				this->move((distanceFromOthers * dt * -15.f) / 20.f);
			}
		}
	}
}