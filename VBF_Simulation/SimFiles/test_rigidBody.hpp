#ifndef TEST_RIGID_BODY_H
#define TEST_RIGID_BODY_H

#include <VBF_StaticMesh.hpp>
#include <VBF_Static_Cube.hpp>
#include <VBF_Static_Sphere.hpp>

#include <VBF_KinematicMesh.hpp>
#include <VBF_Kinematic_Cube.hpp>
#include <VBF_Kinematic_Sphere.cpp>

#include <VBF_Dynamic_Cube.hpp>
#include <VBF_Dynamic_Sphere.hpp>
#include <VBF_DynamicMesh.hpp>


void releaseResources(std::vector<btCollisionShape*> &collShape, std::vector<btRigidBody*> &rbody,
                      std::vector<btDefaultMotionState*> &motionState){
    for(size_t i=0; i<collShape.size(); ++i){
        delete collShape[i];
        collShape[i] = nullptr;
    }
    for(size_t i=0; i<rbody.size(); ++i){
        delete rbody[i];
        rbody[i] = nullptr;
    }
    for(size_t i=0; i<motionState.size(); ++i){
        delete motionState[i];
        motionState[i] = nullptr;
    }

    std::cout << "Successfully freed the memory\n";
}

VBF::Static_Cube* get_ground(){

    //create a ground
    double grLength = 50;
    btVector3 grOrigin = btVector3(0.0, -4-grLength, 0.0);
    size_t grIndex = 23;
    
    return new VBF::Static_Cube(grLength, grOrigin, grIndex);
 
}

// template functions for static and kinematic cubes
template<typename CubeType>
void get_cubes(std::vector<VBF::RigidBody*>& rigid_bodies_vector){

    //create more objects cube objects
    double cubeLen = 1.0;
    size_t cubeIndex = 12;
    size_t array_size = 5;

    for(size_t k=0; k<array_size; ++k){
        for (size_t i = 0; i < array_size; ++i) {
           for (size_t j = 0; j < array_size; ++j) {
               
               btVector3 cubeOrigin = btVector3(2.0*i, 20+2.0*k, 2.0*j);
               cubeIndex += j + array_size*i + array_size*k;
               CubeType *cube = new CubeType(cubeLen, cubeOrigin,  cubeIndex);
               rigid_bodies_vector.push_back(cube);
           } 
        }
    }
}

//specialized template functions for rigid body type cube
template<>
void get_cubes<VBF::Dynamic_Cube>(std::vector<VBF::RigidBody*>& rigid_bodies_vector){

    //create more objects cube objects
    double cubeLen = 1.0;
    double cubeMass = 1.0; //  these are dynamic objects
    size_t cubeIndex = 12;
    size_t array_size = 5;

    for(size_t k=0; k<array_size; ++k){
        for (size_t i = 0; i < array_size; ++i) {
           for (size_t j = 0; j < array_size; ++j) {
               
               btVector3 cubeOrigin = btVector3(2.0*i, 20+2.0*k, 2.0*j);
               cubeIndex += j + array_size*i + array_size*k;
               VBF::Dynamic_Cube* cube = new VBF::Dynamic_Cube(cubeLen, cubeOrigin,  cubeMass);
               rigid_bodies_vector.push_back(cube);
           } 
        }
    }
}



//template function for static or kinematic spehere
template<typename SphereType>
void get_spheres(std::vector<VBF::RigidBody*>& sphere_vector){
    
    double sphereRad = 1.0;
    size_t sphereIndex = 44;
    size_t array_size = 5;
       for(size_t k=0; k<array_size; ++k){ 
           for (size_t i = 0; i < array_size; ++i) {
               for (size_t j = 0; j < array_size; ++j) {
                   
                   btVector3 sphereOrigin = btVector3(2.0*i, 20+2.0*k, 2.0*j);
                   sphereIndex += j + array_size*i + array_size*k;
                   SphereType *sph = new SphereType(sphereRad, sphereOrigin, sphereIndex);
                   sphere_vector.push_back(sph);
               } 
            }
        }

}

//specialized template function for dynamic rigid body type sphere
template<>
void get_spheres<VBF::Dynamic_Sphere>(std::vector<VBF::RigidBody*>& sphere_vector){
    
    double sphereRad = 1.0;
    double sphereMass = 1.0;
    size_t sphereIndex = 44;
    size_t array_size = 5;
       for(size_t k=0; k<array_size; ++k){ 
           for (size_t i = 0; i < array_size; ++i) {
               for (size_t j = 0; j < array_size; ++j) {
                   
                   btVector3 sphereOrigin = btVector3(2.0*i, 20+2.0*k, 2.0*j);
                   sphereIndex += j + array_size*i + array_size*k;
                   VBF::Dynamic_Sphere *sph = new VBF::Dynamic_Sphere(sphereRad, sphereOrigin, sphereMass);
                   sphere_vector.push_back(sph);
               } 
            }
        }

}


#endif //TEST_RIGIDBODY_H
