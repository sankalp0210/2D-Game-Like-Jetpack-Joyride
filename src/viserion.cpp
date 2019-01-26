#include "viserion.h"
#include "main.h"

Viserion::Viserion(float x, float y, color_t color1, color_t color2) {
    this->position = glm::vec3(x, y, 0);
    this->speedVer = 0.05;
    this->bal = 1;
    this->score = 0;
    GLfloat vertex_buffer_data1[100] = {
        -1.0f, -0.5f, 0,
        -0.75f,  1.0f, 0,
         0.5f, -0.5f, 0,

         -0.5f, -0.5f, 0, 
         0.75f,  1.0f, 0,
          1.0f, -0.5f, 0,
    };
	GLfloat vertex_buffer_data2[100] = {
        -1.0f, -0.5f, 0, 
         1.0f, -2.5f, 0,
         1.0f, -0.5f, 0, 
        -1.0f, -0.5f, 0, 
         1.0f, -2.5f, 0,
        -1.0f, -2.5f, 0,
    };
    
	GLfloat vertex_buffer_data3[100] = {
        -2.5f,  0.25f, 0, 
        -1.0f, -1.25f, 0,
        -1.0f,  0.25f, 0, 
        -2.5f,  0.25f, 0,
        -1.0f, -1.25f, 0,
        -2.5f, -1.25f, 0,
    };
    GLfloat vertex_buffer_data4[100] = {
         1.0f, -2.0f, 0, 
         2.0f, -1.5f, 0,
         1.0f, -1.0f, 0,

         1.6f, -2.0f, 0, 
         2.6f, -1.5f, 0,
         1.6f, -1.0f, 0,
    };
    GLfloat vertex_buffer_data5[100] = {
        -0.8f, -3.0f, 0, 
        -0.4f, -2.5f, 0,
        -0.4f, -3.0f, 0, 
        -0.8f, -3.0f, 0, 
        -0.4f, -2.5f, 0,
        -0.8f, -2.5f, 0,

         0.8f, -3.0f, 0, 
         0.4f, -2.5f, 0,
         0.4f, -3.0f, 0, 
         0.8f, -3.0f, 0, 
         0.4f, -2.5f, 0,
         0.8f, -2.5f, 0,
    };
    this->box.x = x - 2;
    this->box.y = y - 3;
    this->box.width = 4;
    this->box.height = 4;

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color2, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_PURPLE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_RED, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, color2, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data5, color2, GL_FILL);
}

void Viserion::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
}

void Viserion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
 
void Viserion::tick() {
    if(this->bal > 1)
        this->bal+=2;
    if(this->bal == 20)
        this->bal = 1;
    
    // this->position.y += this->speedVer;
    // if(this->position.y < -0.5f){
    //     this->position.y = -0.5f;
    //     this->speedVer = 0.1;
    // }
    // if(this->position.y > 12.5f){
    //     this->position.y = 12.5f;
    //     this->speedVer = -0.1;
    // }
    this->box.x = this->position.x - 2;
    this->box.y = this->position.y - 3;
}
