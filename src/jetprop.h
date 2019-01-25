#include "main.h"

#ifndef JETPROP_H
#define JETPROP_H


class Jetprop {
public:
    Jetprop() {}
    Jetprop(float x, float y);
    glm::vec3 position;
    float originY;
    int dir1;
    int dir2;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedVer;
private:
    VAO *object;
};

#endif // Jetprop_H
