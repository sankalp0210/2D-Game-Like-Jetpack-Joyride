#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y, color_t color, int score) {
    this->position = glm::vec3(x, y, 0);
    this->score = score;
    int n = 50;
    GLfloat g_vertex_buffer_data[9*n+100];
	GLfloat deg = 2*3.1415926/((float)n), r = 0.25f;
    float x1 = r, y1 = 0.0f, z = 0.0f;
	for(int i=0;i<n;i++){
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
    this->box.x = x -r;
    this->box.y = y -r;
    this->box.width  = 2*r;
    this->box.height = 2*r;
    
    this->object = create3DObject(GL_TRIANGLES, (n)*3, g_vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
// bool Coin::operator()(const Coin& a, const Coin& b)
// {
//     return (a.position.x - b.position.x);
// }

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin::tick() {
    // std::cout << this->position.x << " " << this->position.y << std::endl;
}
