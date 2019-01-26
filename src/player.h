#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color1,  color_t color2);
    glm::vec3 position;
    float rotation;
    int dir1, dir2, bal, jet, score, lives, speedup, shield;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedVer, speedHor, speed, speedInc;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *objectShield1;
    VAO *objectShield2;
};

#endif // PLAYER_H
