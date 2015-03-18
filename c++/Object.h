#pragma once
#include "texture.h"

class Object
{
	public:
		Object();
		void onPaint();
		void onUpdate();
		void onDestroy();
		void setSpeed(int speed);
		void setXY(int x, int y);
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();
		void setTexture(char sFilename[], int width = 0, int height = 0);
		int getWidth();
		int getHeight();
	protected:
		int x;
		int y;
		int speed;
		int speedUp;
		CTexture texture;
};

