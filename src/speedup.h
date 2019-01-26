#include "main.h"

#ifndef Speedup_H
#define Speedup_H


class Speedup {
public:
    Speedup() {}
    Speedup(float x, float y, color_t color1);
    glm::vec3 position;
    float r, rotation;
    int dir;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // Speedup_H
