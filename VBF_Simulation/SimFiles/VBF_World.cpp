#include "vbf_world.hpp"

//destrutor
VBF::World::~World(){

    //free resources 
    delete m_world;
    delete m_collisionConfig;
    delete m_dispatcher;
    delete m_interface;
    delete m_solver;

    //prevent dangling pointers
    m_world =           nullptr;
    m_collisionConfig = nullptr;
    m_dispatcher =      nullptr;
    m_interface =       nullptr;
    m_solver =          nullptr;
}


VBF::World::World():
    m_world(nullptr),
    m_collisionConfig(nullptr),
    m_dispatcher(nullptr),
    m_interface(nullptr),
    m_solver(nullptr)
{
    //empty constructor body
}

VBF::World::World(btWorld* world,
             btCollConfig* collConfig,
             btDispatcher_iwb* dispatcher,
             btInterface* interface,
             btSolver* solver):
    m_world(world),
    m_collisionConfig(collConfig),
    m_dispatcher(dispatcher),
    m_interface(interface),
    m_solver(solver)
{
    //empty constructor body
}

//new world is shaped on the implicit this object
//assumption that the world is empty 
void  VBF::World::intialize_new_world(){
    
    m_collisionConfig = new btCollConfig();
    m_dispatcher      = new btDispatcher_iwb(m_collisionConfig);
    m_interface       = new btDbvtBroadphase();
    m_solver          = new btSolver;

    m_world = new btWorld(m_dispatcher, m_interface, m_solver, m_collisionConfig);
    m_world->setGravity(btVector3(0.0, -9.81, 0.0));
}

void VBF::World::set_world(btWorld* world){
    m_world = world;
}

void VBF::World::set_collisionConfig(btCollConfig* collConfig){
    m_collisionConfig = collConfig;
}

void VBF::World::set_dispatcher(btDispatcher_iwb* dispatcher){
    m_dispatcher = dispatcher;
}

void VBF::World::set_interface(btInterface* interface){
    m_interface = interface;
}

void VBF::World::set_solver(btSolver* solver){
    m_solver = solver;
}

void VBF::World::set_debug_drawer(GLDebugDrawer* debugDraw){
    m_world->setDebugDrawer(debugDraw);
}


void VBF::World::add_rigid_bodies_to_world(std::vector<btRigidBody*>& rbody){
    
    for(size_t i = 0; i<rbody.size(); ++i){
        m_world->addRigidBody(rbody[i]);
    }
}


btWorld* VBF::World::get_World() const{
    return m_world;
}
btCollConfig* VBF::World::get_collisionConfig() const{
    return m_collisionConfig;
}
btDispatcher_iwb* VBF::World::get_dispatcher() const{
    return m_dispatcher;
}
btInterface*  VBF::World::get_broadphaseInterface() const{
    return m_interface;
}
btSolver* VBF::World::get_solver() const{
    return m_solver;
}

void VBF::World::step_simulation(double deltaT1, double deltaT2) const{
    m_world->stepSimulation(deltaT1, deltaT2);
}

void VBF::World::print_updated_positions() const
{
    for (int j = 0; j < m_world->getNumCollisionObjects(); ++j){
        btCollisionObject *obj = m_world->getCollisionObjectArray()[j];
        btRigidBody* bdy = btRigidBody::upcast(obj);
        if(bdy && bdy->getMotionState()){
             btTransform trans;
             bdy->getMotionState()->getWorldTransform(trans);
             m_world->debugDrawWorld();
             std::cout << "world pos: " << trans.getOrigin().getX() <<"\nY: " << trans.getOrigin().getY() << "\nZ:" << trans.getOrigin().getZ() << "\n";
        }
    }
}

