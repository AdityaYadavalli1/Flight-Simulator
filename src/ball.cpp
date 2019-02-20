#include "ball.h"
#include "main.h"
#include "loader.h"
Ball::Ball(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotation1 = 0;
    this->rotation2 = -90;
    this->fuel = 5000000;
    this->max_altitude = 50;
    this->rotation3 = 0;
    this->camrotation = 0;
    this->mainrotation = glm::mat4(1.0f);
    this->countTime = 40;
    this->speed = 0.2;
    power = 10;
    // delta = 0.01;
    // yvelocity = 0;
    // xautovelocity = 0;
    // zautovelocity = 0;
    // yaccel = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // GLfloat vertex_buffer_data[] = {
    //     -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    //     -1.0f,-1.0f, 1.0f,
    //     -1.0f, 1.0f, 1.0f, // triangle 1 : end
    //     1.0f, 1.0f,-1.0f, // triangle 2 : begin
    //     -1.0f,-1.0f,-1.0f,
    //     -1.0f, 1.0f,-1.0f, // triangle 2 : end
    //     1.0f,-1.0f, 1.0f,
    //     -1.0f,-1.0f,-1.0f,
    //     1.0f,-1.0f,-1.0f,
    //     1.0f, 1.0f,-1.0f,
    //     1.0f,-1.0f,-1.0f,
    //     -1.0f,-1.0f,-1.0f,
    //     -1.0f,-1.0f,-1.0f,
    //     -1.0f, 1.0f, 1.0f,
    //     -1.0f, 1.0f,-1.0f,
    //     1.0f,-1.0f, 1.0f,
    //     -1.0f,-1.0f, 1.0f,
    //     -1.0f,-1.0f,-1.0f,
    //     -1.0f, 1.0f, 1.0f,
    //     -1.0f,-1.0f, 1.0f,
    //     1.0f,-1.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f,
    //     1.0f,-1.0f,-1.0f,
    //     1.0f, 1.0f,-1.0f,
    //     1.0f,-1.0f,-1.0f,
    //     1.0f, 1.0f, 1.0f,
    //     1.0f,-1.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f,
    //     1.0f, 1.0f,-1.0f,
    //     -1.0f, 1.0f,-1.0f,
    //     1.0f, 1.0f, 1.0f,
    //     -1.0f, 1.0f,-1.0f,
    //     -1.0f, 1.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f,
    //     -1.0f, 1.0f, 1.0f,
    //     1.0f,-1.0f, 1.0f
    // };
    std::vector<GLfloat> vertices;
  	std::vector<GLfloat> uvs;
  	std::vector<GLfloat> normals; // Won't be used at the moment.
    bool res = loadOBJRect("../src/fighter_jet.obj", vertices, uvs, normals);
    this->object = create3DObject(GL_TRIANGLES, vertices.size()/3, &vertices[0], color, GL_FILL);
    // this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale(glm::vec3(0.4f, 0.4f ,0.4f));
    glm::mat4 rotate1   = glm::rotate((float) (this->rotation2 * M_PI / 180.0f), glm::vec3(1, 0, 0));// plane made was 90 wrong pitch
    glm::mat4 rotate    = glm::rotate((float) (this->rotation  * M_PI / 180.0f), glm::vec3(0, -1, 0));// roll
    glm::mat4 rotate2   = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(0, 0, 1)); // yaw
    glm::mat4 rotate3   = glm::rotate((float) (this->rotation3 * M_PI / 180.0f), glm::vec3(0, 1, 0)); // weird but tilt
    mainrotation = rotate*rotate1*rotate2*rotate3;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * mainrotation * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() {
  // this->position.z += this->zautovelocity;
  // this->position.x += this->xautovelocity;
  // this->position.y += this->yvelocity;
  // this->yvelocity += this->yaccel;
  // if(this->position.y <= 0 && this->yvelocity < 0) this->position.y = 0, this->yvelocity = 0;
}
bounding_box_t Ball::bounding_box() {
  bounding_box_t bbox = { this->position.x, this->position.y, this->position.z, 0.75, 1.75, this->mastheight};
  return bbox;
}
