#include "main.h"

#ifndef ICEBALL_H
#define ICEBALL_H


class Iceball {
public:
    Iceball() {}
    Iceball(float x, float y);
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
    VAO *object;
};

#endif // Iceball_H
