#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    int n = 500;
    GLfloat g_vertex_buffer_data[9*n+100];
	GLfloat deg = 2*3.1415926/((float)n), r1 = 15.5f, r2 = 12.5f;
    float x1 = r1, y1 = 0.0f, z = 0.0f;
	for(int i=0;i<n/2;i++){
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
    this->object1 = create3DObject(GL_TRIANGLES, n/2*3, g_vertex_buffer_data, color, GL_FILL);
    this->r1 = r1 - 1.0f;
    this->r2 = r2 - 0.5f;
    r1 -= 2.5f;
    r2 -= 3.5f; 
    x1 = r1, y1 = 0.0f, z = 0.0f;
    for(int i=0;i<n/2;i++) {
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
    this->object2 = create3DObject(GL_TRIANGLES, n/2*3, g_vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);
    this->centreX = x;
    this->centreY = y;
    this->angle = 180;
    this->box.height = 0.1f;
    this->box.width  = 1.6f;
    this->box.y = y;
    this->box.x = x - this->r1 + 0.8f;
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}
// bool Ring::operator()(const Ring& a, const Ring& b)
// {
//     return (a.position.x - b.position.x);
// }

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick() {
}
