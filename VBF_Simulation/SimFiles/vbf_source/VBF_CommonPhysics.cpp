
#include <VBF_CommonPhysics.hpp>


//destructor                           
VBF::CommonPhysics::~CommonPhysics(){
    delete m_VBF_world;
    
    for (size_t i=0; i < m_VBF_rbody.size(); ++i){
    delete m_VBF_rbody[i];
    delete m_shape[i];
    m_VBF_rbody[i] = nullptr;
    m_shape[i] = nullptr;
    }
    
    m_VBF_world = nullptr;
}
  
//defualt constructor
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
                        
void VBF::CommonPhysics::initPhysics()
{
    if(!m_VBF_world->is_initialized()) {
        m_VBF_world->intialize_new_world(); }
	
	if (m_VBF_world->get_debug_drawer())
		m_VBF_world->get_debug_drawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe+btIDebugDraw::DBG_DrawContactPoints);
	
}

void VBF::CommonPhysics::step_simulation(double deltaTime, double resolution){
			m_VBF_world->step_simulation(deltaTime, resolution);
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

