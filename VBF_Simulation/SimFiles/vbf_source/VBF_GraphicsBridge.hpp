#ifndef VBF_GRAPHICS_BRIDGE_H
#define VBF_GRAPHICS_BRIDGE_H

#include <bullet/LinearMath/btVector3.h>
#include <CommonParameterInterface.h>
#include <string>
#include <helper.hpp>


/*! @brief The purpose of this class is to get the graphics working with 
 * VBF Simulation.
 *  
 *  @details For the purpose of visual debugging and make the simulation not
 *  look dry and boring, this interface helps to put the physical object and
 *  their interactions in the simulation in an OpenGL based window. 
 *
 * @warning The interface for graphics bridge has been adopted from one of the demo examples
 * that was packed with the bullet physics library. The demo had no comments in it
 * and due to lack of proper documentation from bullet physics developer, it has 
 * not yet been ascertained how the graphics bridge works in conjunction
 * with bullet physics library.
 *
 * The helper.hpp included in this file has some methods whose exact utility could 
 * not be determined. It is essential it be included unchanged, unless of course
 * someone can understand it and code it nicer than it already is. 
 *
 * @warning The DemoApplication is an Abstract class that was shipped with
 * bullet physics in one of the demo examples for creating visualization window
 * Due to missing documentation, it's unknown why this class has been implemented.
 * Hence another class that extends and implements the DemoApplication class 
 * has been created. The empty functions implemented here have been out of compulsion
 * to make the code compile, otherwise they don't do anything useful.
 */
typedef b3gDefaultOpenGLWindow GLWindow;
typedef b3gWindowConstructionInfo WinCrInfo;

class VBF_Vis : public	DemoApplication{
    public:
    
	virtual void initPhysics()
	{
	}
	
	virtual void clientMoveAndDisplay()
	{
	}
	
	virtual		void swapBuffers()
	{
	}
	
	virtual		void	updateModifierKeys()
	{
		m_modifierKeys = 0;
		if (isAltPressed)
			m_modifierKeys |= BT_ACTIVE_ALT;

		if (isCtrlPressed)
			m_modifierKeys |= BT_ACTIVE_CTRL;

		if (isShiftPressed)
			m_modifierKeys |= BT_ACTIVE_SHIFT;

    }

};
/*! @brief VBF::Windo object creates, excatly what you thought, a graphics window
 * for VBF simulation. This interface encapsulates several of VBF and non-VBF objects.
 *
 */
namespace VBF{

    class Window{
    
        private:
            GLWindow* m_GL_window; /*!< Membe variable of type GLWindow (OpenGL object) */
            World *m_VBF_world; /*!< Pointer to VBF::World */
            int m_GL_width; /*!< Width of openGL window */
            int m_GL_height; /*!< Height of openGL window */
            std::string m_GL_title; /*!< Name of openGL window */
            WinCrInfo m_wci; /*!< OpenGL window creation information (exact purpose unknown) */
        public:
    
            /*! @brief Destructor
             *
             * @details
             *
             * @warning
             */
            ~Window(){
                delete m_GL_window;
                //we don't want to delete the resources
                //being held in m_VBF_world
                //if it still might be used after the window 
                //is closed and simulation is running
            
                //better would be to use shared pointers
                //to prevent such undefined behavior
                m_GL_window = nullptr;
            }

    
            /*! @brief User constructor
             *
             * @details The user constructor sets up the graphics for
             * VBF Simulation and names the graphics window as 'iwb TUM'.
             * Within the constructor body, the member variable m_wci 
             * is initialized with width, height and openglVersion(=2).
             *
             * @param world : pointer to VBF::World objcet.
             * @param width : Graphics window width. Default value = 1024
             * @param height : Graphics window height. Default value = 840
             * @param title : name for graphics window. Default value = 'iwb TUM'
             * @warning
             */
            Window(World *world,
                   int width=1024, 
                   int height=840, 
                   const char* title="iwb TUM"):
                m_GL_window(new GLWindow()),
                m_VBF_world(world),
                m_GL_width(width),
                m_GL_height(height),
                m_GL_title(title){
                
                    m_wci.m_width = m_GL_width;
                    m_wci.m_height = m_GL_height;
                    m_wci.m_openglVersion = 2;
            }

    
            /*! @brief Renders the graphics scene
             *
             * @details As the simulation progresses, the attributes
             * (rigid body positions, velocity, etc.) of the physics
             * world changes and it will be usefult to see them change
             * on the graphics. This is the objective of the Non-static 
             * public method
             *
             * @warning Internally it calls another method tied to private
             * attribute m_GL_Winodw, called startRendering which accepts
             * no parameters. It is not clear what is the mechanics of 
             * this method since bullet had no documentation.
             */
            void start_rendering() const {m_GL_window->startRendering();}
    
