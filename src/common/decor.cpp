#include"decor.h"

decor::decor()
{
		obj=new objloader();
		sol=obj->load("data/decor.obj",NULL);
	
		
}
decor::~decor()
{
	delete obj;
}
void decor::update()
{

}
void decor::draw()
{
	glPushMatrix();	
	glTranslated(20000,800,7000);
	glScaled(20,20,20);
	glCallList(sol);
	glPopMatrix();
}
