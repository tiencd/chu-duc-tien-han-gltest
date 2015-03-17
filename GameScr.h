#pragma once
#include "screen.h"
#include "Object.h"
#include "Animal.h"
#include "ItemDrop.h"
#include <list>
#include "Utils.h"

class GameScr : public Screen
{
	public:
		GameScr(void);
		void WindowProcedure (HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
		void onInit();
		void addNewAnimal(int type);
		void onPaint();
		void onUpdate();
		void onStart();
		void onPause();
		void onResume();
		void onRestart();
		void onGameOver();
		void onDestroy();
		bool onCheckGameOver();
	private:
		int dem;
		typedef Screen super;
		void doChangeStateGame();
		void onCheckEat();
		Object basket;
		list<Animal> listAnimal;
		list<ItemDrop> listItemDrop;
		CTexture textureEgg, textureShit;
		CTexture texturePause, texturePlay;
		int level;
		int scoreEat;
		int scoreDropEggs, scoreEatShit;
};

