
#include <stdio.h>
#include "BasicDemoPhysicsSetup.h"

int main(int argc, char* argv[])
{
	BasicDemoPhysicsSetup physicsSetup;
	GraphicsPhysicsBridge br;
	physicsSetup.initPhysics(br);
	physicsSetup.stepSimulation(1./60.);
	physicsSetup.exitPhysics();

	printf("hello\n");
}
