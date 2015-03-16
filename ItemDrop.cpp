#include "ItemDrop.h"
#include "Constrain.h"

ItemDrop::ItemDrop(int type, int speed)
{
	setTypeItem(type);
	setSpeed(speed);
}

void ItemDrop::setSpeed(int speed) {
	this->speed = speed;
}

void ItemDrop::setTypeItem(int typeItem) {
	string strTmp = imgItemDrop + to_string(typeItem) + ".png";
	char *str =(char *)strTmp.c_str();
	setTexture(str, 0, 0);
}

void ItemDrop::onPaint() {
	super::onPaint();
}

void ItemDrop::onUpdate() {
	if(y < SCREEN_HEIGHT) {
		y -= speed;
	}
}

void ItemDrop::setTexture(char sFilename[], int width, int height) {
	super::setTexture(sFilename, width, height);
}

void ItemDrop::setXY(int x, int y) {
	super::setXY(x, y);
}

void ItemDrop::setX(int x) {
	super::setX(x);
}

void ItemDrop::setY(int y) {
	super::setY(y);
}

int ItemDrop::getX() {
	return super::getX();
}

int ItemDrop::getY() {
	return super::getY();
}

int ItemDrop::getWidth() {
	return super::getWidth();
}

int ItemDrop::getHeight() {
	return super::getHeight();
}