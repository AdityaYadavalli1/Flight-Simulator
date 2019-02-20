#include "main.h"
#include "timer.h"
#include "water.h"
#include "rock.h"
#include "flame.h"
#include "monflame.h"
#include "monster.h"
#include "volcano.h"
#include "arrow.h"
#include "ball.h"
#include "smoke.h"
#include "para.h"
#include "fuel.h"
#include "altitude.h"
#include "fuelcan.h"
#include "compass.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int health = 100, level = 1, score = 0;

int volcanoRadius = 9;
int viewType = 1;
float screen_zoom = 100, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int currentCheckpoint = 0;
vector<Rock> rocks;
vector<Volcano> volcanoes;
vector<Flame> flames;
vector<Monflame> monflames;
vector<Flame> monsflames;
vector<Arrow> arrows;
vector<Monster> monsters;
vector<Smoke> smoke;
vector<Para> para;
vector<Fuelcan> fuelcan;
int smokeRadius = 2;
int paraRadius = 200;
Ball ball;
Water water;
Fuel fuel;
Altitude altitude;
Compass compass;
Timer t60(1.0 / 60);
int countTime = 20;
int EcountTime = 150;
double x1 = -1, ypoint = -1;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!

    glm::vec3 eye(5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f));
    glm::vec3 target (0, 0, 0);
    glm::vec3 up (0, 1, 0);
    if(viewType == 1)
    {
      glm::vec3 eye(ball.position.x + 3*sin(ball.rotation*M_PI/180.0f),ball.position.y + 3,3*cos(ball.rotation*M_PI/180.0f) + ball.position.z);
      glm::vec3 target=ball.position;
      glm::vec3 up (0, 1, 0);
      Matrices.view = glm::lookAt( eye, target, up );
    }
    else if (viewType==2)
    {
      glm::vec3 eye(ball.position.x,30,ball.position.z);
      glm::vec3 target=ball.position;
      glm::vec3 up(0,-1,-1);
      Matrices.view = glm::lookAt( eye, target, up );
    }
    else if (viewType==3)
    {
      glm::vec3 eye(0,20,0);
      glm::vec3 target = ball.position;
      glm::vec3 up (0, 1, 0);
      Matrices.view = glm::lookAt( eye, target, up );
    }
    else if (viewType==4)
    {
      glm::vec3 eye(ball.position.x - 3*sin(ball.rotation*M_PI/180.0f),ball.position.y + 0.75,ball.position.z - 3*cos(ball.rotation*M_PI/180.0f));
      glm::vec3 target(ball.position.x-15*sin(ball.rotation*M_PI/180.0f),ball.position.y,ball.position.z-15*cos(ball.rotation*M_PI/180.0f));
      glm::vec3 up (0, 1, 0);
      Matrices.view = glm::lookAt( eye, target, up );
    }
    else if (viewType==5)
    {
      glm::vec3 eye(ball.position.x + 3*sin(ball.rotation4*M_PI/180.0f),ypoint/10 - 25,3*cos(ball.rotation4*M_PI/180.0f) + ball.position.z);
      glm::vec3 target=ball.position;
      glm::vec3 up (0, 1, 0);
      Matrices.view = glm::lookAt( eye, target, up );
    }
    else
    {
      glm::vec3 eye(5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f));
      glm::vec3 target (0, 0, 0);
      glm::vec3 up (0, 1, 0);
      Matrices.view = glm::lookAt( eye, target, up );
    }
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view ;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    water.draw(VP);
    ball.draw(VP);
    fuel.draw(VP);
    altitude.draw(VP);
    compass.draw(VP);
    for (int i = 0; i < (int)rocks.size(); i++)
    {
      rocks[i].draw(VP);
    }
    for (int i = 0; i < (int)flames.size(); i++)
    {
      flames[i].draw(VP);
    }
    for (int i = 0; i < (int)monflames.size(); i++)
    {
      monflames[i].draw(VP);
    }
    for (int i = 0; i < (int)monsters.size(); i++)
    {
      monsters[i].draw(VP);
    }
    for (int i = 0; i < (int)volcanoes.size(); i++)
    {
      volcanoes[i].draw(VP);
    }
    for (int i = 0; i < (int)smoke.size(); i++)
    {
      smoke[i].draw(VP);
    }
    for (int i = 0; i < (int)para.size(); i++)
    {
      para[i].draw(VP);
    }
    for (int i = 0; i < (int)fuelcan.size(); i++)
    {
      fuelcan[i].draw(VP);
    }
    for (int i = 0; i < (int)arrows.size(); i++)
    {
      if(i==currentCheckpoint)
      {
        arrows[i].draw(VP);
      }
    }


}


