#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float rotation1;
    float rotation2;
    float rotation3;
    int fuel;
    int max_altitude;
    glm::mat4 mainrotation;
    float camrotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bounding_box_t bounding_box();
    void tick();
    double speed;
    int power;
    float mastheight;
    float mastthickness;
    int countTime;
private:
    VAO *object;
};

#endif // BALL_H
