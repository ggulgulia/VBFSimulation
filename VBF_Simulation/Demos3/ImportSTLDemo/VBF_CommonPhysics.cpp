
#include "VBF_CommonPhysics.hpp"

//defualt constructor0, the pointers point to uninitialized 
//member objects

//constructor1
VBF::CommonPhysics::CommonPhysics(): m_VBF_world(new VBF::World()),
                                m_ground(new VBF::RigidBody()){   }

//constructor2 taking one ground and a vector of rigid bodies
VBF::CommonPhysics::CommonPhysics(VBF::World* vbf_world,
                             VBF::RigidBody* ground,
                             std::vector<VBF::RigidBody*>& vbf_rbody_vect):
                                m_VBF_world(vbf_world), m_ground(ground) {
        m_shape.push_back(m_ground->get_shape());
        m_VBF_world->add_rigid_bodies_to_world(m_ground->get_rbody());
        for(size_t i=0; i < vbf_rbody_vect.size(); ++i){
            m_VBF_rbody.push_back(vbf_rbody_vect[i]);
            m_shape.push_back(vbf_rbody_vect[i]->get_shape());
            m_VBF_world->add_rigid_bodies_to_world(vbf_rbody_vect[i]->get_rbody());
       }
}

//constructor3 taking one ground and one rigid body
VBF::CommonPhysics::CommonPhysics(VBF::World* vbf_world,
                             VBF::RigidBody* ground,
                             VBF::RigidBody* vbf_rbody):
                                m_VBF_world(vbf_world), m_ground(ground) {
        m_shape.push_back(m_ground->get_shape());
        m_VBF_world->add_rigid_bodies_to_world(m_ground->get_rbody());
        
        m_VBF_rbody.push_back(vbf_rbody);
        m_shape.push_back(vbf_rbody->get_shape());
        m_VBF_world->add_rigid_bodies_to_world(vbf_rbody->get_rbody());
}

//constructor4
VBF::CommonPhysics::CommonPhysics(VBF::World* vbf_world):
                              m_VBF_world(vbf_world)    {   } 

//constructor5                            
VBF::CommonPhysics::CommonPhysics(VBF::World* vbf_world, VBF::RigidBody* vbf_rbody):
                        m_VBF_world(vbf_world)
{
    m_VBF_rbody.push_back(vbf_rbody);
}
                        
//destructor                           
VBF::CommonPhysics::~CommonPhysics(){
    
    for (size_t i=0; i < m_VBF_rbody.size(); ++i){
    //don't delete the rigid bodies since
    //the member m_VBF_rbody refers to the bodies
    //that are externally passed to the constructor
    //delete m_VBF_rbody[i];
    //m_VBF_rbody[i] = nullptr;
    }
    
    //same reason for not freeing the resources
    //held by m_VBF_World
    //delete m_VBF_world;
    m_VBF_world = nullptr;
}
  
void VBF::CommonPhysics::initPhysics()
{
    if(!m_VBF_world->is_initialized()) {
        m_VBF_world->initialize_new_world(); }
	
	if (m_VBF_world->get_debug_drawer())
		m_VBF_world->get_debug_drawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe+btIDebugDraw::DBG_DrawContactPoints);
	
}

void VBF::CommonPhysics::stepSimulation(double deltaTime){
			m_VBF_world->step_simulation(deltaTime);
}


void VBF::CommonPhysics::syncPhysicsToGraphics() {   
}

void  VBF::CommonPhysics::debugDraw(int debugDrawFlags){
    btWorld *temp_world = m_VBF_world->get_world();
 	if (temp_world){
		if (temp_world->getDebugDrawer()){
			temp_world->getDebugDrawer()->setDebugMode(debugDrawFlags);
		}
        temp_world->debugDrawWorld();
    } 
}

btWorld*  VBF::CommonPhysics::get_world() const{
    return m_VBF_world->get_world();
}

