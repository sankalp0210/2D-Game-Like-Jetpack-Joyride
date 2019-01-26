#include "main.h"
#include "timer.h"
#include "player.h"
#include "platform.h"
#include "coin.h"
#include "magnet.h"
#include "fireline.h"
#include "firebeam.h"
#include "specialobject.h"
#include "specialcoins.h"
#include "speedup.h"
#include "shield.h"
#include "boomerang.h"
#include "balloon.h"
#include "wall.h"
#include "score.h"
#include "ring.h"
#include "viserion.h"
#include "iceball.h"
#include "jetprop.h"

using namespace std;

// Declarations
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
Score score[4];
bool insideRing;
Player pl;
Magnet mg;
Ring ring;
Viserion viserion;
vector<Balloon> balloon;
vector<Jetprop> jetprop;
vector<Iceball> iceball;
vector<Boomerang> boom;
vector<Coin> coins;
vector<Platform> plat;
vector<Wall> wall;
Firebeam firebeam1, firebeam2;
vector<Fireline> fireline;
vector<Specialobject> spObj;
vector<Specialcoins> spCoin;
vector<Speedup> speedUp;
vector<Shield> shield;
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
    int x = 1;
    for(int i=0;i<4;i++)
    {
        score[i].draw(VP, (pl.score/x)%10);
        x*=10;
    }
    ring.draw(VP);
    for(int i=0;i<balloon.size();i++)
        balloon[i].draw(VP);

    for(int i=0;i<jetprop.size();i++)
        jetprop[i].draw(VP);

    for(int i=0;i<iceball.size();i++)
        iceball[i].draw(VP);

    for(int i=0;i<boom.size();i++)
        boom[i].draw(VP);

    for(int i=0;i<spObj.size();i++)
        spObj[i].draw(VP);
    for(int i=0;i<spCoin.size();i++)
        spCoin[i].draw(VP);
    for(int i=0;i<speedUp.size();i++)
        speedUp[i].draw(VP);
    for(int i=0;i<shield.size();i++)
        shield[i].draw(VP);
    for(int i=0;i<coins.size();i++){
        coins[i].draw(VP);
    }
    pl.draw(VP);
    viserion.draw(VP);
    for(int i=0;i<plat.size();i++)
        plat[i].draw(VP);
    for(int i=0;i<wall.size();i++)
        wall[i].draw(VP);
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
        pl.speedHor = -pl.speed;
    }
    if (right) {
        pl.speedHor = pl.speed;
    }
    if (space) {
        pl.speedVer = 0.15;
        if(pl.jet == 1){
            jetprop.push_back(Jetprop(pl.position.x - 1.5f, pl.position.y-2.0f)), pl.jet = 2;
        }
    }
    // if (up) {
    //     screen_zoom += 0.1;
    //     if(screen_zoom > 2)
    //         screen_zoom = 2;
    // }
    // if (down) {
    //     pl.position.y -= 0.1;
    //     screen_zoom -= 0.1;
    //     if(screen_zoom < 0.4)
    //         screen_zoom = 0.4;
    // }
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
    // Platform 
    for(int i=0;i<plat.size();i++)
        plat[i].tick();

    // Wall
    for(int i=0;i<wall.size();i++)
        wall[i].tick();
    for(int i=0;i<spObj.size();i++)
        spObj[i].tick();
    for(int i=0;i<spCoin.size();i++)
        spCoin[i].tick();
    for(int i=0;i<speedUp.size();i++)
        speedUp[i].tick();
    for(int i=0;i<shield.size();i++)
        shield[i].tick();
    for(int i=0;i<boom.size();i++)
        boom[i].tick();

    for(int i=0;i<balloon.size();i++)
        balloon[i].tick();
    for(int i=0;i<jetprop.size();i++)
        jetprop[i].tick();
    for(int i=0;i<iceball.size();i++)
        iceball[i].tick();

    for(int i=0;i<4;i++) {
        score[i].position.x = screen_center_x - 3.3 / screen_zoom - 0.7*i;
        if(screen_zoom > 1.2f)
            score[i].position.y = pl.position.y + 6 / screen_zoom ;
        else
            score[i].position.y = screen_center_y + 7 / screen_zoom;
    }
        
    // player
    pl.tick();

    // dragon
    if(viserion.position.y < pl.position.y)
        viserion.position.y += viserion.speedVer;
    else if(viserion.position.y > pl.position.y)
        viserion.position.y -= viserion.speedVer;
    if(viserion.position.x + 2 > pl.position.x)
        viserion.tick();
    
    firebeam1.tick();
    firebeam2.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // creating the player
    insideRing = false;
    pl    = Player(2.0f, 1.0f, COLOR_GREEN, COLOR_RED);
    
    // Initialising the dragon
    viserion = Viserion(200.0f, 1.0f,COLOR_RED, COLOR_GREEN);
    
    // creating platform
    for(int i=0;i<20;i++)
        plat.push_back(Platform(-8.0f + (float)(i*2), -4.0f, i%2?COLOR_GROUND1:COLOR_GROUND2));
    
    // creating wall
    for(int i=0;i<20;i++)
        wall.push_back(Wall(-8.0f + (float)(i*2), 13.5f, i%2?COLOR_GROUND1:COLOR_GROUND2));
    
    // creating semi circular ring
    ring = Ring(120, screen_center_y - 3.0, COLOR_SCORE);

    for(int i=0;i<4;i++)
        score[i] = Score(screen_center_x - 2 - 0.5*i, screen_center_y + 4);
    
    mg = Magnet(screen_center_x + 20, 6, COLOR_BLUE);
    
    // fireline.push_back(Fireline(20.0f, 4.0f,COLOR_BLACK,COLOR_YELLOW,60.0f));
    
    // initialising firebeam 
    firebeam1 = Firebeam(screen_center_x,screen_center_y,COLOR_BLACK, COLOR_RED);
    firebeam2 = Firebeam(screen_center_x,screen_center_y,COLOR_BLACK, COLOR_RED);
    
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
    // Colission of player with ice balls
    for(int i=0;i<iceball.size();i++){
        if(detect_collision(pl.box, iceball[i].box)){
            iceball.erase(iceball.begin()+i);
            if(!pl.shield)
                player_killed();
            break;
        }
    }
    // Colission of player with dragon
    if(detect_collision(pl.box, viserion.box)) {
        if(!pl.shield)
            player_killed();
        else
            viserion.position.x += 200.0f;        
    }

    // Colission of player with ring   
    if(detect_collision(pl.box, ring.box) && !insideRing) {
        pl.position.x = ring.box.x + 1.0f;
        pl.position.y = ring.box.y + 1.0f;
        insideRing = true;
    }

    // Colission of player with magnet
    if(mg.time < 60*mg.existTime and detect_collision(pl.box, mg.box)){
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
            boom.erase(boom.begin() + i);
            if(!pl.shield)
                player_killed();
            break;
        }
    }

    // Colission of player with special objects (Lives)
    for(int i=0;i<spObj.size();i++){
        if(detect_collision(pl.box, spObj[i].box)){
            spObj.erase(spObj.begin()+i);
            pl.lives ++ ;
            break;
        }
    }

    // Colission of player with special objects (Coins)
    for(int i=0;i<spCoin.size();i++){
        if(detect_collision(pl.box, spCoin[i].box)){
            spCoin.erase(spCoin.begin()+i);
            pl.score += 100 ;
            break;
        }
    }

    // Colission of player with special objects (SpeedUp)
    for(int i=0;i<speedUp.size();i++){
        if(detect_collision(pl.box, speedUp[i].box)){
            speedUp.erase(speedUp.begin()+i);
            pl.speedup = 1;
            pl.speed += pl.speedInc;
        }
    }

    // Colission of player with special objects (Shield)
    for(int i=0;i<shield.size();i++){
        if(detect_collision(pl.box, shield[i].box)){
            shield.erase(shield.begin()+i);
            pl.shield = 1;
        }
    }

    // Colission of player with firebeams
    if(firebeam1.col)
    {
        if(detect_collision(pl.box,firebeam1.box) or detect_collision(pl.box,firebeam2.box))
        {
            firebeam1.time = firebeam1.col = firebeam2.time = firebeam2.col = 0;
            if(!pl.shield)
                player_killed();
        }
    }
    
    // Colission of balloons with firebeams
    if(firebeam1.col)
    {
        for(int i=0;i<balloon.size();i++) {
            if(detect_collision(balloon[i].box,firebeam1.box))
            {
                pl.score += 100;
                balloon.erase(balloon.begin() + i);
                firebeam1.time = 0;
                firebeam1.col = 0;
            }
            if(detect_collision(balloon[i].box,firebeam2.box))
            {
                pl.score += 100;
                balloon.erase(balloon.begin() + i);
                firebeam2.time =  0;
                firebeam2.col = 0;
            }
        }
    }


    // Colission of player with firelines
    for(int i=0;i<fireline.size();i++){
        if(detect_collision_fireline(pl.box,fireline[i].box,fireline[i].rotation))
        {
            fireline.erase(fireline.begin() + i);
            if(!pl.shield)
                player_killed();
            break;
        }
    }

    // Colission of water balloons with firelines
    for(int i=0;i<fireline.size();i++) {
        int flag = 0;
        for(int j=0;j<balloon.size();j++){
            if(detect_collision_fireline(balloon[j].box,fireline[i].box,fireline[i].rotation)) {
                balloon.erase(balloon.begin() + j);
                pl.score += 100;
                flag = 1;
                break;
            }
        }
        if(flag) {
            fireline.erase(fireline.begin()+i);
            break;
        }
    }
}

