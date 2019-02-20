#include "compass.h"
#include "main.h"

Compass::Compass(float x, float y, float size) {
    this->position = glm::vec3(x, y, 1);
    this->size = 1;
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // GLfloat vertex_buffer_data[] = {
    //    1.0,  1.0, 0.0,
    //    1.0, -1.0, 0.0,
    //   -1.0,  1.0, 0.0,
    //    1.0, -1.0, 0.0,//2nd triangle
    //   -1.0,  1.0, 0.0,
    //   -1.0, -1.0, 0.0,
    // };
    GLfloat vertex_buffer_data[] = {
        -1.0f,0.0f,-1.0f, // triangle 1 : begin
        -1.0f,0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,0.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,0.0f, 1.0f,
        -1.0f,0.0f,-1.0f,
        1.0f,0.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,0.0f,-1.0f,
        -1.0f,0.0f,-1.0f,
        -1.0f,0.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,0.0f, 1.0f,
        -1.0f,0.0f, 1.0f,
        -1.0f,0.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,0.0f, 1.0f,
        1.0f,0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,0.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,0.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,0.0f, 1.0f
    };
    GLfloat vertex_buffer_data1[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 0.0f, 1.0f, // triangle 1 : end
        1.0f, 0.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 0.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 0.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 0.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 0.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f,-1.0f,
        -1.0f, 0.0f,-1.0f,
        1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f,-1.0f,
        -1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };
    this->main_body = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->main_body1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, COLOR_GREY, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale(glm::vec3(0.01f, 0.1*this->size, 0.01f));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate *scale);
    glm::mat4 MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->main_body);
    draw3DObject(this->main_body1);
}

void Compass::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Compass::tick(float rotation) {
  this->rotation = rotation;
  // this->rotation = 0.1*rotation;
  // float rotate = glm::angle(ball, arrow);
  // this->rotation = 0.5*rotate;

}

bounding_box_t Compass::bounding_box() {
  bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 1, 1, 1};
  return bbox;
}
