#include "precompile.hpp"
#include "RangedEnemy.hpp"

class RangedBoss : public RangedEnemy {
private:
    Clock shootTimer;
    Texture bulletTexture;

    int lastAttack;
    int step;
    int attackStepSize[3];
    int attack;
    float timeBetweenShots;
    float angle;
public:
    RangedBoss();
    void init(Texture& texture, Vector2f position, char type) override;
    void takeDamage(float damage);
    void aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets) override;
    void shoot(Player* plr, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets);
};