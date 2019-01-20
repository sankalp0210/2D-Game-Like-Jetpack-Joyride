#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    
    GLfloat vertex_buffer_data[100] = {
        -0.5f, -0.5f, 0, 
         0.5f, -0.5f, 0,
        -0.5f,  0.5f, 0, 
         0.5f,  0.5f, 0, 
         0.5f, -0.5f, 0,
        -0.5f,  0.5f, 0,
    };
    this->box.x = x -0.5;
    this->box.y = y -0.5;
    this->box.width  = 1;
    this->box.height = 1;
    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
// bool Magnet::operator()(const Magnet& a, const Magnet& b)
// {
//     return (a.position.x - b.position.x);
// }

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    // std::cout << this->position.x << " " << this->position.y << std::endl;
}
