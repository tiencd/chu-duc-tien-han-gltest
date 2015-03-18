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
		int onInit();
		void addNewAnimal(int type);
		void onPaint();
		void onUpdate();
		void onStart();
		void onPause();
		void onResume();
		void onGameOver();
		void onDestroy();
		bool onCheckGameOver();
	private:
		typedef Screen super;
		int dem;
		Object basket;
		list<Animal> listAnimal;
		list<ItemDrop> listItemDrop;
		CTexture textureEgg, textureShit;
		CTexture texturePause, texturePlay, textureBg;
		CTexture textureAddAnimal[3];
		int level;
		int scoreEat;
		int scoreDropEggs, scoreEatShit;
		long timeDisplayText;
		void onResetData();
		void doChangeStateGame();
		void onCheckEat();
};

