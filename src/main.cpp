#include "main.h"
#include "timer.h"
#include "player.h"
#include "platform.h"
#include "coin.h"
#include "magnet.h"
#include "fireline.h"
#include "firebeam.h"
#include "specialobject.h"
#include "boomerang.h"
#include "balloon.h"

using namespace std;

// Declarations
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
Player pl;
Magnet mg;
vector<Balloon> balloon;
vector<Boomerang> boom;
vector<Coin> coins;
vector<Platform> plat;
Firebeam firebeam1, firebeam2;
vector<Fireline> fireline;
vector<Specialobject> spObj;
float screen_zoom = 1, screen_center_x = 4, screen_center_y = 4;
float camera_rotation_angle = 0;
int width  = 600;
int height = 600;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
   glm::vec3 eye (screen_center_x, screen_center_y, 10);
    
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (screen_center_x, screen_center_y, 0);

    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    glm::mat4 VP = Matrices.projection * Matrices.view;
    mg.draw(VP);
    for(int i=0;i<boom.size();i++)
        boom[i].draw(VP);
    // plat.draw(VP);
    for(int i=0;i<plat.size();i++)
        plat[i].draw(VP);
    for(int i=0;i<spObj.size();i++)
        spObj[i].draw(VP);
    for(int i=0;i<coins.size();i++){
        coins[i].draw(VP);
    }
    for(int i=0;i<balloon.size();i++){
        balloon[i].draw(VP);
    }
    pl.draw(VP);
    for(int i=0;i<fireline.size();i++){
        fireline[i].draw(VP);
    }
    firebeam1.draw(VP);
    firebeam2.draw(VP);
}

// processing the inputs
void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int b = glfwGetKey(window, GLFW_KEY_B);
    if (left) {
        pl.speedHor = -0.2;
    }
    if (right) {
        pl.speedHor = 0.2;
    }
    if (space) {
        pl.speedVer = 0.15;
    }
    if (up) {
        screen_zoom += 0.1;
        if(screen_zoom > 4)
            screen_zoom = 4;
    }
    if (down) {
        pl.position.y -= 0.1;
        screen_zoom -= 0.1;
        if(screen_zoom < 1)
            screen_zoom = 1;
    }
    if(b and pl.bal==1) {
        pl.bal = 2;
        balloon.push_back(Balloon(pl.position.x, pl.position.y));
        balloon[balloon.size() - 1].speedHor += pl.speedHor;
    }
}

