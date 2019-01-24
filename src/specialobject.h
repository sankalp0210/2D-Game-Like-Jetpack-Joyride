#include "main.h"

#ifndef SPECIALOBJECT_H
#define SPECIALOBJECT_H


class Specialobject {
public:
    Specialobject() {}
    Specialobject(float x, float y, color_t color1);
    glm::vec3 position;
    float r;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // Specialobject_H
