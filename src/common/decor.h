#ifndef DEF_DECOR_H
#define DEF_DECOR_H
#include"vector.h"
#include"objloader.hpp"

class decor
{
	public:
		decor();
		~decor();
		void update();
		void draw();
	private:
		objloader *obj;
		int sol;
	
};
#endif