void tick_input(GLFWwindow *window) {
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int r = glfwGetKey(window, GLFW_KEY_R);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int mouseLeft = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int mouseRight = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    int one = glfwGetKey(window, GLFW_KEY_1);//camera
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4);
    int five = glfwGetKey(window, GLFW_KEY_5);

    if (one)
    {
      viewType = 1;
    }
    if (two)
    {
      viewType = 2;
    }
    if (three)
    {
      viewType = 3;
    }
    if (four)
    {
      viewType = 4;
    }
    if(five)
    {
      viewType = 5;
      glfwGetCursorPos(window, &x1, &ypoint);
      // printf("%f --ballposx, %f --ballposy %f --x1, %f --ypoint\n", ball.position.x, ball.position.y, x1, ypoint);
      if(x1 -320 > ball.position.x)
      {
        ball.rotation4 -= 1;
      }
      else
      {
        ball.rotation4 +=1;
      }
    }
    if(!five)
    {
      ball.rotation4 = 0;
      if (left)
      {
        ball.rotation += 1;

      }
      if (right)
      {
        ball.rotation -= 1;

      }
      if (d)
      {
        ball.rotation1 -= 1;

      }
      if (a)
      {
        ball.rotation1 += 1;

      }
      if(e)
      {
        ball.rotation3 -= 1;
      }
      if(r)
      {
        ball.rotation3 += 1;
      }
      if (up)
      {
        ball.position.x -= ball.speed*sin(ball.rotation*M_PI/180.0f);
        ball.position.z -= ball.speed*cos(ball.rotation*M_PI/180.0f);
        ball.fuel-= 2000;
      }
      if (down)
      {
        ball.position.x += ball.speed*sin(ball.rotation*M_PI/180.0f);
        ball.position.z += ball.speed*cos(ball.rotation*M_PI/180.0f);
        ball.fuel-= 3000;
      }
      if (space)
      {
        if(ball.max_altitude>=ball.position.y+0.3)
          ball.position.y += 0.3;
      }
      if (s) {
        if(ball.position.y >= 6)
          ball.position.y -= 0.3;
      }
      if(mouseLeft) {
        longshoot();
      }
      if(mouseRight) {
        shortshoot();
      }
      if(b) {
        bombshoot();
      }
    }
}

int canCount = 0;
void longshoot()
{
  if(canCount >= countTime)
  {
    canCount = 0;
    flames.push_back(Flame(ball.position.x, ball.position.y+2, ball.position.z, 0.3, ball.rotation, 0.5, 0.3, COLOR_RED));
  }
  return;
}
void shortshoot()
{
  if(canCount >= countTime)
  {
    canCount = 0;
    flames.push_back(Flame(ball.position.x, ball.position.y+2, ball.position.z, 0.3, ball.rotation, 0.5, 0, COLOR_RED));
  }
  return;
}
void bombshoot()
{
  if(canCount >= countTime)
  {
    canCount = 0;
    flames.push_back(Flame(ball.position.x, ball.position.y-2, ball.position.z, 0.3, ball.rotation, 0.0, 0, COLOR_RED));
  }
  return;
}