void moveInsideRing()
{
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    if(ring.angle > 182){
        insideRing = false;
        ring.angle = 180.0f;
    }
    if(left)
        ring.angle += 0.5f;
    if(right)
        ring.angle -= 0.5f;
    float ang = ring.angle*(2*3.1415926/360.0f);
    pl.position.x = ring.centreX + ring.r1*cos(ang);
    pl.position.y = ring.centreY + ring.r2*sin(ang);
    if(ring.angle < -1){
        ring.angle = 180.0f;
        insideRing = false;
    }
}

// delete the objects that are far from view
void deleteObjects()
{
    // no need to delete magnet and firebeams as they change position with time
    // platform and wall ahead and back as per the movement of player
    // 

    // moving dragon forward
    if(viserion.position.x < screen_center_x - 40)
        viserion.position.x += 200.0f;
    
    // moving ring forward
    if(ring.position.x < screen_center_x - 40)
        ring.position.x += 200.0f;
    
    // deleting jetprops
    for(int i=0;i<jetprop.size();i++){
        if(jetprop[i].position.y < jetprop[i].originY - 2.0f)
            jetprop.erase(jetprop.begin() + i);
    }

    // deleting balloons
    for(int i=0;i<balloon.size();i++){
        if(balloon[i].position.y < -3)
            balloon.erase(balloon.begin() + i);
    }

    // deleting iceballs
    for(int i=0;i<iceball.size();i++){
        if(iceball[i].position.y < -3)
            iceball.erase(iceball.begin() + i);
    }

    // deleting coins
    for(int i=0;i<coins.size();i++) {
        if(coins[i].position.x < (screen_center_x - 40))
            coins.erase(coins.begin() + i);
    }

    // deleting firelines
    for(int i=0;i<fireline.size();i++){
        if(fireline[i].position.x < (screen_center_x -40))
            fireline.erase(fireline.begin() + i);
    }

    // deleting boomerang
    for(int i=0;i<boom.size();i++){
        if(boom[i].position.x < (screen_center_x -40))
            boom.erase(boom.begin() + i);
    }

    // deleting special objects
    for(int i=0;i<spObj.size();i++){
        if(spObj[i].position.x < (screen_center_x -40))
            spObj.erase(spObj.begin() + i);
    }

    // deleting special coins
    for(int i=0;i<spCoin.size();i++){
        if(spCoin[i].position.x < (screen_center_x -40))
            spCoin.erase(spCoin.begin() + i);
    }
    
    // deleting special speedups
    for(int i=0;i<speedUp.size();i++){
        if(speedUp[i].position.x < (screen_center_x -40))
            speedUp.erase(speedUp.begin() + i);
    }

    // deleting special shield
    for(int i=0;i<shield.size();i++){
        if(shield[i].position.x < (screen_center_x -40))
            shield.erase(shield.begin() + i);
    }

}

