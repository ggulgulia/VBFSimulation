
#ifndef VBF_GRAPHICS_BRIDGE_H
#define VBF_GRAPHICS_BRIDGE_H


#include <bullet/LinearMath/btVector3.h>
#include <OpenGL/DemoApplication.h>
#include "CommonParameterInterface.h"

///The Bullet 2 GraphicsPhysicsBridge let's the graphics engine create graphics representation and synchronize


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

#endif //VBF_GRAPHICS_BRIDGE_H
