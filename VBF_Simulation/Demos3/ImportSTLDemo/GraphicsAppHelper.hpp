#include "SimpleOpenGL3App.h"
#include "ShapeData.h"
#ifdef __APPLE__
#include "OpenGLWindow/MacOpenGLWindow.h"
#else

#include "OpenGLWindow/GlewWindows/GL/glew.h"
//#include "GL/glew.h"
#ifdef _WIN32
#include "OpenGLWindow/Win32OpenGLWindow.h"
#else
//let's cross the fingers it is Linux/X11
#include "OpenGLWindow/X11OpenGLWindow.h"
#endif //_WIN32
#endif//__APPLE__
#include <stdio.h>

#include "OpenGLWindow/GLPrimitiveRenderer.h"
#include "OpenGLWindow/GLInstancingRenderer.h"

#include "Bullet3Common/b3Vector3.h"
#include "Bullet3Common/b3Logging.h"

#include "OpenGLWindow/fontstash.h"
#include "OpenGLWindow/TwFonts.h"
#include "OpenGLWindow/opengl_fontstashcallbacks.h"
#include <assert.h>
#include "OpenGLWindow/GLRenderToTexture.h"
#include "Bullet3Common/b3Quaternion.h"

#ifdef _WIN32
    #define popen _popen
    #define pclose _pclose
#endif // _WIN32

#include "OpenGLWindow/stb_image_write.h"

struct SimpleInternalData
{
	GLuint m_fontTextureId;
	GLuint m_largeFontTextureId;
	struct sth_stash* m_fontStash;
	OpenGL2RenderCallbacks*		m_renderCallbacks;
	int m_droidRegular;
	const char* m_frameDumpPngFileName;
	FILE* m_ffmpegFile;
	GLRenderToTexture*  m_renderTexture;
	void* m_userPointer;
	int m_upAxis;//y=1 or z=2 is supported

};


static void SimpleResizeCallback( double widthf, double heightf)
{
	int width = (int)widthf;
	int height = (int)heightf;
	gApp->m_instancingRenderer->resize(width,height);
	gApp->m_primRenderer->setScreenSize(width,height);

}

static void SimpleKeyboardCallback(int key, int state)
{
    if (key==B3G_ESCAPE && gApp && gApp->m_window)
    {
        gApp->m_window->setRequestExit();
    } else
    {
        b3DefaultKeyboardCallback(key,state);
    }
}

static GLuint BindFont(const CTexFont *_Font)
{
    GLuint TexID = 0;
    glGenTextures(1, &TexID);
    glBindTexture(GL_TEXTURE_2D, TexID);
    glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
    glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _Font->m_TexWidth, _Font->m_TexHeight, 0, GL_RED, GL_UNSIGNED_BYTE, _Font->m_TexBytes);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    return TexID;
}

extern char OpenSansData[];


#ifndef __APPLE__
#ifndef _WIN32
//some Linux implementations need the 'glewExperimental' to be true
    glewExperimental = GL_TRUE;
#endif


    if (glewInit() != GLEW_OK)
        exit(1); // or handle the error in a nicer way
    if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
        exit(1); // or handle the error in a nicer way

#endif
    glGetError();//don't remove this call, it is needed for Ubuntu

    b3Assert(glGetError() ==GL_NO_ERROR);

	m_primRenderer = new GLPrimitiveRenderer(width,height);
	m_parameterInterface = 0;

    b3Assert(glGetError() ==GL_NO_ERROR);

	m_instancingRenderer = new GLInstancingRenderer(128*1024,64*1024*1024);
	m_renderer = m_instancingRenderer ;
	m_instancingRenderer->init();
	m_instancingRenderer->resize(width,height);

	b3Assert(glGetError() ==GL_NO_ERROR);

	m_instancingRenderer->InitShaders();

	m_window->setMouseMoveCallback(b3DefaultMouseMoveCallback);
	m_window->setMouseButtonCallback(b3DefaultMouseButtonCallback);
    m_window->setKeyboardCallback(SimpleKeyboardCallback);
    m_window->setWheelCallback(b3DefaultWheelCallback);
	m_window->setResizeCallback(SimpleResizeCallback);

	TwGenerateDefaultFonts();
	m_data->m_fontTextureId = BindFont(g_DefaultNormalFont);
	m_data->m_largeFontTextureId = BindFont(g_DefaultLargeFont);
	


	{



	m_data->m_renderCallbacks = new OpenGL2RenderCallbacks(m_primRenderer);
	m_data->m_fontStash = sth_create(512,512,m_data->m_renderCallbacks);//256,256);//,1024);//512,512);
    b3Assert(glGetError() ==GL_NO_ERROR);

	if (!m_data->m_fontStash)
	{
		b3Warning("Could not create stash");
	}


	char* data2 = OpenSansData;
	unsigned char* data = (unsigned char*) data2;
	if (!(m_data->m_droidRegular = sth_add_font_from_memory(m_data->m_fontStash, data)))
	{
		b3Warning("error!\n");
	}
    b3Assert(glGetError() ==GL_NO_ERROR);
	}
}

