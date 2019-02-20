#include "monster.h"
#include "main.h"
#include "loader.h"
Monster::Monster(float x, float y, float z, float size, int health) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->size = size;
    this->health = health;
    this->counter = 0;
    this->countTime = 200;
    speed = 1;
    this->isBoss = 0;
    std::vector<GLfloat> vertices;
  	std::vector<GLfloat> uvs;
  	std::vector<GLfloat> normals; // Won't be used at the moment.
    bool res = loadOBJ("../src/mushroom.obj", vertices, uvs, normals);
    this->main_body = create3DObject(GL_TRIANGLES, vertices.size()/3, &vertices[0], COLOR_GREEN, GL_FILL);
    this->bb = create3DObject(GL_TRIANGLES, vertices.size()/3, &vertices[0], COLOR_BLACK, GL_LINE);
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->main_body);
    draw3DObject(this->bb);
}

void Monster::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Monster::tick() {
  this->position.x += -0.03 + static_cast<float> (rand()) / (static_cast <float> (RAND_MAX/(0.06)));
  this->position.z += -0.03 + static_cast<float> (rand()) / (static_cast <float> (RAND_MAX/(0.06)));
  if(this->counter < this->countTime) this->counter++;
}

bounding_box_t Monster::bounding_box() {
  bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, this->size, this->size, 2*this->size};
  return bbox;
}
