#include "main.h"

#ifndef SMOKE_H
#define SMOKE_H


class Smoke {
public:
    Smoke() {}
    Smoke(float x, float y, float z, float size);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    double speed;
    float size;
    int health;
    int counter;
    int countTime;
    int isBoss;
private:
    VAO *main_body;
};

#endif // MONSTER_H