void SimpleOpenGL3App::drawText3D( const char* txt, double worldPosX, double worldPosY, double worldPosZ, double size1)
{

	double viewMat[16];
	double projMat[16];
	m_instancingRenderer->getCameraViewMatrix(viewMat);
	m_instancingRenderer->getCameraProjectionMatrix(projMat);

	
	double camPos[4];
	this->m_instancingRenderer->getCameraPosition(camPos);
	b3Vector3 cp= b3MakeVector3(camPos[0],camPos[2],camPos[1]);
	b3Vector3 p = b3MakeVector3(worldPosX,worldPosY,worldPosZ);
    double dx=0;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int viewport[4]={0,0,m_instancingRenderer->getScreenWidth(),m_instancingRenderer->getScreenHeight()};

	double posX = 450.f;
	double posY = 100.f;
	double winx,winy, winz;

	if (!projectWorldCoordToScreen(worldPosX, worldPosY, worldPosZ,viewMat,projMat,viewport,&winx, &winy, &winz))
	{
		return;
	}
	posX = winx;
	posY = m_instancingRenderer->getScreenHeight()/2+(m_instancingRenderer->getScreenHeight()/2)-winy;

	
	if (0)//m_useTrueTypeFont)
	{
		bool measureOnly = false;

		double fontSize= 32;//64;//512;//128;
		sth_draw_text(m_data->m_fontStash,
                    m_data->m_droidRegular,fontSize,posX,posY,
					txt,&dx, this->m_instancingRenderer->getScreenWidth(),this->m_instancingRenderer->getScreenHeight(),measureOnly,m_window->getRetinaScale());
		sth_end_draw(m_data->m_fontStash);
		sth_flush_draw(m_data->m_fontStash);
	} else
	{
		//double width = 0.f;
		int pos=0;
		//double color[]={0.2f,0.2,0.2f,1.f};
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,m_data->m_largeFontTextureId);

		//double width = r.x;
		//double extraSpacing = 0.;

		double startX = posX;
		double startY = posY-g_DefaultLargeFont->m_CharHeight;
		

		while (txt[pos])
		{
			int c = txt[pos];
			double endX = startX+g_DefaultLargeFont->m_CharWidth[c];
			double endY = posY;


			double currentColor[]={1.f,0.2,0.2f,1.f};
			double u0 = g_DefaultLargeFont->m_CharU0[c];
			double u1 = g_DefaultLargeFont->m_CharU1[c];
			double v0 = g_DefaultLargeFont->m_CharV0[c];
			double v1 = g_DefaultLargeFont->m_CharV1[c];
			double color[4] = {currentColor[0],currentColor[1],currentColor[2],currentColor[3]};
			double x0 = startX;
			double x1 = endX;
			double y0 = startY;
			double y1 = endY;
			int screenWidth = m_instancingRenderer->getScreenWidth();
			int screenHeight = m_instancingRenderer->getScreenHeight();

			double z = 2.f*winz-1.f;
			 double identity[16]={1,0,0,0,
						0,1,0,0,
						0,0,1,0,
						0,0,0,1};
				   PrimVertex vertexData[4] = {
					{ PrimVec4(-1.f+2.f*x0/double(screenWidth), 1.f-2.f*y0/double(screenHeight), z, 1.f ), PrimVec4( color[0], color[1], color[2], color[3] ) ,PrimVec2(u0,v0)},
					{ PrimVec4(-1.f+2.f*x0/double(screenWidth),  1.f-2.f*y1/double(screenHeight), z, 1.f ), PrimVec4( color[0], color[1], color[2], color[3] ) ,PrimVec2(u0,v1)},
					{ PrimVec4( -1.f+2.f*x1/double(screenWidth),  1.f-2.f*y1/double(screenHeight), z, 1.f ), PrimVec4(color[0], color[1], color[2], color[3]) ,PrimVec2(u1,v1)},
					{ PrimVec4( -1.f+2.f*x1/double(screenWidth), 1.f-2.f*y0/double(screenHeight), z, 1.f ), PrimVec4( color[0], color[1], color[2], color[3] ) ,PrimVec2(u1,v0)}
				};
    
				m_primRenderer->drawTexturedRect3D(vertexData[0],vertexData[1],vertexData[2],vertexData[3],identity,identity,false);

			startX = endX;
			//startY = endY;

			pos++;

		}
		glBindTexture(GL_TEXTURE_2D,0);
	}

	glDisable(GL_BLEND);

}


