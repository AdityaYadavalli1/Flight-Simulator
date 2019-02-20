#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z, float size, int health);
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
    VAO *bb;
};

#endif // MONSTER_H
