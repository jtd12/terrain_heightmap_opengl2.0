#ifndef DEF_SKYBOX_H
#define DEF_SKYBOX_H
#include"vector.h"
#include <gl/gl.h>
#include<gl/glu.h>
#include<iostream>
 #ifndef GL_UNSIGNED_SHORT_5_6_5
 #define GL_UNSIGNED_SHORT_5_6_5 0x8363
 #endif
#ifndef M_PI
#define M_PI 3.1415926535
#endif

class skybox
{
	public:
skybox();
~skybox();
GLuint loadTexture(const char * filename,bool  useMipMap,int w,int h);
void drawSkybox(float size);
void update();
float getRot();

	private:
	enum {SKY_LEFT=0,SKY_BACK,SKY_RIGHT,SKY_FRONT,SKY_TOP,SKY_BOTTOM};
	unsigned int sky[6];
		float rot;

		
};

#endif