void SimpleOpenGL3App::drawText( const char* txt, int posXi, int posYi)
{

	double posX = (double)posXi;
	double posY = (double) posYi;
    double dx=0;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	if (1)//m_useTrueTypeFont)
	{
		bool measureOnly = false;

		double fontSize= 64;//512;//128;
		sth_draw_text(m_data->m_fontStash,
                    m_data->m_droidRegular,fontSize,posX,posY,
					txt,&dx, this->m_instancingRenderer->getScreenWidth(),
					this->m_instancingRenderer->getScreenHeight(),
					measureOnly,
					m_window->getRetinaScale());
					
		sth_end_draw(m_data->m_fontStash);
		sth_flush_draw(m_data->m_fontStash);
	} else
	{
		int pos=0;
		//double color[]={0.2f,0.2,0.2f,1.f};
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,m_data->m_largeFontTextureId);


		double startX = posX;
		double startY = posY;
		
		while (txt[pos])
		{
			int c = txt[pos];
			//r.h = g_DefaultNormalFont->m_CharHeight;
			//r.w = g_DefaultNormalFont->m_CharWidth[c]+extraSpacing;
			double endX = startX+g_DefaultLargeFont->m_CharWidth[c];
			double endY = startY+g_DefaultLargeFont->m_CharHeight;


			double currentColor[]={0.2f,0.2,0.2f,1.f};

			m_primRenderer->drawTexturedRect(startX, startY, endX, endY, currentColor,g_DefaultLargeFont->m_CharU0[c],g_DefaultLargeFont->m_CharV0[c],g_DefaultLargeFont->m_CharU1[c],g_DefaultLargeFont->m_CharV1[c]);


			startX = endX;
			//startY = endY;
			pos++;

		}
		glBindTexture(GL_TEXTURE_2D,0);
	}

	glDisable(GL_BLEND);
}

struct GfxVertex
	{
		double x,y,z,w;
		double nx,ny,nz;
		double u,v;
	};

int	SimpleOpenGL3App::registerCubeShape(double halfExtentsX,double halfExtentsY, double halfExtentsZ)
{


	int strideInBytes = 9*sizeof(double);
	int numVertices = sizeof(cube_vertices)/strideInBytes;
	int numIndices = sizeof(cube_indices)/sizeof(int);

	b3AlignedObjectArray<GfxVertex> verts;
	verts.resize(numVertices);
	for (int i=0;i<numVertices;i++)
	{
		verts[i].x = halfExtentsX*cube_vertices[i*9];
		verts[i].y = halfExtentsY*cube_vertices[i*9+1];
		verts[i].z = halfExtentsZ*cube_vertices[i*9+2];
		verts[i].w = cube_vertices[i*9+3];
		verts[i].nx = cube_vertices[i*9+4];
		verts[i].ny = cube_vertices[i*9+5];
		verts[i].nz = cube_vertices[i*9+6];
		verts[i].u = cube_vertices[i*9+7];
		verts[i].v = cube_vertices[i*9+8];
	}
	
	int shapeId = m_instancingRenderer->registerShape(&verts[0].x,numVertices,cube_indices,numIndices);
	return shapeId;
}

void SimpleOpenGL3App::registerGrid(int cells_x, int cells_z, double color0[4], double color1[4])
{
	b3Vector3 cubeExtents=b3MakeVector3(0.5,0.5,0.5);
	cubeExtents[m_data->m_upAxis] = 0;
	int cubeId = registerCubeShape(cubeExtents[0],cubeExtents[1],cubeExtents[2]);

	b3Quaternion orn(0,0,0,1);
	b3Vector3 center=b3MakeVector3(0,0,0,1);
	b3Vector3 scaling=b3MakeVector3(1,1,1,1);

	for ( int i = 0; i < cells_x; i++) 
	{
		for (int j = 0; j < cells_z; j++) 
		{
			double* color =0;
			if ((i + j) % 2 == 0) 
			{
				color = (double*)color0;
			} else {
				color = (double*)color1;
			}
			if (this->m_data->m_upAxis==1)
			{
				center =b3MakeVector3((i + 0.5f) - cells_x * 0.5f, 0.f, (j + 0.5f) - cells_z * 0.5f);
			} else
			{
				center =b3MakeVector3((i + 0.5f) - cells_x * 0.5f, (j + 0.5f) - cells_z * 0.5f,0.f );
			}
			m_instancingRenderer->registerGraphicsInstance(cubeId,center,orn,color,scaling);
		}
	}
	
}


