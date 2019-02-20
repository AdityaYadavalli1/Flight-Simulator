#include "arrow.h"
#include "main.h"
#include "loader.h"
Arrow::Arrow(float x, float y, float z, float size) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->size = size;
    speed = 1;
    std::vector<GLfloat> vertices;
  	std::vector<GLfloat> uvs;
  	std::vector<GLfloat> normals; // Won't be used at the moment.
    bool res = loadOBJ("../src/arrow.obj", vertices, uvs, normals);
    this->main_body = create3DObject(GL_TRIANGLES, vertices.size()/3, &vertices[0], COLOR_BLUE, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale(glm::vec3(10.0f, 10.0f ,10.0f));
    glm::mat4 rotate   = glm::rotate((float) (180* M_PI / 180.0f), glm::vec3(1, 0, 0));
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->main_body);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick() {
  this->position.x += -0.03 + static_cast<float> (rand()) / (static_cast <float> (RAND_MAX/(0.06)));
  this->position.z += -0.03 + static_cast<float> (rand()) / (static_cast <float> (RAND_MAX/(0.06)));
  if(this->counter < this->countTime) this->counter++;
}

bounding_box_t Arrow::bounding_box() {
  bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 4*this->size, 4*this->size, 2*this->size};
  return bbox;
}
