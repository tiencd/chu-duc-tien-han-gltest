#include "ItemDrop.h"
#include "Constrain.h"

ItemDrop::ItemDrop(int type, int x, int y, int speed)
{
	setType(type);
	setSpeed(speed);
	setXY(x - getWidth() / 2, y);
}

void ItemDrop::onDestroy() {
	super::onDestroy();
}

void ItemDrop::setSpeed(int speed) {
	this->speed = speed;
}

void ItemDrop::setType(int typeItem) {
	string strTmp = imgItemDrop + to_string(typeItem) + ".png";
	char *str =(char *)strTmp.c_str();
	this->typeItem = typeItem;
	setTexture(str, 40, 45);
}

int ItemDrop::getType() {
	return typeItem;
}

void ItemDrop::onPaint() {
	super::onPaint();
}

void ItemDrop::onUpdate() {
	//if(y <= SCREEN_HEIGHT) {
		y += speed;
	//}
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