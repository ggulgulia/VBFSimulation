#include <GL/glew.h>
#include <OpenGLWindow/X11OpenGLWindow.h>
#include <OpenGL/GLDebugDrawer.h>
#include <OpenGL/DemoApplication.h>


int sWidth(400), sHeight(400);
DemoApplication* gApp = 0;
bool isShiftPressed = false;
bool isCtrlPressed = false;
bool isAltPressed = false;

void MyKeyboardCallback(int orgKeycode, int state)
{
	int keycode = orgKeycode;

	if (gApp)
	{

		switch (orgKeycode)
		{
			case 	B3G_SHIFT:
			{
				isShiftPressed = (state==1);
				break;
			}
			case B3G_ALT:
			{
				isAltPressed = (state==1);
				break;
			}
			case B3G_CONTROL:
			{
				isCtrlPressed = (state==1);
				break;
			}
			default:
			{
			}
		};

		if (state)
		{
			gApp->keyboardCallback(keycode,0,0);
		} else
		{
			gApp->keyboardUpCallback(keycode,0,0);
		}
	}
}
void MyMouseMoveCallback( float x, float y)
{
	if (gApp)
	{
		//printf("mouseMotionFunc %f,%f\n",x,y);
		gApp->mouseMotionFunc(x,y);
	}
}

void MyMouseButtonCallback(int button, int state, float x, float y)
{
	if (gApp)
	{
		//printf("mouseFunc %d,%d, %f,%f\n",button,state,x,y);
		gApp->mouseFunc(button,1-state,x,y);
	}
}

void MyResizeCallback(float width, float height)
{
	sWidth = width;
	sHeight = height;
	if (gApp)
	{
		gApp->reshape(width,height);
	}
}

