#define AVOID_SINGULARITIES 2

#include "gepetto/viewer/corba/client.hh"
#include "viewer.h"

// Demonstration d'affichage du drone dans le viewer et vérification des translations
// et rotations.

int main()
{
    Viewer viewer;

    const char* dronename = PIE_SOURCE_DIR"/data/quadrotor_base.stl";
    viewer.createDrone(dronename);


    float x = 1.0;
    float y = 0.0;
    float z = 1.0;
    float roll = 0.0;
    float pitch = 0.0;
    float yaw = 0.0;

    usleep(2000000);

    // Translation Test
    std::cout << "Translation Test" << std::endl;
    for (int i = 0;i<200;i++)
    {
        x = 0.f + (float)i/200.f;
        y = 0.f - (float)i/120.f;
        z = 1.f + (float)i/140.f;

        viewer.moveDrone(x,y,z,roll,pitch,yaw);
        usleep(50000);
    }
    usleep(5000000);

    // Yaw Test
    std::cout << "Yaw Test" << std::endl;
    for(int i = 0;i<100;i++)
    {
        yaw = 0.02f;

        viewer.moveDrone(x,y,z,roll,pitch,yaw);
        usleep(50000);
    }
    yaw = 0.0f;
    usleep(3000000);


    // Pitch Test
    std::cout << "Pitch Test" << std::endl;
    for(int i = 0;i<100;i++)
    {
        pitch = 0.02f;

        viewer.moveDrone(x,y,z,roll,pitch,yaw);
        usleep(50000);
    }
    pitch = 0.0f;
    usleep(3000000);


    // Roll Test
    std::cout << "Roll Test" << std::endl;
    for (int i=0; i<100; i++)
    {
        roll = 0.02f;

        viewer.moveDrone(x,y,z,roll,pitch,yaw);
        usleep(50000);
    }

    return 0;
}