void tick_elements()
{
  canCount++;
  ball.tick();
  fuel.tick(ball.fuel);
  altitude.tick(ball.position.y);
  compass.tick(ball.rotation);
  for(int i = 0; i < (int)para.size(); i++)
  {
    para[i].tick();
  }
  for (int i = 0; i < (int)rocks.size(); i++)
  {
    rocks[i].tick();
  }

  for (int i = 0; i < (int)flames.size(); i++)
  {
    flames[i].tick();
  }
  for (int i = 0; i < (int)monflames.size(); i++)
  {
    monflames[i].tick();
  }
  for (int i = 0; i < (int)monsflames.size(); i++)
  {
    monsflames[i].tick();
  }
  for (int i = 0; i < (int)monsters.size(); i++)
  {
    monsters[i].tick();
  }

}

void cannonball_monster_collisions()
{
  for (int i = 0; i < (int)monsters.size(); i++)
  {
    for (int j = 0; j < (int)flames.size(); j++)
    {
      if (detect_collision(flames[j].bounding_box(), monsters[i].bounding_box()))
      {
        flames.erase(flames.begin() + j);
        monsters[i].health -= ball.power;
      }
    }
  }
  return;
}
void fuelcan_player_collisions()
{
  for (int i = 0; i < (int)fuelcan.size(); i++)
  {
    if (detect_collision(fuelcan[i].bounding_box(), ball.bounding_box()))
    {
        fuelcan.erase(fuelcan.begin() + i);
        ball.fuel += 1000000;
      }
    }
    return;
}

void cannonball_rock_collisions()
{
  for(int i = 0; i < (int)flames.size(); i++)
  {
    for(int j = 0; j < (int)rocks.size(); j++)
    {
      if(detect_collision(flames[i].bounding_box(), rocks[j].bounding_box()))
      {
        flames.erase(flames.begin() + i);
        rocks.erase(rocks.begin() + j);
        score += 1;

      }
    }
  }
  return;
}
void cannonball_para_collisions()
{
  for(int i = 0; i < (int)flames.size(); i++)
  {
    for(int j = 0; j < (int)para.size(); j++)
    {
      if(detect_collision(flames[i].bounding_box(), para[j].bounding_box()))
      {
        flames.erase(flames.begin() + i);
        para.erase(para.begin() + j);
        score += 100;
      }
    }
  }
  return;
}
void detect_player_monflames_collisions()
{
  for (int i = 0; i < (int)monflames.size(); i++)
  {
    if (detect_collision(monflames[i].bounding_box(), ball.bounding_box()))
    {
      health -= monflames[i].damage;
      monflames.erase(monflames.begin() + i);
    }
  }
  return;
}
bool volcano_helper()
{
  for(int i=0;i<volcanoes.size();i++)
  {

      if(glm::distance(volcanoes[i].position,ball.position) <= volcanoRadius)
      {
        return 1;
      }
  }
  return 0;
}
bool smoke_passed_helper()
{
  for(int i=0;i<smoke.size();i++)
  {
      if(glm::distance(smoke[i].position,ball.position) <= smokeRadius)
      {
        smoke.erase(smoke.begin() + i);
        return 1;
      }
  }
  return 0;
}
void Para_inRadius()
{
  for(int i=0; i<para.size(); i++)
  {
    if(glm::distance(para[i].position,ball.position) <= paraRadius)
    {
      para[i].inRadius = 1;
    }
  }
  return;
}
void volcano_hit()
{
  if(volcano_helper())
  {
    health -= 20;
  }
}
void smoke_passed()
{
  if(smoke_passed_helper())
  {
    score += 10;
  }
}
void collisions() {
  cannonball_monster_collisions();
  detect_player_monflames_collisions();
  cannonball_rock_collisions();
  volcano_hit();
  smoke_passed();
  Para_inRadius();
  cannonball_para_collisions();
  fuelcan_player_collisions();
}

