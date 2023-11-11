#pragma once
#include "precompile.hpp"
#include "Player.hpp"
#include "Square.hpp"
#include "Walker.hpp"
#include "RangedEnemy.hpp"
#include "Weapons.hpp"
#include "Enemy.hpp"
#include "Chest.hpp"
#include "Item.hpp"
#include "RectangleHitbox.hpp"
#include <thread>
#include <semaphore>

#define FLAGS_MULTITHREADING

using namespace sf;

class Game {
private:
    float dt;
    float dashDistance;
    bool shouldClose;
    bool dash;
    bool lab;

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
    Texture carbonTexture;
    Texture oxygenTexture;
    Texture hydrogenTexture;
    Texture nitrogenTexture;
    Texture roomTexture;
    Texture squareHitboxTexture;
    Texture ellipseHitboxTexture;

    Font font;

    Text carbonText;
    Text oxygenText;
    Text hydrogenText;
    Text nitrogenText;

    Text compound;

    RectangleShape square4, square1, square2, square3;

    RenderObject* room;

    View view;
    Clock clock;
    Vector2f plrVelocity;
    Vector2f dir;
    Vector2f dashed;
    Clock dashClock;
    Clock iFrames;
    Clock attackCD;
    Clock labCD;

    Ranged* ak;
    Player* plr;
    Chest* chest;
    RenderObject* key;
    Chest* selected;

    std::vector<Bullet*> bullets;
    std::vector<Enemy*> enemies;
    std::vector<RenderObject*> renderObjects;
    std::vector<Chest*> chests;
    std::vector<Element*> elements;
    std::vector<Element*> elementsToSpawn;
    std::vector<RenderObject*> garbage;
    std::vector<RectangleHitbox*> hitboxes;

    std::unordered_map<std::string, Texture> elementTextureMap;

    friend class RangedEnemy;

    void mainLoop();
    void handleInput(float dt);
    void draw();
    void handleMovement();
    void handleEnemies();
    void collectGarbage();
    void update();
    void spawnElements();
    void openLab();
    void drawLab();
    bool resolveCollisionsPlr(Bullet& bullet, float size);
    bool resolveCollisions(RenderObject& obj, float radius);
    std::vector<int> resolveCollisionsEnemy(Bullet& bullet, float size);
    int randomLevel();

public:
    Game();
    ~Game();
};