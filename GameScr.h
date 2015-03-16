#pragma once
#include "screen.h"
#include "Object.h"

class GameScr : public Screen
{
	public:
		GameScr(void);
		void onInit();
		void onPaint();
		void onUpdate();
		void onDestroy();
		void WindowProcedure (HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	private:
		Object basket;
};

