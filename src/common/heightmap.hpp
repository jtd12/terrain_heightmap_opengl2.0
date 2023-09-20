#ifndef DEF_HEIGHTMAP_HPP
#define DEF_HEIGHTMAP_HPP
#include"GLee/GLee.h"
#include<GL/gl.h>
#include<GL/glu.h>
#include"vector.h"
#include"texture.hpp"

class vert
{
public:
	
	vector3d translate;
		
};

class texCoord
{
public:

	float u,v;
	
};


class height
{
	public:
		
	int loadHeightmap(const char * name,int width, int height);
	void renderHeightMap();
	BYTE hHeightField[512][512];
	BYTE hHeightField2[0][512];
	void init();
	float getHeightOfTerrain(float worldX, float worldZ, BYTE heights[][512]);
	float barryCentric(vector3d p1, vector3d p2, vector3d p3, vector3d pos);
	height(int xpos,int zpos);
	~height();
	
	private:
		
	int width_,height_;
	int vertexCount;
	vert* vertices;
	texCoord* texturesCoordinates;
	textures* tex;
	GLuint texture;
	unsigned int vboVertices;
	unsigned int vboTexCoords;
	float x,z;
	float size;
	
};

#endif
