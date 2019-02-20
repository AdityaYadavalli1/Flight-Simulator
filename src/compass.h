#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float size);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float rotation);
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
    VAO *main_body1;
};

#endif // COMPASS_H
