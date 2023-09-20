#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"texture.hpp"



textures::textures()
{
	
}

GLuint textures::loadBMP_custom(const char * imagepath){



	//printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file

	
	// Actual RGB data
	//unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file)							    {

	 return -1;
	 }

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if ( fread(images.header, 1, 54, file)!=54 ){ 
		printf("Not a correct BMP file\n");
		return 0;
	}
	// A BMP files always begins with "BM"
	if ( images.header[0]!='B' || images.header[1]!='M' ){
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Make sure this is a 24bpp file
	if ( *(int*)&(images.header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    return 0;}
	if ( *(int*)&(images.header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    return 0;}

	// Read the information about the image
	images.dataPos    = *(int*)&(images.header[0x0A]);
	images.imageSize  = *(int*)&(images.header[0x22]);
	images.width      = *(int*)&(images.header[0x12]);
	images.height     = *(int*)&(images.header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (images.imageSize==0)    images.imageSize=images.width*images.height*3; // 3 : one byte for each Red, Green and Blue component
	if (images.dataPos==0)      images.dataPos=54; // The BMP header is done that way

	// Create a buffer
	images.data = new unsigned char [images.imageSize];

	// Read the actual data from the file into the buffer
	fread(images.data,1,images.imageSize,file);

	// Everything is in memory now, the file wan be closed
	fclose (file);

	glGenTextures( 1, &texture_);
	glBindTexture( GL_TEXTURE_2D, texture_ );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0,3, images.width, images.height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, images.data);
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
//gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );



//gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
	// OpenGL has now copied the data. Free our own version
	delete [] images.data;

	// Poor filtering, or ...

	
//	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
return texture_;


}

// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library, 
// or do it yourself (just like loadBMP_custom and loadDDS)
//GLuint loadTGA_glfw(const char * imagepath){
//
//	// Create one OpenGL texture
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//
//	// "Bind" the newly created texture : all future texture functions will modify this texture
//	glBindTexture(GL_TEXTURE_2D, textureID);
//
//	// Read the file, call glTexImage2D with the right parameters
//	glfwLoadTexture2D(imagepath, 0);
//
//	// Nice trilinear filtering.
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	// Return the ID of the texture we just created
//	return textureID;
//}