void generateNewObjects()
{
    //rand value
    int randV = 10000;
    int r = rand()%randV;
    float pr = 0.0005;
    
    // generating ice balls
    if(viserion.bal==1 and viserion.position.x + 2 > pl.position.x and viserion.position.x < pl.position.x + 8) {
        viserion.bal = 2;
        iceball.push_back(Iceball(viserion.position.x, viserion.position.y));
    }

    // generating magnets
    if(mg.time > 60*(mg.gapTime + mg.existTime))
        mg.position.x = pl.position.x + 10, mg.time = 1;

    // generating coins
    if(r < 6*pr*randV and r > 3*pr*randV and coins.size() < 5){
        for(int i=0;i<10;i++)
            coins.push_back(Coin(screen_center_x+10+i, screen_center_y-4+rand()%10, COLOR_YELLOW, 10));
        for(int i=0;i<10;i++)
            coins.push_back(Coin(screen_center_x+10+i,screen_center_y-4+rand()%10, COLOR_RED, 20));
    }

    // generating firebeams
    if(!firebeam1.time)
    {
        if(r < pr*randV){
            firebeam1.time = firebeam2.time = 1;
            firebeam1.position.x = firebeam2.position.x = screen_center_x - 4;
            firebeam1.position.y = firebeam1.originY = screen_center_y - 5;
            firebeam2.position.y = firebeam2.originY = screen_center_y + 5;
        }
    }

    //generating firelines
    if(r < 8*pr*randV and r > 6*pr*randV and fireline.size() < 3){
        fireline.push_back(Fireline(screen_center_x + 8, screen_center_y-4 + rand()%8,COLOR_BLACK,COLOR_YELLOW, rand()%180));
    }

    // generating boomerang
    if(r < 10*pr*randV and r > 8*pr*randV and boom.size() < 3){
        boom.push_back(Boomerang(screen_center_x + 8, screen_center_y, COLOR_BOOMERANG));
    }

    // generating special objects
    if(r < 12*pr*randV and r > 11*pr*randV and spObj.size() < 1)
        spObj.push_back(Specialobject(screen_center_x + 20, 6.0f,COLOR_PINK));
    
    // generating special Coins
    if(r < 14*pr*randV and r > 13*pr*randV and spCoin.size() < 1)
        spCoin.push_back(Specialcoins(screen_center_x + 20, 6.0f,COLOR_GOLD));

    // generating special speedups
    if(r < 16*pr*randV and r > 14*pr*randV and speedUp.size() < 1)
        speedUp.push_back(Speedup(screen_center_x + 20, 6.0f,COLOR_BLUE));
    
    // generating special Shield
    if(r < 18*pr*randV and r > 17*pr*randV and shield.size() < 1)
        shield.push_back(Shield(screen_center_x + 20, 6.0f,COLOR_SHIELD));

}

