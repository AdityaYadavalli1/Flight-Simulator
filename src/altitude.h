#include "main.h"

#ifndef ALTITUDE_H
#define ALTITUDE_H


class Altitude {
public:
    Altitude() {}
    Altitude(float x, float y, float size);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float curAltitude);
    bounding_box_t bounding_box();
    double speed;
    bool inRadius;
    float size;
    int health;
    int counter;
    int countTime;
    int isBoss;
private:
    VAO *main_body;
};

#endif // MONSTER_H
