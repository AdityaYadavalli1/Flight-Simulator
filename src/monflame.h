#include "main.h"

#ifndef MONFLAME_H
#define MONFLAME_H


class Monflame {
public:
    Monflame() {}
    Monflame(float x, float y, float z, float angle, float velocity, float xvelocity, float yvelocity, float zvelocity, color_t color);
    glm::vec3 position;
    glm::vec3 mpos;
    glm::vec3 ballpos;
    float rotation;
    float rotation1;
    float rotation2;
    glm::mat4 mainrotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    float dist;
    float vecx;
    float vecy;
    float vecz;
    float yvelocity;
    float zvelocity;
    float xvelocity;
    float yaccel;
    float velocity;
    float angle;
    float size;
    int damage;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // MONFLAME_H
