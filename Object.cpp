#include "Object.h"

Object::Object() {

}

void Object::onPaint() {
	texture.Blit(x,y);
}

void Object::onUpdate() {}

void Object::setTexture(char sFilename[], int width, int height) {
	if(!this->texture.Init(sFilename, width, height)) {
		MessageBox (NULL, "khong the load anh ", sFilename, MB_OK);
        return;
	}
}


void Object::setSpeed(int speed) {
	this->speed = speed;
}

void Object::setXY(int x, int y) {
	this->x = x;
	this->y = y;
}

void Object::setX(int x) {
	this->x = x;
}

void Object::setY(int y) {
	this->y = y;
}

int Object::getX() {
	return x;
}

int Object::getY() {
	return y;
}

int Object::getWidth() {
	return texture.texture->width;
}

int Object::getHeight() {
	return texture.texture->height;
}