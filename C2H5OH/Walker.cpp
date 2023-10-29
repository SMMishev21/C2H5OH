#include "Walker.hpp"

void Walker::aiMove(Player* plr, Clock& iFrames, Time& dt, std::vector<Enemy*>& enemies, bool& dash) {
	Vector2f distanceFromPlayer = plr->getPosition() - this->getPosition();
	float hypotenuse = sqrt(distanceFromPlayer.x * distanceFromPlayer.x + distanceFromPlayer.y * distanceFromPlayer.y);

	if (hypotenuse < 600) {
		if (hypotenuse > 47) {
			this->move((distanceFromPlayer / hypotenuse * 155.f) * dt.asSeconds());
		}
		else {
			if (iFrames.getElapsedTime().asSeconds() > 0.4 && dash) {
				iFrames.restart();
				//this->healthBar.setSize(this->healthBar.getSize() - Vector2f(40, 0));
				plr->health -= 10;
			}
		}
	}
}