#include "firebeam.h"
#include "main.h"

Firebeam::Firebeam(float x, float y, color_t color1, color_t color2) {
    this->position = glm::vec3(x, y, 0);
    this->originY = y;
    float var = 1.0f;
    float len = 6.0f;
    this->dir = 1;
    GLfloat vertex_buffer_data[40] = {
         0.0f,  0.0f, 0, 
         1.0f,  0.0f, 0,
         1.0f,  1.0f, 0, 
         0.0f,  0.0f, 0, 
         0.0f,  1.0f, 0,
         1.0f,  1.0f, 0,

         len+1.0f,  0.0f, 0, 
         len+2.0f,  0.0f, 0,
         len+2.0f,  1.0f, 0, 
         len+1.0f,  0.0f, 0, 
         len+1.0f,  1.0f, 0,
         len+2.0f,  1.0f, 0,
    };
    GLfloat g_vertex_buffer_data[20] = {
         1.0f    ,  0.4f, 0, 
         len+1.0f,  0.4f, 0,
         len+1.0f,  0.6f, 0, 
         1.0f    ,  0.4f, 0, 
         1.0f    ,  0.6f, 0,
         len+1.0f,  0.6f, 0,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color1, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, g_vertex_buffer_data, color2, GL_FILL);
    this->box.x = x;
    this->box.y = y;
    this->box.width = len+2;
    this->box.height = 0.2;
    this->time = 0;
    this->col = 0;
    this->existTime = 12;
}

void Firebeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->time > 0) {
        draw3DObject(this->object1);
        if(this->time > 2*60){
            draw3DObject(this->object2);
        }
    }
}

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam::tick() {
    this->position.x = screen_center_x - 4;
    if(this->time > 0)
        this->time++;
    if(this->time > 2*60)
        this->col = 1;
    if(this->time > 3*60)
        this->position.y += this->dir*0.02f;
    
    if(this->position.y > this->originY + 2)
        this->dir = -1;
    if(this->position.y < this->originY - 2)
        this->dir = 1;
    if(this->time > 60*this->existTime){
        this->time = 0;
        this->col = 0;
    }
    this->box.x = this->position.x;
    this->box.y = this->position.y;
    
}
