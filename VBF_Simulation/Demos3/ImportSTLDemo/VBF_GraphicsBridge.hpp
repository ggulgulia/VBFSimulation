#ifndef VBF_GRAPHICS_BRIDGE_H
#define VBF_GRAPHICS_BRIDGE_H

#include <bullet/LinearMath/btVector3.h>
#include "CommonParameterInterface.h"
#include <string>
#include "helper.hpp"

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

namespace VBF{

    class Window{
    
        private:
            GLWindow* m_GL_window;
            World *m_VBF_world;
            int m_GL_width;
            int m_GL_height;
            std::string m_GL_title;
            WinCrInfo m_wci;
        public:
    
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

            void start_rendering() const {m_GL_window->startRendering();}
            void end_rendering()const {m_GL_window->endRendering();}
            bool requested_exit() const {return m_GL_window->requestedExit();}
            void close_window() const {m_GL_window->closeWindow();} 
            void set_window_title(std::string title);
            const int get_width() const {return m_GL_width;}
            const int get_height() const{return m_GL_height;}
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
