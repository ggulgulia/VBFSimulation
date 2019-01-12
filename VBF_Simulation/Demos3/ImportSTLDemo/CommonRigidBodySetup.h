
#ifndef COMMON_RIGID_BODY_SETUP_H
#define COMMON_RIGID_BODY_SETUP_H

//todo: replace this 'btBulletDynamicsCommon.h' header with specific used header files
#include <bullet/btBulletDynamicsCommon.h>
#include "CommonPhysicsSetup.h"
#include "VBF_World.hpp"
#include <vector>

class CommonRigidBodySetup{

    private:
	//keep the collision shapes, for deletion/cleanup
	btWorld*          m_world;
	btCollConfig*     m_collisionConfiguration;
	btDispatcher_iwb* m_dispatcher;
	btInterface*	  m_broadphase;
	btSolver*         m_solver;
	std::vector<btCollisionShape*> m_collisionShapes;
	

    public:
    //constructor
	CommonRigidBodySetup()
	   :m_broadphase(new btDbvtBroadphase()),
		m_solver(new btSequentialImpulseConstraintSolver),
		m_collisionConfiguration(new btDefaultCollisionConfiguration())
		{
	        m_dispatcher = new	btCollisionDispatcher(m_collisionConfiguration);
	        m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	        m_world->setGravity(btVector3(0, -10, 0));
	    }

	virtual void createEmptyDynamicsWorld(){		
		m_collisionConfiguration = new btDefaultCollisionConfiguration();
		m_dispatcher = new	btCollisionDispatcher(m_collisionConfiguration);
		m_broadphase = new btDbvtBroadphase();
		m_solver = new btSequentialImpulseConstraintSolver;
		m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
		m_world->setGravity(btVector3(0, -10, 0));
	}


	virtual void stepSimulation(float deltaTime){
		if (m_world){
			m_world->stepSimulation(deltaTime);
		}
	}


	virtual void exitPhysics(){
		if (m_world){

            int i;
            for (i = m_world->getNumConstraints() - 1; i >= 0; i--){
                m_world->removeConstraint(m_world->getConstraint(i));
            }
			for (i = m_world->getNumCollisionObjects() - 1; i >= 0; i--){
				btCollisionObject* obj = m_world->getCollisionObjectArray()[i];
				btRigidBody* body = btRigidBody::upcast(obj);
				if (body && body->getMotionState())
				{
					delete body->getMotionState();
				}
				m_world->removeCollisionObject(obj);
				delete obj;
			}
		}
		
		//delete collision shapes
		for (int j = 0; j<m_collisionShapes.size(); j++){
			delete m_collisionShapes[j];
			m_collisionShapes[j] = nullptr;
		}
		delete m_world;
		delete m_solver;
		delete m_broadphase;
		delete m_dispatcher;
		delete m_collisionConfiguration;
	}

virtual void syncPhysicsToGraphics(GraphicsPhysicsBridge& gfxBridge){
	if (m_world)
	{
		gfxBridge.syncPhysicsToGraphics(m_world);
	}
}

virtual void debugDraw(int debugDrawFlags){
 	if (m_world)
    {
		if (m_world->getDebugDrawer())
		{
			m_world->getDebugDrawer()->setDebugMode(debugDrawFlags);
		}
        m_world->debugDrawWorld();
    }

}

btBoxShape* createBoxShape(const btVector3& halfExtents){

	btBoxShape* box = new btBoxShape(halfExtents);
	return box;
}

btRigidBody* createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape,  const btVector4& color = btVector4(1, 0, 0, 1)){
	    btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

	    //rigidbody is dynamic if and only if mass is non zero, otherwise static
	    bool isDynamic = (mass != 0.f);

	    btVector3 localInertia(0, 0, 0);
	    if (isDynamic)
		    shape->calculateLocalInertia(mass, localInertia);

	    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

    #define USE_MOTIONSTATE 1
    #ifdef USE_MOTIONSTATE
	    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	    btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);
	    btRigidBody* body = new btRigidBody(cInfo);
    #else
	    btRigidBody* body = new btRigidBody(mass, 0, shape, localInertia);
	    body->setWorldTransform(startTransform);
    #endif
	    body->setUserIndex(-1);
	    m_world->addRigidBody(body);
	    return body;
    }
};

#endif //COMMON_RIGID_BODY_SETUP_H

