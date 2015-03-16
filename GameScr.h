#pragma once
#include "screen.h"
#include "Object.h"
#include "Animal.h"
#include "ItemDrop.h"
#include <list>

class GameScr : public Screen
{
	public:
		GameScr(void);
		void onInit();
		void onPaint();
		void onUpdate();
		void onDestroy();
		void addNewAnimal(int type);
		void WindowProcedure (HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	private:
		Object basket;
		list<Animal> listAnimal;
		list<ItemDrop> listItemDrop;
};