void helperGenerateRocks()
{
  int numRocks = 60;
  for(int i = 0; i < numRocks/4; i++)
  {
    float y = 0.20;
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    rocks.push_back(Rock(1*x, y, 1*y, COLOR_BROWN));
  }
  for(int i = 0; i < numRocks/4; i++)
  {
    float y = 0.20;
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    rocks.push_back(Rock(1*x, y, -1*z, COLOR_BROWN));
  }
  for(int i = 0; i < numRocks/4; i++)
  {
    float y = 0.20;
    float x = (rand()) /( (RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    rocks.push_back(Rock(-1*x, y, -1*z, COLOR_BROWN));
  }
  for(int i = 0; i < numRocks/4; i++)
  {
    float y = 0.20;
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    rocks.push_back(Rock(-1*x, y, 1*z, COLOR_BROWN));
  }
  return;
}

void helperGenerateVolcanoes()
{
  int numVolcanoes = 40;
  for(int i = 0; i < numVolcanoes/4; i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand())/((RAND_MAX/(200)));
    volcanoes.push_back(Volcano(x*1, 2, z*1, 1, 50));
  }
  for(int i = 0; i < numVolcanoes/4; i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand())/((RAND_MAX/(200)));
    volcanoes.push_back(Volcano(x*1, 2, z*-1, 1, 50));
  }
  for(int i = 0; i < numVolcanoes/4; i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand())/((RAND_MAX/(200)));
    volcanoes.push_back(Volcano(x*-1, 2, z*-1, 1, 50));
  }
  for(int i = 0; i < numVolcanoes/4; i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand())/((RAND_MAX/(200)));
    volcanoes.push_back(Volcano(x*-1, 2, z*1, 1, 50));
  }
  return;
}
void helperGenerateMonsters()
{
  int numMonsters = 32;
  float y = 2;
  for(int i = 0; i<numMonsters/4;i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    monsters.push_back(Monster(x*1, 2, z*1, y/2, 50));
  }
  for(int i = 0; i<numMonsters/4;i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    monsters.push_back(Monster(x*1, 2, z*-1, y/2, 50));
  }
  for(int i = 0; i<numMonsters/4;i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    monsters.push_back(Monster(x*-1, 2, z*-1, y/2, 50));
  }
  for(int i = 0; i<numMonsters/4;i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    monsters.push_back(Monster(x*-1, 2, z*1, y/2, 50));
  }
}
void helperGenerateFuelcan()
{
  int numFuelcan = 32;
  float y = 12;
  for(int i = 0; i<numFuelcan/4; i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    fuelcan.push_back(Fuelcan(x*1, y, z*1, y/2));
  }
  for(int i = 0; i<numFuelcan/4; i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    fuelcan.push_back(Fuelcan(x*1, y, z*-1, y/2));
  }
  for(int i = 0; i<numFuelcan/4;i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    fuelcan.push_back(Fuelcan(x*-1, y, z*-1, y/2));
  }
  for(int i = 0; i<numFuelcan/4; i++)
  {
    float x = (rand()) /((RAND_MAX/(200)));
    float z = (rand()) /((RAND_MAX/(200)));
    fuelcan.push_back(Fuelcan(x*-1, y, z*1, y/2));
  }
}
void helperGenerateArrows()
{
  int numArrows = 32;
  float y = 15;
  for(int i = 0; i<numArrows; i++)
  {
    arrows.push_back(Arrow(monsters[i].position.x, y, monsters[i].position.z,1));
  }
  return;
}

