#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color1, color_t color2) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speedVer = 0.00;
    this->speedHor = 0.0;
    this->speedup = 0;
    this->shield = 0;
    this->speed = 0.2;
    this->speedInc = 0.1;
    this->bal = 1;
    this->jet = 1;
    this->score = 0;
    this->lives = 5;
	GLfloat vertex_buffer_data1[100] = {
        -1.0f, -0.5f, 0, 
         1.0f, -2.5f, 0,
         1.0f, -0.5f, 0, 
        -1.0f, -0.5f, 0, 
         1.0f, -2.5f, 0,
        -1.0f, -2.5f, 0,
    };
    GLfloat vertex_buffer_data2[100] = {
        -1.7f, -1.0f, 0,
        -1.1f, -2.0f, 0,
        -1.1f, -1.0f, 0, 
        -1.7f, -1.0f, 0, 
        -1.1f, -2.0f, 0,
        -1.7f, -2.0f, 0,
    };
    GLfloat vertex_buffer_data3[100] = {
        -0.8f, -3.0f, 0, 
        -0.4f, -2.5f, 0,
        -0.4f, -3.0f, 0, 
        -0.8f, -3.0f, 0, 
        -0.4f, -2.5f, 0,
        -0.8f, -2.5f, 0,
    };
    GLfloat vertex_buffer_data4[100] = {
         0.8f, -3.0f, 0, 
         0.4f, -2.5f, 0,
         0.4f, -3.0f, 0, 
         0.8f, -3.0f, 0, 
         0.4f, -2.5f, 0,
         0.8f, -2.5f, 0,
    };
    
    int n = 500;
    GLfloat g_vertex_buffer_data1[9*n+100];
	GLfloat deg = 2*3.1415926/((float)n), r = 0.75f;
    float x1 = r, y1 = 0.0f, z = 0.0f;
	for(int i=0;i<n;i++)
	{
		GLfloat o = deg*(i+1);
		g_vertex_buffer_data1[9*i + 0] = z;
		g_vertex_buffer_data1[9*i + 1] = z;
		g_vertex_buffer_data1[9*i + 2] = z;
		g_vertex_buffer_data1[9*i + 3] = x1;
		g_vertex_buffer_data1[9*i + 4] = y1;
		g_vertex_buffer_data1[9*i + 5] = z;
		g_vertex_buffer_data1[9*i + 6] = x1 = (r*cos(o));
		g_vertex_buffer_data1[9*i + 7] = y1 = (r*sin(o));
		g_vertex_buffer_data1[9*i + 8] = z;
	}
    
    GLfloat g_vertex_buffer_data2[9*n+100];
    float r1, r2;
	deg = 2*3.1415926/((float)n), r1 = 2.5f, r2 = 3.5f;
    x1 = r1, y1 = -1.0f, z = 0.0f;
	for(int i=0;i<(2*n/5);i++)
	{
		GLfloat o = deg*(i+1 - (2*n/10));
		g_vertex_buffer_data2[9*i + 0] = z;
		g_vertex_buffer_data2[9*i + 1] = z;
		g_vertex_buffer_data2[9*i + 2] = z;
		g_vertex_buffer_data2[9*i + 3] = x1;
		g_vertex_buffer_data2[9*i + 4] = y1;
		g_vertex_buffer_data2[9*i + 5] = z;
		g_vertex_buffer_data2[9*i + 6] = x1 = (r1*cos(o));
		g_vertex_buffer_data2[9*i + 7] = y1 = (r2*sin(o))-1.0f;
		g_vertex_buffer_data2[9*i + 8] = z;
	}
    GLfloat g_vertex_buffer_data3[9*n+100];
	deg = 2*3.1415926/((float)n);
    r1 -= 0.2f, r2 -= 0.2f;
    x1 = r1, y1 = -1.0f, z = 0.0f;
	for(int i=0;i<(2*n/5);i++)
	{
		GLfloat o = deg*(i+1 - (2*n/10));
		g_vertex_buffer_data3[9*i + 0] = z;
		g_vertex_buffer_data3[9*i + 1] = z;
		g_vertex_buffer_data3[9*i + 2] = z;
		g_vertex_buffer_data3[9*i + 3] = x1;
		g_vertex_buffer_data3[9*i + 4] = y1;
		g_vertex_buffer_data3[9*i + 5] = z;
		g_vertex_buffer_data3[9*i + 6] = x1 = (r1*cos(o));
		g_vertex_buffer_data3[9*i + 7] = y1 = (r2*sin(o)) -1.0f;
		g_vertex_buffer_data3[9*i + 8] = z;
	}
    this->object1 = create3DObject(GL_TRIANGLES, (n-5)*3, g_vertex_buffer_data1, color2, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color1, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, color2, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, color2, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, color2, GL_FILL);
    this->objectShield1 = create3DObject(GL_TRIANGLES,(2*n/5)*3, g_vertex_buffer_data2, color2, GL_FILL);
    this->objectShield2 = create3DObject(GL_TRIANGLES,(2*n/5)*3, g_vertex_buffer_data3, COLOR_BACKGROUND, GL_FILL);

    this->box.x      = x - 1.7f;
    this->box.y      = y - 3.25;
    this->box.width  = 2.5f;
    this->box.height = 3.0f;
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
    if(this->shield){
        draw3DObject(this->objectShield1);
        draw3DObject(this->objectShield2);
    }
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
    if(this->speedup)
        this->speedup++;
    if(this->speedup > 60*8){
        this->speedup = 0;
        this->speed -= this->speedInc;
    }

    if(this->shield)
        this->shield++;
    if(this->shield > 60*8)
        this->shield = 0;
    
    if(this->bal > 1)
        this->bal+=2;
    if(this->bal == 120)
        this->bal = 1;
    
    if(this->jet > 1)
        this->jet+=2;
    if(this->jet == 6)
        this->jet = 1;
    
    if(this->speedHor > 0)
        this->speedHor -= 0.01;
    else if(this->speedHor < 0)
        this->speedHor += 0.01;
    if((this->speedHor < 0.02 and this->speedHor > 0) or (this->speedHor > -0.02 and this->speedHor < 0))
        this->speedHor = 0;
    
    this->position.x += this->speedHor;
    
    this->speedVer -= 0.01;
    this->position.y += (float)this->speedVer; 
    if(this->position.y < 0.0f){
        this->position.y = 0.0f;
        this->speedVer = 0.0;
    }
    if(this->position.y > 12.5f){
        this->position.y = 12.5f;
        this->speedVer = 0.0;
    }

    screen_center_x = this->position.x;
    this->box.x = this->position.x - 1;
    this->box.y = this->position.y - 2.75;
}
