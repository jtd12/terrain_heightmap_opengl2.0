#include"gameSetup.hpp"



setup::setup()
{

car=new vehicule();
sky=new skybox();
cam=new camera();

heightMap.push_back(new height(0,0));
heightMap.push_back(new height(520,0));
heightMap.push_back(new height(0,520));
heightMap.push_back(new height(-520,0));

heightMap[0]->loadHeightmap("data/heightmap.bmp",512,512);
heightMap[1]->loadHeightmap("data/heightmap.bmp",512,512);
heightMap[2]->loadHeightmap("data/heightmap.bmp",512,512);
heightMap[3]->loadHeightmap("data/heightmap.bmp",512,512);

dec=new decor();

}



setup::~setup()
{
delete car;
delete sky;
delete cam;

delete dec;

for(int i=0;i<heightMap.size();i++)
 delete heightMap[i];

}



void setup::mouseMove(int mx,int my)
{
	cam->control(mx,my);
}
void setup:: mouseState(int button, int state, int x, int y)
{
	cam->mouse( button,  state,  x,  y);
}
void setup::keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'c':
		case 'C': 
		car->ouvrirPorte1();
		glutPostRedisplay();
		break;
		
		case 'v':
		case 'V': 
		car->ouvrirPorte2();
		glutPostRedisplay();
		break;
		
		case 'w':
		case 'W':
		if(cam->getPitch()!=90 && cam->getPitch()!=-90)
			cam->moveCamera(180);
		cam->moveCameraUp(0.0);
			glutPostRedisplay();
			break;
		
		case 'z':	
		case 'Z':
				 if(cam->getPitch()!=90 && cam->getPitch()!=-90)
			cam->moveCamera(0);
		cam->moveCameraUp(180.0);
			glutPostRedisplay();
			break;
		
		case 'a':	
		case 'A':
			cam->moveCamera(-90);
			glutPostRedisplay();
			break;
			
		case 'd':
		case 'D':
			cam->moveCamera(90);
			glutPostRedisplay();
			break;
			
		     
	}
}
void setup::specialKey(int key, int x, int y)
{
	car->specialKey(key,x,y);
	

}

void setup::specialKeyUp(int key, int x, int y)
 {
 		car->specialKeyUp(key,x,y);
 }



void setup::update()
{

	car->update();
	sky->update();
	

	collisionHeight(heightMap[0],cam,car,0,0);
 	collisionHeight(heightMap[1],cam,car,0,0);
 	collisionHeight(heightMap[2],cam,car,-5000,0);
    collisionHeight(heightMap[3],cam,car,-5000,-5000);
    
    
}

void setup::collisionHeight(height* h,camera* c,vehicule*v, float xpos,float zpos)
{
	



   float terrainHeight = h->getHeightOfTerrain(c->getLocation().x+xpos, c->getLocation().z+zpos, h->hHeightField);
   
 
    if (c->getLocation().y < terrainHeight+1000)
    {
        c->setLocation(terrainHeight+1000);
    }
    
    
 
    else
	{
		c->setLocY(2.5f);
	}

    
  float terrainHeight2 = h->getHeightOfTerrain(v->getLocation().x+xpos, v->getLocation().z+zpos, h->hHeightField);
   
 
    if (v->getLocation().y < terrainHeight2+1000)
    {
        v->setLocation(terrainHeight2+1000);
    }
    
    
 
    else
	{
		v->setLocY(2.5f);
	}





}

void setup::draw()
{
	glTranslated(0,0,0);
	
    
 	cam->update();
 	
 
 
	glPushMatrix();
	glRotated(sky->getRot(),0,0.5,0);
	sky->drawSkybox(40000);
	glPopMatrix();
	glPushMatrix();
	car->draw();
	glPopMatrix();
	glPushMatrix();
	dec->draw();
	glPopMatrix();
	glPushMatrix();
//	glTranslated(0,-8000,0);
for(int i=0;i<heightMap.size();i++)
	heightMap[i]->renderHeightMap();
	
	glPopMatrix();
}