void helperGenerateSmoke()
{
  int numSmoke = 32;
  float y = 10;
  for(int i = 0; i<numSmoke; i++)
  {
    if(i%2==0)
    {
      smoke.push_back(Smoke(monsters[i].position.x - 25, y, monsters[i].position.z + 25,1));
    }
    else
    {
        smoke.push_back(Smoke(monsters[i].position.x + 25, y, monsters[i].position.z - 25,1));
    }
  }
  return;
}
void helperGeneratePara()
{
  int numPara = 32;
  float y = 140;
  for(int i = 0; i<numPara; i++)
  {
    para.push_back(Para(monsters[i].position.x + 10, y, monsters[i].position.z - 10,1));
  }
  return;
}
void monster_firing(Monster& M, float size, float vel)
{
  float dist = glm::distance(M.position,ball.position);
  float vecx = ball.position.x - M.position.x;
  float vecy = ball.position.y - M.position.y;
  float vecz = ball.position.z - M.position.z;
  float xvelocity = vel*vecx/dist;
  float yvelocity = vel*vecy/dist;
  float zvelocity = vel*vecz/dist;
  Monflame temp1 = Monflame(M.position.x, M.position.y, M.position.z, 0, vel, xvelocity, yvelocity, zvelocity, COLOR_DARK_RED); // vecy/dist is component angle needed
  // printf("%f--vecx, %f--vecy, %f--vecz, %f--yaccel, %f--xvel, %f--yvel, %f--zvel ---correct\n", vecx, vecy, vecz, temp.yaccel, temp.xvelocity, temp.yvelocity, temp.zvelocity);
  // printf("%f--vecx, %f--vecy, %f--vecz, %f--yaccel, %f--xvel, %f--yvel, %f--zvel ---wrong\n", temp1.vecx, temp1.vecy, temp1.vecz, temp1.yaccel, temp1.xvelocity, temp1.yvelocity, temp1.zvelocity);
  monflames.push_back(temp1);
  // monsflames.push_back(temp1);
  M.counter = 0;
  return;
}

bool can_fire(Monster& M, float range)
{
  if(glm::distance(ball.position,M.position)<=range && M.counter >= EcountTime)
  {
    return 1;
  }
  return 0;
}
int gameOver=0;
void monster_handling()
{
  for (int i = 0; i < (int)monsters.size(); i++)
    {
      //Monster Dies
      if (monsters[i].health <= 0)
      {
        monsters.erase(monsters.begin() + i);
        if(currentCheckpoint < 32)
        {
          currentCheckpoint++;
        }
        score += 50;
      }
      if (monsters.size() == 0)
      {
          gameOver=1;
      }
      //If in Range fire and Time Gap, fire
      if (glm::distance(ball.position,monsters[i].position)<=30.0 &&  monsters[i].counter >= EcountTime)
      {
        monster_firing(monsters[i], 0.75, 0.2);
      }
    }
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    float fuelsize = ball.fuel/5000000;
    float altitudesize = ball.position.y/ball.max_altitude;
    float compasssize = 2/3;
    ball = Ball(0, 10, 3, COLOR_RED);
    fuel = Fuel(-0.8 ,-0.8, fuelsize);
    altitude = Altitude(-0.6, -0.8, altitudesize);
    compass = Compass(0.8, 0.0, compasssize);
    water = Water(0, 0, 0, COLOR_SKY_BLUE);
    helperGenerateRocks();
    helperGenerateMonsters();
    helperGenerateArrows();
    helperGenerateVolcanoes();
    helperGenerateSmoke();
    helperGeneratePara();
    helperGenerateFuelcan();
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
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
    int width  = 600;
    int height = 600;
    char stringPrint[1000];
    window = initGLFW(width, height);

    initGL (window, width, height);
    Matrices.projection = glm::perspective(glm::radians(screen_zoom), (float)600 / (float)600, 0.1f, 100.0f);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
          // 60 fps
          // OpenGL Draw commands
          sprintf(stringPrint, "Level: %d  Score: %d Health: %d Fuel: %d", level, score, health, ball.fuel);
          glfwSetWindowTitle(window, stringPrint);
          // cout << ball.position.x<<" "<<ball.position.y <<'\n';
          draw();
          // Swap Frame Buffer in double buffering
          glfwSwapBuffers(window);
          monster_handling();
          tick_elements();
          collisions();
          tick_input(window);
          if(health <= 0 || ball.fuel <= 0){
            cout << "Sorry, you died. Score: " << score << "\n";
            quit(window);
          }
          if(gameOver) {
            cout << "Game Over, You won" << score <<'\n';
          }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) < (a.width + b.width)) &&
           (abs(a.y - b.y) < (a.height + b.height)) &&
           (abs(a.z - b.z) < (a.length + b.length));
}
void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
