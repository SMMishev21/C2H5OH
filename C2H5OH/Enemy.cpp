#include "precompile.hpp"
#include "Enemy.hpp"

Color ColorFromHSV(float hue, float saturation, float value)
{
    Color color = { 0, 0, 0, 255 };

    // Red channel
    float k = fmodf((5.0f + hue / 60.0f), 6);
    float t = 4.0f - k;
    k = (t < k) ? t : k;
    k = (k < 1) ? k : 1;
    k = (k > 0) ? k : 0;
    color.r = (unsigned char)((value - value * saturation * k) * 255.0f);

    // Green channel
    k = fmodf((3.0f + hue / 60.0f), 6);
    t = 4.0f - k;
    k = (t < k) ? t : k;
    k = (k < 1) ? k : 1;
    k = (k > 0) ? k : 0;
    color.g = (unsigned char)((value - value * saturation * k) * 255.0f);

    // Blue channel
    k = fmodf((1.0f + hue / 60.0f), 6);
    t = 4.0f - k;
    k = (t < k) ? t : k;
    k = (k < 1) ? k : 1;
    k = (k > 0) ? k : 0;
    color.b = (unsigned char)((value - value * saturation * k) * 255.0f);

    return color;
}

void Enemy::init(Texture& texture, Vector2f position, char type) {
    this->sprite.setTexture(texture);
    this->sprite.setOrigin(Vector2f((float)(texture.getSize().x) / 2, (float)(texture.getSize().y) / 2));
    this->sprite.setPosition(position);
    this->type = type;
    this->hitbox->setRadius(this->getSize());
    this->hitbox->setPosition(this->getPosition());
    this->healthBar.setSize(Vector2f(100, 15));
    this->healthBar.setPosition(this->sprite.getPosition() - Vector2f(50, 40));
    this->healthBar.setFillColor(ColorFromHSV((100 * (this->hp * (this->hp / this->hp))) / 100, 1, 1));
}

void Enemy::move(Vector2f offset) {
    this->sprite.move(offset);
    this->hitbox->move(offset);
    this->hitbox->setPosition(this->hitbox->getPosition() + offset);
    this->healthBar.move(offset);
}

void Enemy::draw(RenderWindow& window) {
    window.draw(this->sprite);
    window.draw(this->healthBar);
}

void Enemy::aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets, std::mutex& m) {

}

void Enemy::takeDamage(float damage) {
    this->hp -= damage;
    this->healthBar.setSize(Vector2f(this->hp, 15));
    this->healthBar.setFillColor(ColorFromHSV(100.f * (100.f * (this->hp / 100.f)) / 100.f, 1, 1));
}

float Enemy::getHp() {
    return this->hp;
}