#include "viserion.h"
#include "main.h"

Viserion::Viserion(float x, float y, color_t color1, color_t color2) {
    this->position = glm::vec3(x, y, 0);
    this->speedVer = 0.1;
    this->bal = 1;
    this->score = 0;
	GLfloat vertex_buffer_data[100] = {
        -1.0f, -0.5f, 0, 
         1.0f, -2.5f, 0,
         1.0f, -0.5f, 0, 
        -1.0f, -0.5f, 0, 
         1.0f, -2.5f, 0,
        -1.0f, -2.5f, 0,
    };
    int n = 500;
    GLfloat g_vertex_buffer_data[9*n+100];
	GLfloat deg = 2*3.1415926/((float)n), r = 0.75f;
    float x1 = r, y1 = 0.0f, z = 0.0f;
	for(int i=0;i<n;i++)
	{
		GLfloat o = deg*(i+1);
		g_vertex_buffer_data[9*i + 0] = z;
		g_vertex_buffer_data[9*i + 1] = z;
		g_vertex_buffer_data[9*i + 2] = z;
		g_vertex_buffer_data[9*i + 3] = x1;
		g_vertex_buffer_data[9*i + 4] = y1;
		g_vertex_buffer_data[9*i + 5] = z;
		g_vertex_buffer_data[9*i + 6] = x1 = (r*cos(o));
		g_vertex_buffer_data[9*i + 7] = y1 = (r*sin(o));
		g_vertex_buffer_data[9*i + 8] = z;
	}
    this->box.x = x - 1;
    this->box.y = y - 2.75;
    this->box.width = 2;
    this->box.height = 3;

    this->object1 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, color2, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color1, GL_FILL);
}

void Viserion::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Viserion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
 
void Viserion::tick() {
    if(this->bal > 1)
        this->bal+=2;
    if(this->bal == 120)
        this->bal = 1;
    
    this->position.y += this->speedVer;
    if(this->position.y < -1.0f){
        this->position.y = -1.0f;
        this->speedVer = 0.1;
    }
    if(this->position.y > 13.0f){
        this->position.y = 13.0f;
        this->speedVer = -0.1;
    }
    this->box.x = this->position.x - 1;
    this->box.y = this->position.y - 2.75;
}
