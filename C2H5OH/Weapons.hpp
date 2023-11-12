#include "precompile.hpp"
#include "RenderObject.hpp"
#include "Bullet.hpp"
#include "Player.hpp"

class Ranged : public RenderObject {
public:
	void setRangedInfo(int damage, int clipSize, float bulletSpread, float maxDistance, float cooldown);
	void shoot(std::vector<Bullet*>& bullets, std::vector<RenderObject*>& renderObjects, RenderWindow& window, Player* plr, Texture& bulletTexture, Clock& attackCD, float speedBuff);
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
