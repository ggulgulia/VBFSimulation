#include <VBF_World.hpp>

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
    m_is_initialized = true;
    m_time = 0.0;
}

//new world is shaped on the implicit this object
//assumption that the world is empty 
void  VBF::World::initialize_new_world(){
    
    m_collisionConfig = new btCollConfig();
    m_dispatcher      = new btDispatcher_iwb(m_collisionConfig);
    m_interface       = new btDbvtBroadphase();
    m_solver          = new btSolver;
    m_world           = new btWorld(m_dispatcher, m_interface, m_solver, m_collisionConfig);
    m_world->setGravity(btVector3(0.0, -9.81, 0.0));
    m_time = 0.0;
    m_is_initialized = true;
}

bool VBF::World::is_initialized() const{
return m_is_initialized;
}

void VBF::World::set_world(btWorld* world){
    m_world = world;
}

void VBF::World::set_gravity(btVector3 gravity){
    m_world->setGravity(gravity);
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

void VBF::World::set_debug_drawer(GLDebugDrawer& debugDraw){
    m_world->setDebugDrawer(&debugDraw);
}

void VBF::World::add_rigid_bodies_to_world(btRigidBody* rbody){
    
        m_world->addRigidBody(rbody);
}

btWorld* VBF::World::get_world() const{
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

btIDebugDraw* VBF::World::get_debug_drawer() const{
    return m_world->getDebugDrawer();
}

long double VBF::World::get_curr_time() noexcept{
    return m_time;
}


void VBF::World::step_simulation(double deltaT1, double deltaT2){
    this->step_simulation(deltaT1, 1.0, deltaT2);
}

void VBF::World::step_simulation(double deltaT1) noexcept{
    this->step_simulation(deltaT1, 1.0, 0.0166667);
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