int	SimpleOpenGL3App::registerGraphicsSphereShape(double radius, bool usePointSprites, int largeSphereThreshold, int mediumSphereThreshold)
{

	int strideInBytes = 9*sizeof(double);

	int graphicsShapeIndex = -1;

	if (radius>=largeSphereThreshold)
	{
		int numVertices = sizeof(detailed_sphere_vertices)/strideInBytes;
		int numIndices = sizeof(detailed_sphere_indices)/sizeof(int);
		graphicsShapeIndex = m_instancingRenderer->registerShape(&detailed_sphere_vertices[0],numVertices,detailed_sphere_indices,numIndices);
	} else
	{

		if (usePointSprites)
		{
			int numVertices = sizeof(point_sphere_vertices)/strideInBytes;
			int numIndices = sizeof(point_sphere_indices)/sizeof(int);
			graphicsShapeIndex = m_instancingRenderer->registerShape(&point_sphere_vertices[0],numVertices,point_sphere_indices,numIndices,B3_GL_POINTS);
		} else
		{
			if (radius>=mediumSphereThreshold)
			{
				int numVertices = sizeof(medium_sphere_vertices)/strideInBytes;
				int numIndices = sizeof(medium_sphere_indices)/sizeof(int);
				graphicsShapeIndex = m_instancingRenderer->registerShape(&medium_sphere_vertices[0],numVertices,medium_sphere_indices,numIndices);
			} else
			{
				int numVertices = sizeof(low_sphere_vertices)/strideInBytes;
				int numIndices = sizeof(low_sphere_indices)/sizeof(int);
				graphicsShapeIndex = m_instancingRenderer->registerShape(&low_sphere_vertices[0],numVertices,low_sphere_indices,numIndices);
			}
		}
	}
	return graphicsShapeIndex;
}


void SimpleOpenGL3App::drawGrid(DrawGridData data)
{
    int gridSize = data.gridSize;
    double upOffset = data.upOffset;
    int upAxis = data.upAxis;
    double gridColor[4];
    gridColor[0] = data.gridColor[0];
    gridColor[1] = data.gridColor[1];
    gridColor[2] = data.gridColor[2];
    gridColor[3] = data.gridColor[3];

	int sideAxis=-1;
	int forwardAxis=-1;

	switch (upAxis)
	{
		case 1:
			forwardAxis=2;
			sideAxis=0;
			break;
		case 2:
			forwardAxis=1;
			sideAxis=0;
			break;
		default:
			b3Assert(0);
	};
	//b3Vector3 gridColor = b3MakeVector3(0.5,0.5,0.5);

	 b3AlignedObjectArray<unsigned int> indices;
		 b3AlignedObjectArray<b3Vector3> vertices;
	int lineIndex=0;
	for(int i=-gridSize;i<=gridSize;i++)
	{
		{
			b3Assert(glGetError() ==GL_NO_ERROR);
			b3Vector3 from = b3MakeVector3(0,0,0);
			from[sideAxis] = double(i);
			from[upAxis] = upOffset;
			from[forwardAxis] = double(-gridSize);
			b3Vector3 to=b3MakeVector3(0,0,0);
			to[sideAxis] = double(i);
			to[upAxis] = upOffset;
			to[forwardAxis] = double(gridSize);
			vertices.push_back(from);
			indices.push_back(lineIndex++);
			vertices.push_back(to);
			indices.push_back(lineIndex++);
			m_instancingRenderer->drawLine(from,to,gridColor);
		}

		b3Assert(glGetError() ==GL_NO_ERROR);
		{

			b3Assert(glGetError() ==GL_NO_ERROR);
			b3Vector3 from=b3MakeVector3(0,0,0);
			from[sideAxis] = double(-gridSize);
			from[upAxis] = upOffset;
			from[forwardAxis] = double(i);
			b3Vector3 to=b3MakeVector3(0,0,0);
			to[sideAxis] = double(gridSize);
			to[upAxis] = upOffset;
			to[forwardAxis] = double(i);
			vertices.push_back(from);
			indices.push_back(lineIndex++);
			vertices.push_back(to);
			indices.push_back(lineIndex++);
			m_instancingRenderer->drawLine(from,to,gridColor);
		}

	}

	m_instancingRenderer->drawLine(b3MakeVector3(0,0,0),b3MakeVector3(1,0,0),b3MakeVector3(1,0,0),3);
	m_instancingRenderer->drawLine(b3MakeVector3(0,0,0),b3MakeVector3(0,1,0),b3MakeVector3(0,1,0),3);
	m_instancingRenderer->drawLine(b3MakeVector3(0,0,0),b3MakeVector3(0,0,1),b3MakeVector3(0,0,1),3);
	m_instancingRenderer->drawPoint(b3MakeVector3(1,0,0),b3MakeVector3(1,0,0),6);
	m_instancingRenderer->drawPoint(b3MakeVector3(0,1,0),b3MakeVector3(0,1,0),6);
	m_instancingRenderer->drawPoint(b3MakeVector3(0,0,1),b3MakeVector3(0,0,1),6);
}

