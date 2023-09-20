#ifndef DEF_GAMESETUP_HPP
#define DEF_GAMESETUP_HPP

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <fstream>
#include <assert.h>
#include"common/heightmap.hpp"
#include"common/objloader.hpp"
#include"common/skybox.h"
#include"common/car.h"
#include"common/camera.h"
#include"common/decor.h"
#include<vector>
#include<GL/gl.h>
#include<GL/glu.h>
#include<C:\library\freeglut\include\GL\freeglut.h>





class setup
{
	public:
		
	setup();
	~setup();
	void init();
	void keyboard(unsigned char key, int x, int y);
	void mouseMove(int mx,int my);
	void specialKey(int key, int x, int y);
	void mouseState(int button, int state, int x, int y);
	void specialKeyUp(int key, int x, int y);
	void collisionHeight(height* h,camera* c,vehicule*v,float xpos,float zpos);
	void update();
	void draw();

	
	private:
	std::vector<height*> heightMap;
	skybox *sky;
	vehicule * car;
	decor* dec;
	camera * cam;


	
};




#endif

