#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z, float size, int health);
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
    VAO* bb;
};

#endif // MONSTER_H
