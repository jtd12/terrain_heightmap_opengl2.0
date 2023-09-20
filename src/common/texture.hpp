#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include<GL/gl.h>
#include<GL/glu.h>

#define GL_BGR 0x80E0


struct img
{
	unsigned int width;
	unsigned int height;
	unsigned char * data;
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	
};


class textures
{
	GLuint texture_;
	
	public:
	
	textures();
	// Load a .BMP file using our custom loader
	GLuint loadBMP_custom(const char * imagepath);
	struct img images;
	//// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library, 
	//// or do it yourself (just like loadBMP_custom and loadDDS)
	//// Load a .TGA file using GLFW's own loader
	//GLuint loadTGA_glfw(const char * imagepath);
	
	// Load a .DDS file using GLFW's own loader
	GLuint loadDDS(const char * imagepath);

};





#endif
