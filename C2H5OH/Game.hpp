#pragma once
#include "precompile.hpp"
#include "Player.hpp"
#include "Square.hpp"
#include "Walker.hpp"
#include "RangedEnemy.hpp"
#include "Weapons.hpp"
#include "Enemy.hpp"
#include "Chest.hpp"
#include <thread>
#include <semaphore>

#define FLAGS_MULTITHREADING

using namespace sf;

class Game {
private:
    float dt;
    bool shouldClose;
    bool dash;
    float dashDistance;

    std::counting_semaphore<1> drawReady{ 1 };
    std::counting_semaphore<1> updateReady{ 1 };

    RenderWindow window;
    Event ev;
    
    Texture plrTexture;
    Texture squareTexture;
    Texture bulletTexture;
    Texture enemyTexture;
    Texture akTexture;
    Texture chestTexture;
    Texture keyTexture;

    View view;
    Clock clock;
    Vector2f plrVelocity;
    Vector2f dir;
    Vector2f dashed;
    Clock dashClock;
    Clock iFrames;
    Clock attackCD;

    Ranged* ak;
    Player* plr;
    Chest* chest;
    RenderObject* key;

    std::vector<Bullet*> bullets;
    std::vector<Enemy*> enemies;
    std::vector<RenderObject*> renderObjects;

    std::vector<RenderObject*> garbage;

    friend class RangedEnemy;

    void mainLoop();
    void handleInput(float dt);
    void draw();
    void handleMovement();
    void handleEnemies();
    void collectGarbage();
    void update();
    bool resolveCollisionsPlr(Bullet& bullet, float size);
    std::vector<int> resolveCollisionsEnemy(Bullet& bullet, float size);

public:
    Game();
    ~Game();
};