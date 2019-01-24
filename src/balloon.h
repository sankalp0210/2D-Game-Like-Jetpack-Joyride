#include "main.h"

#ifndef BALLOON_H
#define BALLOON_H


class Balloon {
public:
    Balloon() {}
    Balloon(float x, float y);
    glm::vec3 position;
    float rotation;
    int dir1;
    int dir2;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedVer, speedHor;
private:
    VAO *object1;
    VAO *object2;
};

#endif // Balloon_H
