#define _USE_MATH_DEFINES
#include <math.h>

class SpaceObject
{
private:
    float x, y, xv, yv, spd, accel, max_spd;
    float move_dir, move_dir_spd, move_dir_accel, move_dir_max_spd;
    float face_dir, face_dir_spd, face_dir_accel, face_dir_max_spd;
    float timestep; //this might actually need to be an int
    SDL_Rect bound;
    void updateVels();
public:
    void steerRight();
    void steerLeft();
    void moveForward();
    void getX() { return x; }
    void getY() { return y; }
};

void SpaceObject::updateVels() {
    if (spd < max_spd)
        spd += accel*timestep;
    xv = spd + cos(move_dir*M_PI/180);
    yv = spd + sin(move_dir*M_PI/180);
}

void SpaceObject::steerRight() {
    if (move_dir_spd < move_dir_max_spd)
    {
        if (move_dir_spd < 0)
            move_dir_spd += move_dir_accel*timestep/4;
        move_dir_spd += move_dir_accel*timestep;
    }
    move_dir += move_dir_spd*timestep;
}
void SpaceObject::steerLeft() {
    if (move_dir_spd > -move_dir_max_spd)
    {
        if (move_dir_spd > 0)
            move_dir_spd -= move_dir_accel*timestep/4;
        move_dir_spd -= move_dir_accel*timestep;
    }
    move_dir += move_dir_spd*timestep;
}
void SpaceObject::moveForward() {
    updateVels();
    x += xv*timestep;
    y += yv*timestep;
}
