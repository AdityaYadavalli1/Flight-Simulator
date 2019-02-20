#include "main.h"

#ifndef FUELCAN_H
#define FUELCAN_H


class Fuelcan {
public:
    Fuelcan() {}
    Fuelcan(float x, float y, float z, float size);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();
    double speed;
    float size;
    int health;
    int counter;
    int countTime;
    int isBoss;
private:
    VAO *object;
};

#endif // MONSTER_H
