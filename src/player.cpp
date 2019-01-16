#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color1, color_t color2) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speedVer = 0.00;
    speedHor = 0.0;

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

    this->object1 = create3DObject(GL_TRIANGLES, (n-2)*3, g_vertex_buffer_data, color2, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color1, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
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

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {

    this->speedHor -= 0.01;
    if((this->speedHor < 0.02 and this->speedHor > 0) or (this->speedHor > -0.02 and this->speedHor < 0))
        this->speedHor = 0;
    this->position.x += this->speedHor;
    this->speedVer -= 0.01;
    this->position.y += (float)this->speedVer;
    if(this->position.y < 4.5f){
        this->position.y = 4.5f;
        this->speedVer = 0.0;
    }
    if(this->position.y > 15.5f){
        this->position.y = 15.5f;
        this->speedVer = 0.0;
    }
    if(this->position.x < screen_center_x - 4)
        this->position.x = screen_center_x - 4;
    if(this->position.x > screen_center_x + 4)
        screen_center_x += this->speedHor;

}
