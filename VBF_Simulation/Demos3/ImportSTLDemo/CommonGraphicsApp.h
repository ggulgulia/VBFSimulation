#ifndef COMMON_GRAPHICS_APP_H
#define COMMON_GRAPHICS_APP_H

#include "X11OpenGLWindow.h"

class DrawGridData
{
    public:
        int gridSize;
        float upOffset;
        int upAxis;
        float gridColor[4];

        DrawGridData()
        :gridSize(10),
        upOffset(0.001f),
        upAxis(1)
        {
            gridColor[0] = 0.6f;
            gridColor[1] = 0.6f;
            gridColor[2] = 0.6f;
            gridColor[3] = 1.f;
        }
};

class CommonGraphicsApp{

    private:
        b3gDefaultOpenGLWindow* m_window;
	    class CommonRenderInterface*	m_renderer;
	    class CommonParameterInterface*	m_parameterInterface;
	    class Common2dCanvasInterface*	m_2dCanvasInterface;

    public:
	    CommonGraphicsApp(const char* title, int width, int height)
		    :m_window(new b3gDefaultOpenGLWindow()),
		    m_renderer(nullptr),
		    m_parameterInterface(nullptr),
		    m_2dCanvasInterface(nullptr) { 
            b3gWindowConstructionInfo ci;
            ci.m_title = title;
            ci.m_width = width;
            ci.m_height = height;
            m_window->createWindow(ci); 
            m_window->setWindowTitle(title); 
            m_window->startRendering(); 
            m_window->setMouseMoveCallback(b3DefaultMouseMoveCallback);
            m_window->setMouseButtonCallback(b3DefaultMouseButtonCallback);
            m_window->setWheelCallback(b3DefaultWheelCallback);
            }
	    
        virtual ~CommonGraphicsApp(){  }
	    virtual void drawGrid(DrawGridData data=DrawGridData()) = 0;
	    virtual void setUpAxis(int axis) = 0;
	    virtual int getUpAxis() const = 0;
	    virtual void swapBuffer() = 0;
	    virtual void drawText( const char* txt, int posX, int posY) = 0;
	    virtual void drawText3D( const char* txt, float posX, float posZY, float posZ, float size)=0;
	    virtual int	registerCubeShape(float halfExtentsX,float halfExtentsY, float halfExtentsZ)=0;
	    virtual int	registerGraphicsSphereShape(float radius, bool usePointSprites=true, int largeSphereThreshold=100, int mediumSphereThreshold=10)=0;
	    virtual void registerGrid(int xres, int yres, float color0[4], float color1[4])=0;
        virtual CommonRenderInterface* get_renderer_interface(){return m_renderer;}
        virtual void set_renderer_interface(GLInstancingRenderer* rr ){
            m_renderer = rr;
        }
        
        virtual b3gDefaultOpenGLWindow* get_window() const{return m_window;}
};

#endif //COMMON_GRAPHICS_APP_H
