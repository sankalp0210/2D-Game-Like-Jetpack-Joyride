#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color1);
    glm::vec3 position;
    bounding_box_t box;
    bool operator<(const Magnet& a){
        return this->position.x < a.position.x;
    };
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // Magnet_H
