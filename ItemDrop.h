#pragma once
#include "object.h"
class ItemDrop : public Object
{
	public:
		ItemDrop(int type, int speed);
		void setSpeed(int speed);
		void setTypeItem(int type);
		int getTypeItem();
		void onPaint();
		void onUpdate();
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

