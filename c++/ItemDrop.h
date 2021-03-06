#pragma once
#include "object.h"
class ItemDrop : public Object
{
	public:
		ItemDrop(int type, int x, int y, int speed);
		void setSpeed(int speed);
		void setType(int type);
		int getType();
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
	private:
		typedef Object super;
		int typeItem;
		int speed;
};

