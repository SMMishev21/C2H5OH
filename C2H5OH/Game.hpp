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
#include "RangedBoss.hpp"
#include <thread>

#define FLAGS_MULTITHREADING
//#define FLAGS_DEBUGGING

using namespace sf;

class Game {
private:
    int roomNumber;
    int reverse;
    float dt;
    float dashDistance;
    float speedBuff;
    float attackSpeedBuff;
    float healthBuff;
    float damageBuff;
    bool shouldClose;
    bool dash;
    bool lab;
    bool dashInvincibility;
    std::string currentRoom;

    std::counting_semaphore<1> drawReady{ 1 };
    std::counting_semaphore<1> updateReady{ 1 };

    std::mutex m;

    RenderWindow window;
    Event ev;
    
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
    Texture walkerTexture;
    Texture rangedEnemyTexture;
    Texture rangedBossTexture;
    Texture squareHitboxTexture;
    Texture ellipseHitboxTexture;
    Texture invCarbon;
    Texture invNitro;
    Texture invHydrogen;
    Texture invOxygen;
    Texture backgroundImage;
    Texture trenImg;
    Texture coffeeImg;
    Texture bossRoomTexture;
    Texture plrLeftTexture;
    Texture plrRightTexture;
    Texture gunTexture;

    Sprite invBg;

    Font font;

    Text carbonText;
    Text oxygenText;
    Text hydrogenText;
    Text nitrogenText;

    Text carbonInfo;
    Text oxygenInfo;
    Text hydrogenInfo;
    Text nitrogenInfo;

    Text coffee;
    Text tren;

    RectangleShape square4, square1, square2, square3, trenSqrt, coffeeSqrt;
    RectangleShape healthBar;

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
    Clock dashIFrames;

    Ranged* gun;
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

    std::unordered_map<std::string, Texture> elementTextureMap;
    std::unordered_map<std::string, Texture> enemyTextureMap;
    std::unordered_map<std::string, std::vector<RectangleHitbox*>> roomCollisions;

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
    bool resolveCollisionsPlr(Bullet& bullet, Vector2f size);
    bool resolveCollisions(RenderObject& obj, float radius);
    std::vector<int> resolveCollisionsEnemy(Bullet& bullet, float size);
    int randomLevel();
    void prepareRoom();

public:
    Game();
    ~Game();
};