
#ifndef LOAD_MESH_FROM_STL_H
#define LOAD_MESH_FROM_STL_H

/*! This is a helper file that assists in opening and importing the triangular mesh data 
 * from a binary encoded stl file and parse it in a format suitable to be converted into
 * a bullet rigid body. This file is used by the classes VBF::StaticMeshBody, VBF::KinematicMeshBody
 * and VBF::DynamicMeshBody during the constructor call of the respective class
 */


//internal routine to convert tri mesh data to a sensible bullet rigid body

/*! Removing the ugly type name
 */
typedef GLInstanceGraphicsShape VBF_MeshShape;

/*! Inlined function (to ensure the method has only a single definition)
 * This function creates a collision shape of type btGImpactMeshShape from the 
 * mesh data. The return type of this function is essential for the creation
 * of a VBF::RigidBody which needs a collision shape in its constructor call.
 *
 * Note: This function is called by the method LoadMeshFromSTL
 */
inline btGImpactMeshShape* triMeshToCollisionShape(const VBF_MeshShape* mesh){

    /*! an empty trimeshData is created on the heap. This triMeshData is not used
     * further after the method goes out of scope but it still makes sense to
     * allocate a heap storage since if the stl file is very large,
     * it will suck up the entire stack space and cause a bad memory error
     */
    btTriangleMesh* trimeshData = new btTriangleMesh();

    /*! This is C++11 style initialization. If the initializer list is empty
     * the default constructor for the template type T is called. For the 
     * fundemental data types, the default constructor initializes the variable
     * to zero
     */
	double xV0{}, yV0{}, zV0{};
    double xV1{}, yV1{}, zV1{};
    double xV2{}, yV2{}, zV2{};

    b3AlignedObjectArray<int>* meshIndices = mesh->m_indices;
    b3AlignedObjectArray<GLInstanceVertex>* meshVertices = mesh->m_vertices;

    //set the origin of the body as the 
    //coordinate of the first element
    
    /*! This loop fishes out the mesh vertex data and adds it to the data structre
     * triMeshData. The basic steps used here are:
     *  1. retrieve the x,y,z coordinates of first vertex of triangle.
     *  2. repeat step 1 for second and third vertices of triangle.
     *  3. create a vetor (btVector3) of each of the vertices.
     *  4. add it to the triMeshData object by a call to  (bullet physics)
     *     public member function addTriangle() passing the three vertices 
     *     created in step3.
     */
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

    /*! create a collision shape on the heap and 
     * return the pointer to this storage location
     */
    return new btGImpactMeshShape(trimeshData);
    //return new btGImpactConvexDecompositionShape(trimeshData, btVector3(1.f,1.f,1.f),btScalar(0.01));
}

class MySTLTriangle
{
    public:
	    float normal[3];
	    float vertex0[3];
	    float vertex1[3];
	    float vertex2[3];
};

inline GLInstanceGraphicsShape* LoadMeshFromSTL(const std::string& relativeFileName, double scaling_factor){
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
