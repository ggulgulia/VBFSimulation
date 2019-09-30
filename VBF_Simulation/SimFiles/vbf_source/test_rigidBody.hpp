
/*! @file test_rigidBody.hpp */

#ifndef TEST_RIGID_BODY_H
#define TEST_RIGID_BODY_H

#include <VBF_StaticMesh.hpp>
#include <VBF_Static_Cube.hpp>
#include <VBF_Static_Sphere.hpp>
#include <VBF_Static_Ground.hpp>

#include <VBF_KinematicMesh.hpp>
#include <VBF_Kinematic_Cube.hpp>
#include <VBF_Kinematic_Sphere.cpp>

#include <VBF_Dynamic_Cube.hpp>
#include <VBF_Dynamic_Sphere.hpp>
#include <VBF_DynamicMesh.hpp>
#include <VBF_Dynamic_Cylinder.hpp>
    /*!
     * @brief This file imports all the rigid body types so far
     * created and additionally some functions are defined in this file 
     * to assist creation of rigid body pointers on a contiguous chunk 
     * of memory. This file mainly prevents the #includes in main
     * file from bloating
     * @date 2019
     */

/*! collision margin as prescribed in bullet physics engine 
 * usage (on the internet) 
 */
static const double collMarg = 0.004;

/*! @brief helper function that releases the memory held by a rigid body 
 * container
 *
 * @details a bullet rigid body is defined by its `btCollisionShape` and
 * `btRigidBody` parameter. This helper function is designed to clean
 * the pointer stored in `std::vector<btCollisionShape*>` and 
 * `std::vector<btRigidBody*>`, and both the containers need not 
 * be of same size (see source code)
 */
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


/*! @brief helper function to create a datum/ground object
 * for bullet world
 *
 * @detail The datum/ground is a static objct, meaning any object in
 * the physics world colliding with the ground will react according to
 * the laws of physics while the ground will stay unaffected
 *
 * @bug the ground object in the physics simulation
 * is not visible in the graphic even though it can 
 * be seen to be present
 */
VBF::Static_Ground* get_ground(const double collMarg){

    //create a ground
    float grPos = -20; /*! this ground position/height has been found 
                        * to be optimal given the size of the 
                        * vibratory bowl feeder. In short:
                        * this has been derived through trial and error
                        */
    btVector3 grNormal= btVector3(0.0, 1.0, 0.0); /*! ground normal along y-direction, which is the 
                                                   * vertical direction in bullet physics world
                                                   */
    btVector3 grOrigin;
    size_t grIndex = 245;
    
    return new VBF::Static_Ground(grNormal, grPos, grOrigin, collMarg, grIndex);
 
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
               CubeType *cube = new CubeType(cubeLen, cubeOrigin,  collMarg, cubeIndex);
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
               VBF::Dynamic_Cube* cube = new VBF::Dynamic_Cube(cubeLen, cubeOrigin,  collMarg, cubeMass);
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
                   SphereType *sph = new SphereType(sphereRad, sphereOrigin, collMarg, sphereIndex);
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
                   VBF::Dynamic_Sphere *sph = new VBF::Dynamic_Sphere(sphereRad, sphereOrigin, collMarg, sphereMass);
                   sphere_vector.push_back(sph);
               } 
            }
        }

}


#endif //TEST_RIGIDBODY_H
