#ifndef OBJECT_H
#define OBJECT_H
#define PLAYER_WIDTH 0.15
#define PLAYER_HEIGHT 0.15
#define BULLET_RADIUS 0.01f
#define BULLET_SPEED 0.01f
#define PI 3.14159265358979323846
#include <vector>
#include "../mode.h"
#include <random>

typedef struct triangle {
    float x;
    float y;
    float width;
    float height;
} triangle;

typedef struct rectangle {
    float x;
    float y;
    float width;
    float height;
} rectangle;

typedef struct Position {
    float x;
    float y;
} Position;

enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    UPRIGHT,
    UPLEFT,
    DOWNRIGHT,
    DOWNLEFT,
};

enum BulletType {
    NORMAL_UP,
    NORMAL_DOWN,
    NORMAL_RIGHT,
    NORMAL_LEFT,
    NORMAL_UPRIGHT,
    NORMAL_UPLEFT,
    NORMAL_DOWNRIGHT,
    NORMAL_DOWNLEFT,
};

enum Owner {
    PLAYER,
    ENEMY
};

extern int over;

class Object {

protected:
    Position position;

public:
    Position get_position() { return position; }
    float move_up(float d) { if (position.y + d < 0.98) position.y += d; return position.y; };
    float move_down(float d) { if (position.y - d > 0) position.y -= d; return position.y; };
    float move_right(float d) { if (position.x + d + PLAYER_WIDTH < 1) position.x += d; return position.x; };
    float move_left(float d) { if (position.x - d > 0) position.x -= d; return position.x; };
};

#endif