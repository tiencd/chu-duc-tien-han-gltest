#pragma once
#include "Object.h"

class Animal : Object
{
	public:
		Animal(int type, int x, int y);
		void setTypeAnimal(int type);
		int getTypeAnimal();
		void onPaint();
		void onUpdate();
		void onDestroy();
		void setXY(int x, int y);
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();
		void setTexture(char sFilename[], int width = 0, int height = 0);
		int getWidth();
		int getHeight();
		bool onPorm();
	private:
		typedef Object super;
		int typeAnimal;
		int isGoLeft, isGoUp;
		long timeChangeAnimation;
		long timeSeconds;
};