int main(int argc, char **argv) {
    srand(time(0));
    
    window = initGLFW(width, height);

    initGL (window, width, height);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            
            draw();
            tick_elements();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            if(!insideRing){
                deleteObjects();
                generateNewObjects();
                tick_input(window);
                reset_screen();
                checkColissions();
            }
            else
                moveInsideRing();
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
    box.height = 0.3;
    box.width  = 0.3;
    angle *= (2*3.1415926/360.0f);
    int fl = cos(angle) / abs(cos(angle)) ;
    while(box.x*fl < (b.x + b.width*cos(angle) + 0.3*fl)){
        if(detect_collision(a,box)) {
                return true;
        }
        box.x += 0.5*cos(angle);
        box.y += 0.5*sin(angle);
    }
    return false;
}
void reset_screen() {
    float y = 0.0f;
    if(screen_zoom > 1.2)
        y = pl.position.y - 3;
    float top    =  (y + 10) / screen_zoom;
    float bottom =  (y - 8) / screen_zoom;
    float left   =   - 8 / screen_zoom;
    float right  =   + 8 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void player_killed()
{
    pl.lives--;
    cout << endl ;
    cout << "Lives left :- " << pl.lives << endl;
    cout << "Score :- " << pl.score << endl;
    if(pl.lives == 0)
        exit(0);
    pl.position.x += 3.0f;
    pl.position.y = 1.0f;
}