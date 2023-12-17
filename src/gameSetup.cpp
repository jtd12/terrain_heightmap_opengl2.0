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
	//	cam->moveCameraUp(0.0);
			glutPostRedisplay();
			break;
		
		case 'z':	
		case 'Z':
		  if(cam->getPitch()!=90 && cam->getPitch()!=-90)
			cam->moveCamera(0);
		//cam->moveCameraUp(180.0);
			glutPostRedisplay();
			break;
		
		case 'a':	
		case 'A':
			cam->moveCamera(90);
			glutPostRedisplay();
			break;
			
		case 'd':
		case 'D':
			cam->moveCamera(-90);
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
	


	collisionHeight(heightMap[0],cam,car,1500,1500);
 	collisionHeight(heightMap[1],cam,car,1500,1500);
 	collisionHeight(heightMap[2],cam,car,1500,1500);
    collisionHeight(heightMap[3],cam,car,-9000,-3500);
    
    
}

void setup::collisionHeight(height* h,camera* c,vehicule*v, float xpos,float zpos)
{
	



   float terrainHeight = h->getHeightOfTerrain(c->getLocation().x+xpos, c->getLocation().z+zpos, h->hHeightField);
   
 

    
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
	vector3d camPos;
	vector3d target;
	vector3d camUp;
	
	 camPos=vector3d(car->getLocation().x-cos(car->getRotation()*M_PI/180.0f)*2200,1500,car->getLocation().z+sin(car->getRotation()*M_PI/180.0f)*2200);
	 target=car->getLocation();
	 camUp=vector3d(0,1,0);
	 
	//glTranslated(0,0,0);
	

    
 	cam->update();
 	
    gluLookAt(camPos.x,camPos.y,camPos.z,target.x,target.y+500,target.z,camUp.x,camUp.y,camUp.z);
 
	glPushMatrix();
	glRotated(sky->getRot(),0,0.5,0);
	sky->drawSkybox(40000);
	glPopMatrix();
	glPushMatrix();
	glTranslated(1500,0,1500);
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
