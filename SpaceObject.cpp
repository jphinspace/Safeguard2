#define _USE_MATH_DEFINES#include <SDL.h>
#include <math.h>
//Player ships, NPCs, asteroids, bullets, explosions, particles
class SpaceObject{
    private:
        float x, y, xv, yv, spd, accel, max_spd;
        float move_dir, move_dir_spd, move_dir_accel, move_dir_max_spd;
        float face_dir, face_dir_spd, face_dir_accel, face_dir_max_spd;
        float timestep;
        SDL_Rect bound;
        void updateVelocity();
    public:
        void steerRight();
        void steerLeft();
        void moveForward();
        void getX() { return x; }
        void getY() { return y; }
};
//This runs continuously
void SpaceObject::updateVelocity(){
    if (spd < max_spd)
        spd += accel*timestep;
    xv = spd + cos(move_dir*M_PI/180);
    yv = spd + sin(move_dir*M_PI/180);
}
//Generic implementation, set accels to 1 for instant turn
void SpaceObject::steerRight(){
    if (move_dir_spd < move_dir_max_spd)
    {
        if (move_dir_spd < 0)
            move_dir_spd += move_dir_accel*timestep/4;
        move_dir_spd += move_dir_accel*timestep;
    }
    move_dir += move_dir_spd*timestep;
}
void SpaceObject::steerLeft(){
    if (move_dir_spd > -move_dir_max_spd)
    {
        if (move_dir_spd > 0)
            move_dir_spd -= move_dir_accel*timestep/4;
        move_dir_spd -= move_dir_accel*timestep;
    }
    move_dir += move_dir_spd*timestep;
}//This pretty much runs continuously too
void SpaceObject::moveForward(){
    updateVels();
    x += xv*timestep;
    y += yv*timestep;
}
