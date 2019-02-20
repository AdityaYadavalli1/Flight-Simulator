#include "fuelcan.h"
#include "main.h"
#include "loader.h"
Fuelcan::Fuelcan(float x, float y, float z, float size) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    std::vector<GLfloat> vertices;
  	std::vector<GLfloat> uvs;
  	std::vector<GLfloat> normals; // Won't be used at the moment.
    bool res = loadOBJRectwoUV("../src/gascanhp.obj", vertices, normals);
    this->object = create3DObject(GL_TRIANGLES, vertices.size()/3, &vertices[0], COLOR_BLACK, GL_FILL);
}

void Fuelcan::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f ,1.0f));
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fuelcan::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Fuelcan::tick() {
  // float LO = -0.1;
  // float HI = 0.1;
  // this->position.x += LO + static_cast<float> (rand()) / (static_cast <float> (RAND_MAX/(HI-LO)));
  // this->position.z += LO + static_cast<float> (rand()) / (static_cast <float> (RAND_MAX/(HI-LO)));

}

bounding_box_t Fuelcan::bounding_box() {
  bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 2, 2, 2};
  return bbox;
}
