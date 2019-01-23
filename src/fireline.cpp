#include "fireline.h"
#include "main.h"

Fireline::Fireline(float x, float y, color_t color1, color_t color2, float angle) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = angle;
    float var = 0.5f;
    float len = 6.0f;
    GLfloat vertex_buffer_data[40] = {
         0.0f,  0.0f, 0, 
         0.5f,  0.0f, 0,
         0.5f,  0.5f, 0, 
         0.0f,  0.0f, 0, 
         0.0f,  0.5f, 0,
         0.5f,  0.5f, 0,

         len+0.5f,  0.0f, 0, 
         len+1.0f,  0.0f, 0,
         len+1.0f,  0.5f, 0, 
         len+0.5f,  0.0f, 0, 
         len+0.5f,  0.5f, 0,
         len+1.0f,  0.5f, 0,
    };
    GLfloat g_vertex_buffer_data[20] = {
         0.5f    ,  0.15f, 0, 
         len+0.5f,  0.15f, 0,
         len+0.5f,  0.35f, 0, 
         0.5f    ,  0.15f, 0, 
         0.5f    ,  0.35f, 0,
         len+0.5f,  0.35f, 0,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color1, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, g_vertex_buffer_data, color2, GL_FILL);
    this->box.x = x;
    this->box.y = y;
    this->box.height = 0.5f;
    this->box.width = len + 0.5f;
}

void Fireline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fireline::tick() {
    if(this->position.x < (screen_center_x - 8))
        this->position.x += 40;
}
