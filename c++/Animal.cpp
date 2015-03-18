#include "Animal.h"
#include "Constrain.h"
#include "Utils.h"

Animal::Animal(int type, int x, int y)
{
	isGoUp = rand()%2;
	isGoLeft = rand()%2;
	setType(type);
	setXY(x, y);
	speed = rand() % 4;
	speedUp = rand() % 3;
	timeChangeAnimation = timeSeconds = Utils::getTimeNow();
}

void Animal::onDestroy() {
	super::onDestroy();
}

void Animal::setType(int typeAnimal) {
	string strTmp = imgAnimal + to_string(typeAnimal) + ".png";
	char *str =(char *)strTmp.c_str();
	setTexture(str, 0, 0);
}

void Animal::onPaint() {
	super::onPaint();
}

void Animal::onUpdate() {
	if(Utils::getTimeNow() - timeChangeAnimation > rand()%3000 + 2000) {
		timeChangeAnimation = Utils::getTimeNow();
		int ran = rand() % 4;
		if(ran > 0) {
			speed = rand() % 4;
			speedUp = rand() % 3;
			isGoLeft = rand()%2;
			isGoUp = rand()%2;
		}
	}
	if(isGoLeft) {
		if(x <= 0) {
			x = 0;
			isGoLeft = FALSE;
		} else {
			x -= speed;
		}
	} else {
		if(x >= SCREEN_WIDTH - getWidth()) {
			isGoLeft = TRUE;
		} else {
			x += speed;
		}
	}
	
	if(isGoUp) {
		if(y <= 30) {
			y = 30;
			isGoUp = FALSE;
		} else {
			y -= speedUp;
		}
	} else {
		if(y >= 200) {
			isGoUp = TRUE;
		} else {
			y += speedUp;
		}
	}
	
}

bool Animal::onPorm() {
	long timeSeconds = Utils::getTimeNow();
	if(timeSeconds - this->timeSeconds >= TIME_ANIMAL_PORN * 1000) {
		this->timeSeconds = timeSeconds;
		return true;
	}
	return false;
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