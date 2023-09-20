#ifndef DEF_CAR_H
#define DEF_CAR_H
#include"objloader.hpp"
#include<vector>
#include<C:\library\freeglut\include\GL\freeglut.h>

class roue
{
public:
		roue(const char * filename);
		~roue();
		void update();
		void draw();
		
	private:
		objloader *obj;
		int roue_;	
};


class porte_vitre
{
public:
		porte_vitre(const char * filename);
		~porte_vitre();
		void update();
		void draw();
		
	private:
		objloader *obj;
		int porte_vitre_;	
};

class tb
{
public:
		tb(const char * filename);
		~tb();
		void update();
		void draw();
		
	private:
		objloader *obj;
		int tb_;	
};

class porte
{
	public:
		porte(const char * filename);
		~porte();
		void update();
		void draw();
		void setRotPorte(float r);
		void setRotPorteEgal(float r);
		float getRotPorte();
		
	private:
		objloader *obj;
		porte_vitre *p1_vitre;
		porte_vitre *p2_vitre;
		int porte_;
		float rotPorte;


		
};

class vitres
{
	public:
		vitres();
		~vitres();
		void update();
		void draw();
		
	private:
		int vitres_;
		objloader *obj;
		
};

class volant
{
	public:
		volant();
		~volant();
		void update();
		void draw();
		
	private:
		int volant_;
		objloader *obj;
		
};

class vehicule
{
	public:
		vehicule();
		~vehicule();
		void ouvrirPorte1();
		void ouvrirPorte2();
		void update();
		void draw();
		void rouler();
		void setLocation(float locY);
		vector3d getLocation();
		void setLocY(float y);
		void specialKey(int key, int x, int y);
		void specialKeyUp(int key, int x, int y);
	private:
	int car;
	std::vector<porte *> door;
	std::vector<roue *> wheel;
	objloader *obj;
	vitres *v;
	tb *tab;
	volant * vv;
	vector3d pos;
	float rot;
	int up,down,right,left;
	

};

#endif
