#include "speedup.h"
#include "main.h"

Speedup::Speedup(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->dir = 1;
    this->rotation = 0.0f;
    GLfloat vertex_buffer_data[100] = {
         0.2f,  0.0f, 0, 
        -0.2f,  0.0f, 0,
         0.2f, -0.4f, 0, 
         0.2f, -0.4f, 0, 
        -0.2f, -0.4f, 0,
        -0.2f,  0.0f, 0,

         0.3f, 0.0f, 0.0f,
        -0.3f, 0.0f, 0.0f,
         0.0f, 0.4f, 0.0f,
    };
    
    this->r = r;
    this->box.x = x -0.2;
    this->box.y = y -0.4;
    this->box.width  = 2*0.4;
    this->box.height = 2*0.2;
    
    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, color, GL_FILL);
}

void Speedup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate   = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Speedup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Speedup::tick() {
    this->rotation += 5.0f;
    if(this->position.y > screen_center_y + 5)
        this->dir = -1;
    else if(this->position.y < screen_center_y - 1)
        this->dir = 1;
    this->position.x -= 0.03;
    this->position.y += this->dir*0.05;
    this->box.x = this->position.x -this->r;
    this->box.y = this->position.y -this->r;
}
