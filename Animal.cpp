#include "Animal.h"
#include "Constrain.h"
#include "Utils.h"

Animal::Animal(int type, int x, int y, int speed)
{
	isGoLeft = false;
	setTypeAnimal(type);
	setXY(x, y);
	setSpeed(speed);
	timeSeconds = Utils::getTimeToSeconds();
}

void Animal::onDestroy() {
	super::onDestroy();
}

void Animal::setTypeAnimal(int typeAnimal) {
	string strTmp = imgAnimal + to_string(typeAnimal) + ".png";
	char *str =(char *)strTmp.c_str();
	setTexture(str, 0, 0);
}

void Animal::onPaint() {
	super::onPaint();
}

void Animal::onUpdate() {
	if(isGoLeft) {
		if(x <= 0) {
			x = 0;
			isGoLeft = false;
		} else {
			x -= speed;
			if(x < 0) {
				x = 0;
			}
		}
	} else {
		if(x >= SCREEN_WIDTH - getWidth()) {
			isGoLeft = true;
		} else {
			x += speed;
			if(x >= SCREEN_WIDTH - getWidth()) {
				x = SCREEN_WIDTH - getWidth();
			}
		}
	}
}

bool Animal::onPorm() {
	double timeSeconds = Utils::getTimeToSeconds();
	if(timeSeconds - this->timeSeconds >= 5) {
		this->timeSeconds = timeSeconds;
		return true;
	}
	return false;
}

void Animal::setSpeed(int speed) {
	this->speed = speed;
}

void Animal::setTexture(char sFilename[], int width, int height) {
	super::setTexture(sFilename, width, height);
}

void Animal::setXY(int x, int y) {
	super::setXY(x, y);
}

void Animal::setX(int x) {
	super::setX(x);
}

void Animal::setY(int y) {
	super::setY(y);
}

int Animal::getX() {
	return super::getX();
}

int Animal::getY() {
	return super::getY();
}

int Animal::getWidth() {
	return super::getWidth();
}

int Animal::getHeight() {
	return super::getHeight();
}