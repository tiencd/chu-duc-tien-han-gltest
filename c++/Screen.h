#pragma once

#include <Windows.h>
#include "Constrain.h"

enum GAME_STATE {
	isFree,  isPlaying,  isPause,  isGameOver,
};

class Screen
{
	public:
		Screen();
		virtual int onInit();
		virtual void onPaint();
		virtual void onUpdate();
		virtual void onStart();
		virtual void onPause();
		virtual void onResume();
		virtual void onGameOver();
		virtual void onDestroy();
		virtual void WindowProcedure (HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
		GAME_STATE gameState;
		void resetKeyboard();
		bool KEY_LEFT_DOWN;
		bool KEY_LEFT_UP;
		bool KEY_RIGHT_DOWN;
		bool KEY_RIGHT_UP;
};

