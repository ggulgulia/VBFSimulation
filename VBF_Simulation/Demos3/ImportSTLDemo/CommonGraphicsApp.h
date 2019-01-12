#ifndef COMMON_GRAPHICS_APP_H
#define COMMON_GRAPHICS_APP_H

#include <OpenGLWindow/X11OpenGLWindow.h>

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

    public:
        b3gDefaultOpenGLWindow* m_window;
	    class CommonRenderInterface*	m_renderer;
	    class CommonParameterInterface*	m_parameterInterface;
	    class Common2dCanvasInterface*	m_2dCanvasInterface;

    public:
	    CommonGraphicsApp()
		    :m_window(nullptr),
		    m_renderer(nullptr),
		    m_parameterInterface(nullptr),
		    m_2dCanvasInterface(nullptr) { }
	    
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
};

#endif //COMMON_GRAPHICS_APP_H
