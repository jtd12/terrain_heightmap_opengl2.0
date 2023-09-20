#include"skybox.h"


skybox::skybox()
{
	 
		  
        sky[SKY_LEFT]=loadTexture("data/sky/left.bmp",true,512,512);
        sky[SKY_BACK]=loadTexture("data/sky/front.bmp",true,512,512);
        sky[SKY_RIGHT]=loadTexture("data/sky/right.bmp",true,512,512);
        sky[SKY_FRONT]=loadTexture("data/sky/back.bmp",true,512,512);
        sky[SKY_TOP]=loadTexture("data/sky/top.bmp",true,512,512);
        sky[SKY_BOTTOM]=loadTexture("data/sky/bottom.bmp",true,512,512);
        rot=0.0f;
}
 
skybox::~skybox()
{
        glDeleteTextures(6,&sky[0]);
}

GLuint skybox:: loadTexture(const char * filename,bool  useMipMap,int w,int h)
{
 GLuint texture;

  int width, height;
  
  unsigned char * data;

  FILE * file;

  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
  width=w;
  height=h;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

 for(int i = 0; i < width * height ; ++i)
{
   int index = i*3;
   unsigned char B,R;
   B = data[index];
   R = data[index+2];

   data[index] = R;
   data[index+2] = B;

}


glGenTextures( 1, &texture );
 glBindTexture(GL_TEXTURE_2D,texture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
free( data );

return texture;
}


void skybox::update()
{
	rot+=0.01f;
}

float skybox::getRot()
{
return rot;	
}

void skybox:: drawSkybox(float size)
{
	glPushMatrix();
float difamb[]={1.0,0.5,0.3,1.0};
	
       bool b1=glIsEnabled(GL_TEXTURE_2D); //new, we left the textures turned on, if it was turned on
    glDisable(GL_LIGHTING); //turn off lighting, when making the skybox
    glEnable(GL_TEXTURE_2D);    //and turn on texturing
        glEnable(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D,sky[SKY_BACK]);
    	glColor3d(1,1,1);
    	
        glBegin(GL_QUADS);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,difamb);
        glNormal3f(0.0,0.0,1.0);
                //back face
                glTexCoord2f(0.1,0.1);
                glVertex3f(size/2,size/2,size/2);
                glTexCoord2f(0.99,0.1);
                glVertex3f(-size/2,size/2,size/2);
                glTexCoord2f(0.99,0.99);
                glVertex3f(-size/2,-size/2,size/2);
                glTexCoord2f(0.1,0.99);
                glVertex3f(size/2,-size/2,size/2);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,sky[SKY_LEFT]);
        glBegin(GL_QUADS);     
        glNormal3f(-1.0,0.0,0.0);
                //left face
                glTexCoord2f(0.1,0.1);
                glVertex3f(-size/2,size/2,size/2);
                glTexCoord2f(0.99,0.1);
                glVertex3f(-size/2,size/2,-size/2);
                glTexCoord2f(0.99,0.99);
                glVertex3f(-size/2,-size/2,-size/2);
                glTexCoord2f(0.1,1);
                glVertex3f(-size/2,-size/2,size/2);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,sky[SKY_FRONT]);
        glBegin(GL_QUADS);     
        glNormal3f(0.0,0.0,-1.0);
                //front face
                glTexCoord2f(0.99,0.1);
                glVertex3f(size/2,size/2,-size/2);
                glTexCoord2f(0.1,0.1);
                glVertex3f(-size/2,size/2,-size/2);
                glTexCoord2f(0.1,0.98);
                glVertex3f(-size/2,-size/2,-size/2);
                glTexCoord2f(0.99,0.99);
                glVertex3f(size/2,-size/2,-size/2);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,sky[SKY_RIGHT]);
        glBegin(GL_QUADS);     
        glNormal3f(1.0,0.0,0.0);
                //right face
                glTexCoord2f(0.1,0.1);
                glVertex3f(size/2,size/2,-size/2);
                glTexCoord2f(0.99,0.1);
                glVertex3f(size/2,size/2,size/2);
                glTexCoord2f(0.99,0.99);
                glVertex3f(size/2,-size/2,size/2);
                glTexCoord2f(0.1,0.99);
                glVertex3f(size/2,-size/2,-size/2);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,sky[SKY_TOP]);          
        glBegin(GL_QUADS);     
		  glNormal3f(0.0,1.0,0.0);                 //top face
                glTexCoord2f(0.99,0.1);
                glVertex3f(size/2,size/2,size/2);
                glTexCoord2f(0.1,0.1);
                glVertex3f(-size/2,size/2,size/2);
                glTexCoord2f(0.1,0.99);
                glVertex3f(-size/2,size/2,-size/2);
                glTexCoord2f(0.99,0.99);
                glVertex3f(size/2,size/2,-size/2);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,sky[SKY_BOTTOM]);               
        glBegin(GL_QUADS);     
         glNormal3f(0.0,-1.0,0.0);
                //bottom face
                glTexCoord2f(0.99,0.99);
                glVertex3f(size/2,-size/2,size/2);
                glTexCoord2f(0.1,0.99);
                glVertex3f(-size/2,-size/2,size/2);
                glTexCoord2f(0.1,0.1);
                glVertex3f(-size/2,-size/2,-size/2);
                glTexCoord2f(0.99,0.1);
                glVertex3f(size/2,-size/2,-size/2);
        glEnd();
          glEnable(GL_LIGHTING);  //turn everything back, which we turned on, and turn everything off, which we have turned on.
    glEnable(GL_DEPTH_TEST);
    if(!b1)
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
  
       
}
 
