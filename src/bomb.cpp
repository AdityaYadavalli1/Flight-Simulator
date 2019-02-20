#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z, float size, float angle, float velocity, float yvelocity, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->velocity = velocity;
    this->angle = angle;
    this->rotation = 0;
    this->size = size;
    this->yvelocity = yvelocity;
    this->xvelocity = 0;
    this->zvelocity = 0;
    this->yaccel = -0.01;
    speed = 1;
    this->damage = 50;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 scale = glm::scale(glm::vec3(this->size, this->size ,this->size));
    glm::mat4 rotate1   = glm::rotate((float) (this->rotation2 * M_PI / 180.0f), glm::vec3(1, 0, 0));// plane made was 90 wrong pitch
    glm::mat4 rotate    = glm::rotate((float) (this->rotation  * M_PI / 180.0f), glm::vec3(0, -1, 0));// roll
    glm::mat4 rotate2   = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(0, 0, 1)); // yaw
    mainrotation = rotate*rotate1*rotate2;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * mainrotation * scale);
    //glm::mat4 MVP = VP * Matrices.model;
    glm::mat4 MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bomb::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick() {
  float LO = -0.1;
  float HI = 0.1;
  this->position.x -= this->velocity * sin(this->angle*M_PI/180.0f);
  this->position.z -= this->velocity * cos(this->angle*M_PI/180.0f);
  this->position.y += this->yvelocity; // tilt in the missile initially
  this->yvelocity += this->yaccel;
  this->position.x += this->xvelocity;
  this->position.z += this->zvelocity;
  // ball.position.z -= ball.speed*cos(ball.rotation*M_PI/180.0f);
  // ball.position.x -= ball.speed*sin(ball.rotation*M_PI/180.0f);
}

bounding_box_t Bomb::bounding_box() {
  bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, this->size, this->size, this->size};
  return bbox;
}
