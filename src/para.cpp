#include "para.h"
#include "main.h"
#include "loader.h"
Para::Para(float x, float y, float z, float size) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->size = size;
    this->counter = 0;
    this->countTime = 200;
    speed = 1;
    this->inRadius = 0;
    std::vector<GLfloat> vertices;
  	std::vector<GLfloat> uvs;
  	std::vector<GLfloat> normals; // Won't be used at the moment.
    bool res = loadOBJRect("../src/parachute.obj", vertices, uvs, normals);
    this->main_body = create3DObject(GL_TRIANGLES, vertices.size()/3, &vertices[0], COLOR_YELLOW, GL_FILL);
    this->bb = create3DObject(GL_TRIANGLES, vertices.size()/3, &vertices[0], COLOR_BLACK, GL_LINE);
}

void Para::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f ,1.0f));
    glm::mat4 rotate   = glm::rotate((float) (M_PI / 180.0f), glm::vec3(1, 0, 0));
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->main_body);
    draw3DObject(this->bb);
}

void Para::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Para::tick() {
  if(this->inRadius)
  {
    this->position.y -= 0.05;
  }
}

bounding_box_t Para::bounding_box() {
  bounding_box_t bbox = {this->position.x, this->position.y + 10, this->position.z, 5*this->size, 5*this->size, 5*this->size};
  return bbox;
}
