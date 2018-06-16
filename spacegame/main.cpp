#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;
using namespace std;

struct particle
{
    double x;
    double y;
    double dx;
    double dy;
    double mass;
};

//gravitational constant
//not used yet; 
double gravity = 0.5;

struct gravity_vector {
    double x;
    double y;
    double magnitude;
};

int round_int(double number)
{
    number += 0.5;
    return (int) number;
}

// TODO: needs testing
double get_distance(double x1, double x2,
                    double y1, double y2)
{
    double a = pow((x2 - x1), 2);
    double b = pow((y2 - y1), 2);
    double distance = sqrt(a + b);
    return distance;
}

// TODO: needs testing
double get_gravity_magnitude(double m1, double m2,
                             double distance)
{
    double grav_acc = gravity * m1 * m2;
    grav_acc = grav_acc / pow(distance, 2);
}

// TODO: needs testing
gravity_vector get_gravity_vector(particle left,
                                  particle right)
{
    double distance = get_distance(left.x, right.x,
                                   left.y, right.y);

    double magnitude = get_gravity_magnitude(left.mass,
                                             right.mass,
                                             distance);
    gravity_vector v;
    v.magnitude = magnitude;
    v.x = (right.x - left.x);
    v.y = (right.y - left.y);
    return v;
}

int main(int argc, char* argv[])
{
    //Setup the screen
    screen(256, 256, 0, "Gravity boyyyys");

    //init all the game objects
    particle ship;
    ship.x = 20;
    ship.y = 20;
    ship.dx = 0.1;
    ship.dy = 0;
    ship.mass = 1;
    
    particle p2 = ship;
    p2.x = 20;
    p2.y = 25;
    p2.dy = .5;

    //main loop
    bool done = false;

    float time, oldTime;
    while(!done)
    {
        //calculate time shit
        oldTime = time;
        waitFrame(oldTime, 0.05);
        time = getTime();

        // TODO need to figure out how to do change in
        // velocity due to gravitational acc
        // between two objects. 
        // Hint: use vectors?

        //iterate over all the game objects and update them
        //* Calculate gravity & update vectors
        double change_in_vel_due_to_gravity = .03;
        ship.dy += change_in_vel_due_to_gravity;

        //* apply vectors
        ship.x += ship.dx;
        ship.y += ship.dy;
        p2.x += p2.dx;
        p2.y += p2.dy;

        //draw the background
        // usage: cls(ColorRGB color = RGB_Black)
        cls(RGB_Black);
        
        string quit_message = "Press 'q' to quit";
        print(quit_message, 2, 2);
     
        readKeys();
        if(keyDown(SDLK_q))
        {
            done = true;
        }
        
        if(keyDown(SDLK_UP))
        {
            ship.dy += -0.04;
        }
        if(keyDown(SDLK_DOWN))
        {
            ship.dy += 0.04;
        }
        if(keyDown(SDLK_LEFT))
        {
            ship.dx += -0.04;
        }
        if(keyDown(SDLK_RIGHT))
        {
            ship.dx += 0.04;
        }
        
        //draw the objects
        pset(round_int(ship.x),
             round_int(ship.y),
             ColorRGB(0, 128, 0));
        
        pset(round_int(p2.x),
             round_int(p2.y),
             ColorRGB(0, 128, 0));  

        redraw();
        //sleep();
    }

    return 0;
}
