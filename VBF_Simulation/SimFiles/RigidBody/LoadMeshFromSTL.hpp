
#ifndef LOAD_MESH_FROM_STL_H
#define LOAD_MESH_FROM_STL_H

#include <OpenGLWindow/GLInstanceGraphicsShape.h>
#include <cstdio> //fopen
#include <bullet/Bullet3Common/b3AlignedObjectArray.h>
#include <string>
#include <fstream>
#include <bullet/BulletCollision/Gimpact/btGImpactShape.h>
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

//internal routine to convert tri mesh data to a sensible bullet rigid body
typedef GLInstanceGraphicsShape VBF_MeshShape;
inline btGImpactMeshShape* triMeshToCollisionShape(const VBF_MeshShape* mesh){

    btTriangleMesh* trimeshData = new btTriangleMesh();
	double xV0{0.0}, yV0{0.0}, zV0{0.0};
    double xV1{0.0}, yV1{0.0}, zV1{0.0};
    double xV2{0.0}, yV2{0.0}, zV2{0.0};
    b3AlignedObjectArray<int>* meshIndices = mesh->m_indices;
    b3AlignedObjectArray<GLInstanceVertex>* meshVertices = mesh->m_vertices;

    //set the origin of the body as the 
    //coordinate of the first element
    int numVertices = mesh->m_numvertices;
	for (int ind0 = meshIndices->at(0), ind1 = meshIndices->at(1), ind2=meshIndices->at(2); ind2<numVertices; ind0+=3, ind1+=3, ind2+=3){

        xV0 = meshVertices->at(ind0).xyzw[0];
        yV0 = meshVertices->at(ind0).xyzw[1];
        zV0 = meshVertices->at(ind0).xyzw[2];

        xV1 = meshVertices->at(ind1).xyzw[0];
        yV1 = meshVertices->at(ind1).xyzw[1];
        zV1 = meshVertices->at(ind1).xyzw[2];

        xV2 = meshVertices->at(ind2).xyzw[0];
        yV2 = meshVertices->at(ind2).xyzw[1];
        zV2 = meshVertices->at(ind2).xyzw[2];

        btVector3 v0(xV0, yV0, zV0);
        btVector3 v1(xV1, yV1, zV1);
        btVector3 v2(xV2, yV2, zV2);
		
		trimeshData->addTriangle(v0,v1,v2);
	}
    return new btGImpactMeshShape(trimeshData);
}

class MySTLTriangle
{
    public:
	    float normal[3];
	    float vertex0[3];
	    float vertex1[3];
	    float vertex2[3];
};

static GLInstanceGraphicsShape* LoadMeshFromSTL(const std::string& relativeFileName, double scaling_factor){
	GLInstanceGraphicsShape* shape;
	FILE* file = fopen(relativeFileName.c_str(),"rb");
	int size=0;
    if(!file)
        throw "Mesh file not found, please check the file path";

	if (fseek(file, 0, SEEK_END) || (size = ftell(file)) == EOF || fseek(file, 0, SEEK_SET)){
        throw "cannot access file to determine it's size. Please check user permissions";
	}
    else{
		
        if (size){
		        	printf("Open STL file of %d bytes\n",size);
		        	char* memoryBuffer = new char[size+1];
		        	int actualBytesRead = fread(memoryBuffer,1,size,file);
		        	if (actualBytesRead!=size){
                        throw "Error reading from file";
		        	} 
                    else{
				    int numTriangles = *(int*)&memoryBuffer[80];
				
			    	if (numTriangles){
			    		//perform a sanity check instead of crashing on invalid triangles/STL files
			    		int expectedBinaryFileSize = numTriangles* 50 + 84; //what is 50 + 84 ?
			    		if (expectedBinaryFileSize != size){
			    			return 0;
			    		}

			    		shape = new GLInstanceGraphicsShape;
			    		shape->m_scaling[0] = scaling_factor ;
			    		shape->m_scaling[1] = scaling_factor ;
			    		shape->m_scaling[2] = scaling_factor ;
			    		shape->m_scaling[3] = scaling_factor ;
			    		int index = 0;
			    		shape->m_indices = new b3AlignedObjectArray<int>();
			    		shape->m_vertices = new b3AlignedObjectArray<GLInstanceVertex>();

			    		for (int tri_num=0; tri_num<numTriangles; tri_num++){
			    			    char* curPtr = &memoryBuffer[84+tri_num*50];
			    			    MySTLTriangle* tri = (MySTLTriangle*) curPtr;
			    			    
			    			    GLInstanceVertex temp_vert0,temp_vert1,temp_vert2;

                                //initialzie the coordinates of the vertices
                                //by setting every data to zero
                                for (int vv = 0; vv < 3; ++vv) {
                                   temp_vert0.xyzw[vv] = 0.0; temp_vert1.xyzw[vv] = 0.0; temp_vert2.xyzw[vv] = 0.0; 
                                   temp_vert0.normal[vv] = 0.0; temp_vert1.normal[vv] = 0.0; temp_vert2.normal[vv] = 0.0;
                                }
                                temp_vert0.xyzw[3] = 0.0; temp_vert1.xyzw[3] = 0.0; temp_vert2.xyzw[3] = 0.0; 
			    			    temp_vert0.uv[0] = temp_vert1.uv[0] = temp_vert2.uv[0] = 0.;
			    			    temp_vert0.uv[1] = temp_vert1.uv[1] = temp_vert2.uv[1] = 0.; 

			    			    if (tri_num == numTriangles-2){
			    			    	printf("!\n");
			    			    }
                                
			    			    for (int v=0;v<3;v++){
			    			    	temp_vert0.xyzw[v] = tri->vertex0[v]*scaling_factor;
			    			    	temp_vert1.xyzw[v] = tri->vertex1[v]*scaling_factor;
			    			    	temp_vert2.xyzw[v] = tri->vertex2[v]*scaling_factor;
			    			    	temp_vert0.normal[v] = temp_vert1.normal[v] = temp_vert2.normal[v] = tri->normal[v];
			    			    }

			    			    shape->m_vertices->push_back(temp_vert0);
			    			    shape->m_vertices->push_back(temp_vert1);
			    			    shape->m_vertices->push_back(temp_vert2);
			    			    
			    			    shape->m_indices->push_back(index++);
			    			    shape->m_indices->push_back(index++);
			    			    shape->m_indices->push_back(index++);
			    			
			    		}
			    	}
			}
			
			delete[] memoryBuffer;
		}
	}
	fclose(file);

    if(shape){

	    shape->m_numIndices = shape->m_indices->size();
	    shape->m_numvertices = shape->m_vertices->size();
	    return shape;
    }

    else
        throw("failed to create a bullet collision shape from the mesh\n");
}

#endif //LOAD_MESH_FROM_STL_H
