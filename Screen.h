#pragma once

#include <Windows.h>
#include "Constrain.h"

class Screen
{
	public:
		Screen();
		virtual void onInit();
		virtual void onPaint();
		virtual void onUpdate();
		virtual void onDestroy();
		virtual void WindowProcedure (HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

};

