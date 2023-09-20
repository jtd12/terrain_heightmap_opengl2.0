#include"heightmap.hpp"


height::height(int xpos,int zpos)
{
size=10;
x=xpos*size;
z=zpos*size;
}


height::~height()
{
	
delete [] vertices;
vertices=NULL;
delete [] texturesCoordinates;
texturesCoordinates=NULL;
}


void height::init()
{
glGenBuffersARB(1,&vboVertices);
glBindBufferARB(GL_ARRAY_BUFFER_ARB,vboVertices);
glBufferDataARB(GL_ARRAY_BUFFER_ARB,vertexCount*3*sizeof(float),vertices,GL_STATIC_DRAW_ARB);
glGenBuffersARB(1,&vboTexCoords);
glBindBufferARB(GL_ARRAY_BUFFER_ARB,vboTexCoords);
glBufferDataARB(GL_ARRAY_BUFFER_ARB,vertexCount*2*sizeof(float),texturesCoordinates,GL_STATIC_DRAW_ARB);
}



int height::loadHeightmap(const char * name,int width, int height)
{
	tex=new textures();
//	tex=new textures();
	width_=width;
	height_=height;
	FILE *fp;
	fp=fopen(name,"rb");
	fread(hHeightField,1,width*height,fp);
	fclose(fp);
	vertexCount=(int)( height_*width_*6)/(1*1);
	vertices=new vert[vertexCount];
	texturesCoordinates=new texCoord[vertexCount];
	
	int numIndex=0;

	
	float flx,flz;
	
	for(int mapX=0;mapX<width_;mapX++)
	{
		for(int mapZ=0;mapZ<height_;mapZ++)
		{
			
			for(int tri=0;tri<6;tri++)
			{
				flx=(float)mapX+((tri==1 || tri==2 || tri==5)?1: 0);
				flz=(float)mapZ+((tri==2 || tri==4 || tri==5)?1: 0);
				
				vertices[numIndex].translate.x=flx*size;
				vertices[numIndex].translate.y=hHeightField[(int)flx][(int)flz]*size/2;
				vertices[numIndex].translate.z=flz*size;
				
				texturesCoordinates[numIndex].u=flx/512;
				texturesCoordinates[numIndex].v=flz/512;
				
				numIndex++;
				
			}
		//	printf("%d, %d, %d\n", mapX, mapZ, hHeightField[mapX][mapZ]);
		}
	}
	
		texture=tex->loadBMP_custom("data/Grass_01_c.bmp");
	//	unsigned int pixel=((unsigned int*) pixels)[i*tex->images.dataPos/4 +j];
		init();
		return true;

	
	
}

void  height::renderHeightMap()
{
	

	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboTexCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboVertices);
	glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);
	glTranslated(x,0,z);
	//glScalef(10, 10, 10);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	/*
	
	for (int mapX = 0; mapX < width_; mapX++){
		for (int mapZ = 0; mapZ < height_; mapZ++){
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f((float)mapX / width_, (float)mapZ / height_);
				glVertex3f(mapX*70, hHeightField[mapX][mapZ]*15, mapZ*70);	
				
				glTexCoord2f((float)mapX / width_, (float)(mapZ + 1) / height_) ;
				glVertex3f(mapX*70, hHeightField[mapX][mapZ+1]*15, (mapZ+1)*70);	
				
				glTexCoord2f((float)(mapX + 1) / width_, (float)mapZ / height_);
				glVertex3f((mapX + 1)*70, hHeightField[mapX + 1][mapZ]*15, mapZ*70);	
				
				glTexCoord2f((float)(mapX + 1) / width_, (float)(mapZ + 1) / height_);
				glVertex3f((mapX + 1)*70, hHeightField[mapX + 1][mapZ + 1]*15, (mapZ + 1)*70);
			glEnd();
		}
		}
		*/
		
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_VERTEX_ARRAY);
    
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
}

float height::getHeightOfTerrain(float worldX, float worldZ, BYTE heights[][512])
{   
    //Image is (256 x 256)
    float gridLength = 512;
    float terrainLength = 512;

    float terrainX = worldX-x;
    float terrainZ = worldZ-z;
    float gridSquareLength = size*terrainLength / ((float)gridLength - 1);
    int gridX = (int)std::floor(terrainX / gridSquareLength);
    int gridZ = (int)std::floor(terrainZ / gridSquareLength);

    //Check if position is on the terrain
    if (gridX >= gridLength - 1 || gridZ >= gridLength - 1 || gridX < 0 || gridZ < 0)
    {
        return 0;
    }

    //Find out where the player is on the grid square
    float xCoord = std::fmod(terrainX, gridSquareLength) / gridSquareLength;
    float zCoord = std::fmod(terrainZ, gridSquareLength) / gridSquareLength;
    float answer = 0.0;

    //Top triangle of a square else the bottom
    if (xCoord <= (1 - zCoord))
    {
        answer = barryCentric(vector3d(0, heights[gridX][gridZ], 0),
        vector3d(1, heights[gridX + 1][gridZ], 0), vector3d(0, heights[gridX][gridZ + 1], 1),
        vector3d(xCoord, zCoord));
    }

    else 
    {
        answer = barryCentric(vector3d(1, heights[gridX + 1][gridZ], 0),
        vector3d(1, heights[gridX + 1][gridZ + 1], 1), vector3d(0, heights[gridX][gridZ + 1], 1),
        vector3d(xCoord, 0,zCoord));
    }

    return answer;
} 

float height::barryCentric(vector3d p1, vector3d p2, vector3d p3, vector3d pos)
{
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
