
#include "VBF_CommonPhysics.hpp"

// a Physics Object should have a VBF::World and the related objects (Physical Bodies) in it
// it should have a bridge with the graphics to visualize and 
//it should be optional to speed up the calculations  when needed

//FOR VBF Simulations, we would like to have a world, a ground referece and objects in it
//ofcourse physics can be simulated without a ground but I don't think this is going to 
//make my life easier as it is, the documentations are missing 

//defualt constructor0
VBF::CommonPhysics::CommonPhysics(): m_VBF_world(new VBF::World()),
                                m_ground(new VBF::Static_Cube()){   }

//constructor1
VBF::CommonPhysics::CommonPhysics(VBF::World* vbf_world,
                             VBF::StaticBody* ground,
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

//constructor2
VBF::CommonPhysics::CommonPhysics(VBF::World* vbf_world):
                              m_VBF_world(vbf_world)    {   } 

//constructor3                              
VBF::CommonPhysics::CommonPhysics(VBF::World* vbf_world, VBF::RigidBody* vbf_rbody):
                        m_VBF_world(vbf_world)
{
    m_VBF_rbody.push_back(vbf_rbody);
}
                        
//destructor                           
VBF::CommonPhysics::~CommonPhysics(){
    delete m_VBF_world;
    
    for (size_t i=0; i < m_VBF_rbody.size(); ++i){
    delete m_VBF_rbody[i];
    m_VBF_rbody[i] = nullptr;
    }
    
    m_VBF_world = nullptr;
}
  
void VBF::CommonPhysics::initPhysics()
{
    if(!m_VBF_world->is_initialized()) {
        m_VBF_world->intialize_new_world(); }
	
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