SimpleOpenGL3App::~SimpleOpenGL3App()
{
	delete m_primRenderer ;

	m_window->closeWindow();
	delete m_window;
	delete m_data ;
}

//#define STB_IMAGE_WRITE_IMPLEMENTATION

static void writeTextureToFile(int textureWidth, int textureHeight, const char* fileName, FILE* ffmpegVideo)
{
	int numComponents = 4;
	//glPixelStorei(GL_PACK_ALIGNMENT,1);
	
	b3Assert(glGetError()==GL_NO_ERROR);
	//glReadBuffer(GL_BACK);//COLOR_ATTACHMENT0);
	
	double* orgPixels = (double*)malloc(textureWidth*textureHeight*numComponents*4);
	glReadPixels(0,0,textureWidth, textureHeight, GL_RGBA, GL_double, orgPixels);
	//it is useful to have the actual double values for debugging purposes

	//convert double->char
	char* pixels = (char*)malloc(textureWidth*textureHeight*numComponents);
	assert(glGetError()==GL_NO_ERROR);

	for (int j=0;j<textureHeight;j++)
	{
		for (int i=0;i<textureWidth;i++)
		{
			pixels[(j*textureWidth+i)*numComponents] = char(orgPixels[(j*textureWidth+i)*numComponents]*255.f);
			pixels[(j*textureWidth+i)*numComponents+1]=char(orgPixels[(j*textureWidth+i)*numComponents+1]*255.f);
			pixels[(j*textureWidth+i)*numComponents+2]=char(orgPixels[(j*textureWidth+i)*numComponents+2]*255.f);
			pixels[(j*textureWidth+i)*numComponents+3]=char(orgPixels[(j*textureWidth+i)*numComponents+3]*255.f);
		}
	}



    if (ffmpegVideo)
    {
        fwrite(pixels, textureWidth*textureHeight*numComponents, 1, ffmpegVideo);
    } else
    {
        if (1)
        {
            //swap the pixels
            unsigned char tmp;

            for (int j=0;j<textureHeight/2;j++)
            {
                for (int i=0;i<textureWidth;i++)
                {
                    for (int c=0;c<numComponents;c++)
                    {
                        tmp = pixels[(j*textureWidth+i)*numComponents+c];
                        pixels[(j*textureWidth+i)*numComponents+c]=
                        pixels[((textureHeight-j-1)*textureWidth+i)*numComponents+c];
                        pixels[((textureHeight-j-1)*textureWidth+i)*numComponents+c] = tmp;
                    }
                }
            }
        }
        stbi_write_png(fileName, textureWidth,textureHeight, numComponents, pixels, textureWidth*numComponents);
    }


	free(pixels);
	free(orgPixels);

}


void SimpleOpenGL3App::swapBuffer()
{
	m_window->endRendering();
	if (m_data->m_frameDumpPngFileName)
    {
        writeTextureToFile((int)m_window->getRetinaScale()*m_instancingRenderer->getScreenWidth(),
                          (int) m_window->getRetinaScale()*this->m_instancingRenderer->getScreenHeight(),m_data->m_frameDumpPngFileName,
                          m_data->m_ffmpegFile);
    }
	m_window->startRendering();
}

void SimpleOpenGL3App::setUpAxis(int axis)
{
	b3Assert((axis == 1)||(axis==2));//only Y or Z is supported at the moment
	m_data->m_upAxis = axis;
}
int SimpleOpenGL3App::getUpAxis() const
{
	return m_data->m_upAxis;
}