            /*! @brief Stops the rendering during simulation.
             *
             * @details It does what it says. Rendering at some point
             * may not be desired (to save memory, increase solution speed
             * etc), hence this utility can help user achieve that
             * by suspending the update of graphics.
             *
             * @warning This method needs testing. Currently, this has
             * been copied from one of the demo example code shipped with
             * bullet physics engine.
             */
            void end_rendering()const {m_GL_window->endRendering();}
    
            /*! @brief Checks if the user wished to close the window
             *
             * @details TODO
             *
             * @warning The exact utility of this method could not be determined
             * . It was shipped in one of the demo examples without any documentation
             * and hence I copied it thinking it might be useful later
             */
            bool requested_exit() const {return m_GL_window->requestedExit();}
    
            /*! @brief Closes VBF::Window
             *
             * @details Non-static public method that closes the 
             * graphics winow. This can be done during simulation 
             * without affecting the background physics that is being
             * solved for.
             *
             * @warning Internally it calls a method closeWindow encapsulated within
             * the private member variable m_GL_window. Exact mechanics
             * of this method is unknown.
             */
            void close_window() const {m_GL_window->closeWindow();} 
    
            /*! @brief Change or set the name that appears in the graphics winodw
             *
             * @details In case the user created a VBF::Winodw with a worng name 
             * this non-static public method could be used to provide a correct/new
             * name. 
             *
             * @param title : string of desired name for graphics window.
             *
             * @returns void
             * @todo Safety check if the current and new title are same 
             * or the new title is same as current title and throw a
             * warning if they are.
             */
            void set_window_title(std::string title);
    
            /*! @brief Read only access to graphics window's width
             *
             * @details Non-static public member function providing 
             * read only access to the width of the graphics window.
             * Resizing window slows down the simulation which might not
             * be desirable.
             *
             */
            const int get_width() const {return m_GL_width;}
    
            /*! @brief Read only access to graphics windows height.
             *
             * @details Similar to get_width.
             *
             */
            const int get_height() const{return m_GL_height;}
    
            /*! @brief Creates the openGL window and displays it on screen
             *
             * @details This method consists of the steps that were followed in
             * one of the demo examples to create graphics window and display 
             * them on the screen.
             *
             * @warning Removing any of the lines within the function body causes 
             * the window to not appear on the screen. The callback variables
             * in the last three liens of the function body allow the user to
             * rotate, zoom in/out using keyboard and also manipulate the
             * rigid body using mouse control. This is very dangerous for a VBF
             * simulation. 
             *
             * A workaround to prevent displacement of any object by mistake 
             * through the graphics window would be to close the windodw altogether
             * or figure out a way to disable all controls except rotate, zoomin and zoom out
             */
            void create_window() const {
                m_GL_window->createWindow(m_wci);
                m_GL_window->setWindowTitle(m_GL_title.c_str());            
                m_GL_window->setResizeCallback(MyResizeCallback);
                m_GL_window->setMouseButtonCallback(MyMouseButtonCallback);
                m_GL_window->setMouseMoveCallback(MyMouseMoveCallback);
                m_GL_window->setKeyboardCallback(MyKeyboardCallback);
            }
    };

}


#endif //VBF_GRAPHICS_BRIDGE_H
