#include "boomerang.h"
#include "main.h"

Boomerang::Boomerang(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    float r = 0.5f;
    GLfloat vertex_buffer_data[40] = {
         0.0f,  0.0f, 0, 
            r,    -r, 0,
            r,     r, 0, 
         0.0f,  0.0f, 0, 
            r,     r, 0,
           -r,     r, 0,
         0.0f,  0.0f, 0, 
           -r,     r, 0,
           -r,    -r, 0,
    }; 
    this->a = 8;
    this->b = 4;
    this->r = r;
    this->angle = 0;
    this->rotation = 0;
    this->centreX = x - this->a;
    this->centreY = y;
    this->box.x = x -r;
    this->box.y = y -r;
    this->box.width  = 2*r;
    this->box.height = 2*r;
    
    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate   = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() {
    this->rotation += 20.0f;
    this->angle += 0.02f;
    this->position.x = this->centreX + this->a*cos(this->angle);
    this->position.y = this->centreY + this->b*sin(this->angle);
    this->box.x = this->position.x -this->r;
    this->box.y = this->position.y -this->r;
}
