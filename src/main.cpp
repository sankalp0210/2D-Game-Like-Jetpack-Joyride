#include "main.h"
#include "timer.h"
#include "ball.h"
#include "player.h"
#include "platform.h"
#include "coin.h"
#include "magnet.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

Ball ball;
Player pl;
Platform plat;
Magnet mg;
// set<Coin> coinss;
vector<Coin> coins;
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
    pl.draw(VP);
    plat.draw(VP);
    for(int i=0;i<coins.size();i++){
        coins[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    if (left) {
        pl.speedHor = -0.2;
    //    pl.position.x -= pl.speedHor;
    //    plat.position.x -= pl.speedHor;
    }
    if (right) {
        pl.speedHor = 0.2;
    //    pl.position.x += pl.speedHor;
    //    plat.position.x += pl.speedHor;
    }
    if (up){
        pl.speedVer = 0.15;
        // screen_zoom += 0.1;
        // if(screen_zoom > 4)
        //     screen_zoom = 4;
        // reset_screen();
    }
    if (down){
        // pl.position.y -= 0.1;
        // screen_zoom -= 0.1;
        // if(screen_zoom < 1)
        //     screen_zoom = 1;
        // reset_screen();
    }
}

void tick_elements() {
    // ball1.tick();
    // ball2.tick();
    pl.tick();
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball  = Ball(7.0f, 7.0f, COLOR_RED, 1);
    pl    = Player(2.0f, 5.0f, COLOR_GREEN, COLOR_RED);
    plat  = Platform(8.0f, 1.0f, COLOR_BLACK);
    Coin coin = Coin(10, 10, COLOR_YELLOW);
    Coin coin2 = Coin(10, 12, COLOR_YELLOW);
    mg = Magnet(15, 10, COLOR_BLUE);
    coins.push_back(coin);
    // coinss.insert(coin);
    // coinss.insert(coin2);
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
            draw();
            if(coins.size() && detect_collision(pl.box, coins[0].box)){
                cout<<pl.position.x << " " << pl.position.y<<endl;
                Coin *c = &coins[0];
                cout<<c->position.x << " " << c->position.y<<endl;
                coins.pop_back();
                delete c;
            }
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
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
    // return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
        //    (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 8 / screen_zoom;
    float bottom = screen_center_y - 8 / screen_zoom;
    float left   = screen_center_x - 8 / screen_zoom;
    float right  = screen_center_x + 8 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    std::cout << top << " " << bottom << " " << left << " " << right << std::endl;    
}
