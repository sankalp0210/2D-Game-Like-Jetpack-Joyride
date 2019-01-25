#include "jetprop.h"
#include "main.h"

Jetprop::Jetprop(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->speedVer = -0.2;
    this->originY = y;
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

    this->object = create3DObject(GL_TRIANGLES, n*3,g_vertex_buffer_data,COLOR_JETPROP, GL_FILL);
}

void Jetprop::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Jetprop::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Jetprop::tick() {
    this->speedVer -= 0.005;
    this->position.y += (float)this->speedVer;
}
