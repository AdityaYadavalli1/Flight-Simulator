#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bounding_box_t bounding_box();
    void tick();
    int power;
    double speed;
    float delta;
    float mastheight;
    float mastthickness;
    float yaccel;
    float yvelocity;
    float zautovelocity;
    float xautovelocity;
    int countTime;
private:
    VAO *object;
};

#endif // BALL_H
