
#include "VehicleDemo.h"
#include <OpenGL/GlutStuff.h>
#include <OpenGL/GLDebugDrawer.h>
#include <bullet/btBulletDynamicsCommon.h>
GLDebugDrawer	gDebugDrawer;

int main(int argc,char** argv)
{

        VehicleDemo* vehicleDemo = new VehicleDemo;

        vehicleDemo->initPhysics(); 
		vehicleDemo->getDynamicsWorld()->setDebugDrawer(&gDebugDrawer);

        return glutmain(argc, argv,640,480,"Bullet Vehicle Demo. http://www.continuousphysics.com/Bullet/phpBB2/", vehicleDemo);
}

