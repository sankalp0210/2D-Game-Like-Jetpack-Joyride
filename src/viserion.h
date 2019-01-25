#include "main.h"

#ifndef VISERION_H
#define VISERION_H


class Viserion {
public:
    Viserion() {}
    Viserion(float x, float y, color_t color1,  color_t color2);
    glm::vec3 position;
    int bal, score;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedVer, speedHor;
private:
    VAO *object1;
    VAO *object2;
};

#endif // Viserion_H
