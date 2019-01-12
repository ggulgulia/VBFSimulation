#ifndef SIMPLE_OPENGL3_APP_H
#define SIMPLE_OPENGL3_APP_H

#include <OpenGLWindow/GLInstancingRenderer.h>
#include <OpenGLWindow/GLPrimitiveRenderer.h>
#include <OpenGLWindow/b3gWindowInterface.h>
#include "CommonGraphicsApp.h"
#include "X11OpenGLWindow.h"


class GraphicsApp : public CommonGraphicsApp{

    public:
        class SimpleInternalData* m_data;
        class GLPrimitiveRenderer*	m_primRenderer;
        class GLInstancingRenderer* m_instancingRenderer;

    public:
        GraphicsApp(const char* title, int width,int height);
        virtual ~GraphicsApp();
        virtual int	registerCubeShape(float halfExtentsX=1.f,float halfExtentsY=1.f, float halfExtentsZ = 1.f);
        virtual int	registerGraphicsSphereShape(float radius, bool usePointSprites=true, int largeSphereThreshold=100, int mediumSphereThreshold=10);
        virtual void registerGrid(int xres, int yres, float color0[4], float color1[4]);
        void dumpNextFrameToPng(const char* pngFilename);
        void dumpFramesToVideo(const char* mp4Filename);
        void drawGrid(DrawGridData data=DrawGridData());
        virtual void setUpAxis(int axis);
        virtual int getUpAxis() const;
        virtual void swapBuffer();
        virtual void drawText( const char* txt, int posX, int posY);
        virtual void drawText3D( const char* txt, float posX, float posZY, float posZ, float size);
        struct sth_stash* getFontStash();
};
#endif //SIMPLE_OPENGL3_APP_H