// ticking all the elements
void tick_elements() {
    
    //magnetic force
    mg.tick();
    if(mg.time < 60*mg.existTime) {
        float x = mg.position.x - pl.position.x;
        float y = mg.position.y - pl.position.y;
        float dist = sqrt((x*x)+(y*y));
        double f = 1.5/(dist*dist);
        double xcomp = f*(x/dist);
        double ycomp = f*(y/dist);
        if(xcomp > 0.000001)
            pl.position.x += xcomp;
        if(ycomp > 0.000001)
            pl.position.y += ycomp;
    }
    // platform 
    for(int i=0;i<plat.size();i++)
        plat[i].tick();
    
    for(int i=0;i<spObj.size();i++)
        spObj[i].tick();
    
    for(int i=0;i<boom.size();i++)
        boom[i].tick();

    for(int i=0;i<balloon.size();i++)
        balloon[i].tick();
    for(int i=0;i<balloon.size();i++){
        if(balloon[i].position.y < -2)
            balloon.erase(balloon.begin() + i);
    }
    
    pl.tick();
    
    firebeam1.tick();
    firebeam2.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // creating the player
    pl    = Player(2.0f, 1.0f, COLOR_GREEN, COLOR_RED);
    // creating platform
    for(int i=0;i<20;i++)
        plat.push_back(Platform(-8.0f + (float)(i*2), -3.0f, i%2?COLOR_BLACK:COLOR_RED));
    
    for(int i=0;i<10;i++)
        coins.push_back(Coin(10+i, 5, COLOR_YELLOW, 10));
    for(int i=0;i<10;i++)
        coins.push_back(Coin(10+i, 6, COLOR_RED, 20));
    
    mg = Magnet(screen_center_x + 20, 6, COLOR_BLUE);
    fireline.push_back(Fireline(20.0f, 4.0f,COLOR_BLACK,COLOR_YELLOW,60.0f));
    
    // initialising firebeam 
    firebeam1 = Firebeam(screen_center_x,screen_center_y,COLOR_BLACK, COLOR_RED);
    firebeam2 = Firebeam(screen_center_x,screen_center_y,COLOR_BLACK, COLOR_RED);
    
    // creating boomerang
    boom.push_back(Boomerang(screen_center_x + 8, screen_center_y, COLOR_BLACK));

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 1.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


void checkColissions()
{
    // Colission of player with magnet
    if(detect_collision(pl.box, mg.box)){
        pl.position.x = mg.position.x;
        pl.position.y = mg.position.y;
    }

    // Colission of player with coins
    for(int i=0;i<coins.size();i++){
        if(detect_collision(pl.box, coins[i].box)){
            pl.score += coins[i].score;
            coins.erase(coins.begin()+i);
            break;
        }
    }

    // Colission of player with boomerang
    for(int i=0;i<boom.size();i++){
        if(detect_collision(pl.box, boom[i].box)){
            pl.score -= 50;
            if(pl.score < 0)
                pl.score = 0;
            cout<<"btbtbtbtbt"<<endl;
        }
    }

    // Colission of player with special objects
    for(int i=0;i<spObj.size();i++){
        if(detect_collision(pl.box, spObj[i].box)){
            spObj.erase(spObj.begin()+i);
            break;
        }
    }

    // Colission of player with firebeams
    if(firebeam1.col)
    {
        if(detect_collision(pl.box,firebeam1.box) or detect_collision(pl.box,firebeam2.box))
        {
            cout<<"mar gaya : "<<firebeam1.time<<endl;
            // exit(0);
        }
    }
    
    // Colission of balloons with firebeams
    if(firebeam1.col)
    {
        for(int i=0;i<balloon.size();i++) {
            if(detect_collision(balloon[i].box,firebeam1.box))
            {
                balloon.erase(balloon.begin() + i);
                firebeam1.time = 0;
                firebeam1.col = 0;
                cout<<"aag bhuj gayi : "<<firebeam1.time<<endl;
            }
            if(detect_collision(balloon[i].box,firebeam2.box))
            {
                balloon.erase(balloon.begin() + i);
                firebeam2.time =  0;
                firebeam2.col = 0;
                cout<<"aag bhuj gayi : "<<firebeam2.time<<endl;
            }
        }
    }
    
    
    // Colission of player with firelines
    for(int i=0;i<fireline.size();i++){
        if(detect_collision_fireline(pl.box,fireline[i].box,fireline[i].rotation))
        {
            cout<<"mar gaya : fireline "<<endl;
            // exit(0);
        }
    }

    // Colission of water balloons with firelines
    for(int i=0;i<fireline.size();i++) {
        int flag = 0;
        for(int j=0;j<balloon.size();j++){
            if(detect_collision_fireline(balloon[j].box,fireline[i].box,fireline[i].rotation)) {
                cout<<"aag bhuj gayi "<<endl;
                balloon.erase(balloon.begin() + j);
                flag = 1;
                break;
            }
        }
        if(flag) {
            cout<<"erase"<<endl;
            fireline.erase(fireline.begin()+i);
            break;
        }
    }
}

void generateNewObjects()
{
    //rand value
    int randV = 10000;
    int r = rand()%randV;
    float pr;
    
    // generating magnets
    if(mg.time > 60*(mg.gapTime + mg.existTime))
        mg.position.x = screen_center_x + 10, mg.time = 1;

    // generating coins
    // int 

    // generating firebeams
    if(!firebeam1.time)
    {
        pr = 0.0005;
        if(r < pr*randV){
            firebeam1.time = firebeam2.time = 1;
            firebeam1.position.x = firebeam2.position.x = screen_center_x - 4;
            float y = (rand()%3) + 3.0f;
            firebeam1.position.y = screen_center_y - y;
            firebeam2.position.y = screen_center_y + y;
        }
    }

    // generating boomerang
    pr = 0.000005;
    if(r < 10*pr*randV and r > 9*pr*randV){
        boom.push_back(Boomerang(screen_center_x + 8, screen_center_y, COLOR_BLACK));
    }

    // generating special objects
    pr = 0.0005;
    if(r >= (randV-pr*randV))
        spObj.push_back(Specialobject(screen_center_x + 20, 6.0f,COLOR_RED));
}

int main(int argc, char **argv) {
    srand(time(0));
    
    window = initGLFW(width, height);

    initGL (window, width, height);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        // reset_screen();
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            generateNewObjects();
            draw();
            checkColissions();
            
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            reset_screen();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    int x = a.x + a.width > b.x and b.x + b.width >a.x?1:0;
    int y = a.y + a.height > b.y and b.y + b.height >a.y?1:0;
    return (x and y);
}

bool detect_collision_fireline(bounding_box_t a, bounding_box_t b, float angle) {
    bounding_box_t box = b;
    box.height = 0.5;
    box.width  = 0.5;
    angle *= (2*3.1415926/360.0f);
    while(box.x < (b.x + b.width*cos(angle))){
        if(detect_collision(a,box)) {
                return true;
        }
        box.x += 0.5*cos(angle);
        box.y += 0.5*sin(angle);
    }
    return false;
}
void reset_screen() {
    float top    =  + 8 / screen_zoom;
    float bottom =  - 8 / screen_zoom;
    float left   =  - 8 / screen_zoom;
    float right  =  + 8 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
