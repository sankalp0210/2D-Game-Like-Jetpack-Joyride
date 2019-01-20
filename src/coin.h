#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y, color_t color1);
    glm::vec3 position;
    bounding_box_t box;
    bool operator<(const Coin& a){
        return this->position.x < a.position.x;
    };
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // COIN_H
