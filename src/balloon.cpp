#include "balloon.h"
#include "main.h"

Balloon::Balloon(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speedVer = 0.2;
    this->speedHor = 0.1;
    
    int n = 500;
    GLfloat g_vertex_buffer_data[9*n+100];
	GLfloat deg = 2*3.1415926/((float)n), r1 = 0.40f, r2 = 0.30f;
    float x1 = r1, y1 = 0.0f, z = 0.0f;
	for(int i=0;i<n;i++)
	{
		GLfloat o = deg*(i+1);
		g_vertex_buffer_data[9*i + 0] = z;
		g_vertex_buffer_data[9*i + 1] = z;
		g_vertex_buffer_data[9*i + 2] = z;
		g_vertex_buffer_data[9*i + 3] = x1;
		g_vertex_buffer_data[9*i + 4] = y1;
		g_vertex_buffer_data[9*i + 5] = z;
		g_vertex_buffer_data[9*i + 6] = x1 = (r1*cos(o));
		g_vertex_buffer_data[9*i + 7] = y1 = (r2*sin(o));
		g_vertex_buffer_data[9*i + 8] = z;
	}
	GLfloat vertex_buffer_data[100] = {
               -r1,        r2, 0, 
        -r1 - 0.2f, r2 + 0.2f, 0,
        -r1 - 0.2f, r2 - 0.2f, 0, 
    };
    this->box.x = x - r1 - 0.2f;
    this->box.y = y - r2;
    this->box.width = 2*r1 + 0.2f;
    this->box.height = 2*r2;

    this->object1 = create3DObject(GL_TRIANGLES, n*3,g_vertex_buffer_data,COLOR_BALLOON, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data, COLOR_BALLOON, GL_FILL);
}

void Balloon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Balloon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Balloon::tick() {
    this->position.x += this->speedHor;
    this->speedVer -= 0.005;
    this->position.y += (float)this->speedVer;
    this->box.x = this->position.x - 0.6f;
    this->box.y = this->position.y - 0.3f;
}
