#include "Screen.h"


Screen::Screen()
{

}

void Screen::WindowProcedure (HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {

}


int Screen::onInit() {
	return true;
}

void Screen::onPaint() {

}

void Screen::onUpdate() {

}

void Screen::onStart() {
	gameState = isPlaying;
}

void Screen::onResume() {
	gameState = isPlaying;
}

void Screen::onPause() {
	gameState = isPause;
}

void Screen::onGameOver() {
	gameState = isGameOver;
}

void Screen::onDestroy() {

}