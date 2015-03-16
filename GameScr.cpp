﻿#include "GameScr.h"
#include <string>
using namespace std;

GameScr::GameScr()
{
}

void GameScr::onInit() {
	level = 2;
	string strTmp = imgItemDrop + to_string(ID_EGG_PNG) + ".png";
	char *str =(char *)strTmp.c_str();
	textureEgg.Init(str, 25, 27);
	
	strTmp = imgItemDrop + to_string(ID_SHIT_PNG) + ".png";
	char *str1 =(char *)strTmp.c_str();
	textureShit.Init(str1, 30, 30);

	scoreEat = 0;
	scoreDropEggs = 0;
	scoreEatShit = 0;
	listAnimal.clear();
	listItemDrop.clear();
	basket = Object();
	basket.setTexture(imgBasket, 120, 100);
	basket.setXY((SCREEN_WIDTH - basket.getWidth()) << 1, SCREEN_HEIGHT - basket.getHeight() - 20);
	addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);
	/*addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);
	addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);
	addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);*/
}

void GameScr::onPaint() {
	// paint score
	DrawString("Score:", 5, 5,D3DCOLOR_ARGB(255,0,0,0));
	string strTmp = to_string(scoreEat) + "";
	char* sScore = (char *)strTmp.c_str();
	DrawString(sScore, 73, 5,D3DCOLOR_ARGB(255,50,2,255));
	// paint score drop egg
	textureEgg.Blit(130, 5);
	strTmp = to_string(scoreDropEggs) + "";
	char* sScore1 = (char *)strTmp.c_str();
	DrawString(sScore1, 160, 5,D3DCOLOR_ARGB(255,255,2,62));
	// paint score eat shit
	textureShit.Blit(200, 5);
	strTmp = to_string(scoreEatShit) + "";
	char* sScore2 = (char *)strTmp.c_str();
	DrawString(sScore2, 230, 5,D3DCOLOR_ARGB(255,255,2,62));

	list<Animal>::iterator iter_name; // Khai báo con trỏ để duyệt
	for (iter_name = listAnimal.begin(); iter_name != listAnimal.end(); iter_name++) {
		(*iter_name).onPaint();
	}
	
	list<ItemDrop>::iterator iter_name2; // Khai báo con trỏ để duyệt
	for (iter_name2 = listItemDrop.begin(); iter_name2 != listItemDrop.end(); iter_name2++) {
		(*iter_name2).onPaint();
	}
	basket.onPaint();
	if(gameState == isGameOver) {
		DrawRetangle(100, 200, 300, 200, D3DCOLOR_ARGB(255,255,2,62));
	}
}

void GameScr::onUpdate() {
	if(gameState == isPlaying) {
		basket.onUpdate();

		list<Animal>::iterator iter_name; // Khai báo con trỏ để duyệt
		for (iter_name = listAnimal.begin(); iter_name != listAnimal.end(); iter_name++) {
			(*iter_name).onUpdate();
			if((*iter_name).onPorm()) {
				int type = rand() % 2;
				ItemDrop itemDrop = ItemDrop(type + 1, 
					(*iter_name).getX() +(*iter_name).getWidth() / 2, 
					(*iter_name).getY() + (*iter_name).getHeight() / 2, level);
			
				listItemDrop.push_back(itemDrop);
			}
		}
	
		list<ItemDrop>::iterator iter_name2; // Khai báo con trỏ để duyệt
		for (iter_name2 = listItemDrop.begin(); iter_name2 != listItemDrop.end(); iter_name2++) {
			(*iter_name2).onUpdate();
			if((*iter_name2).getY() >= SCREEN_HEIGHT) {
				(*iter_name2).onDestroy();
				if((*iter_name2).getTypeItem() == ID_EGG_PNG) {
					scoreDropEggs ++;
				}
				if(iter_name2 != --listItemDrop.end()) {
					listItemDrop.erase(iter_name2++);
				}
			}
		}
		onCheckEat();
	}
}

bool GameScr::onCheckGameOver() {

	if(scoreDropEggs >= 3 || scoreEatShit >= 3) {
		onGameOver();
		return true;
	}
	return false;
}

void GameScr::onCheckEat() {
	list<ItemDrop>::iterator iter_name2;
	for (iter_name2 = listItemDrop.begin(); iter_name2 != listItemDrop.end(); iter_name2++) {
		int x0 = (*iter_name2).getX();
		int y0 = (*iter_name2).getY();
		int w0 = (*iter_name2).getWidth();
		int h0 = (*iter_name2).getHeight();
		int x1 = basket.getX();
		int y1 = basket.getY();
		int w1 = basket.getWidth();
		int h1 = basket.getHeight();
		if(x0 + w0> x1 + 20 && x0 + 30 < x1 + w1 && y0 + h0 > y1 + 40 && y0 - 20 < y1 + h1) {
			// la trứng thì cộng điểm
			if((*iter_name2).getTypeItem() == ID_EGG_PNG) {
				scoreEat ++;
				if(scoreEat % 20 == 0) {
					level++;
				}
			} else {
				scoreEatShit ++;
			}
			(*iter_name2).onDestroy();
			if(iter_name2 != --listItemDrop.end()) {
				listItemDrop.erase(iter_name2++);
			}
		}
	}
}

void GameScr::WindowProcedure (HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
	POINTS coords; //Mouse coords
	int xOlder = 0;
    //Check message
    switch(uMessage)
    {
	case WM_KEYDOWN:
		{
			switch (wParam) {
			case VK_LEFT:
				xOlder = basket.getX();
				if(xOlder > 0) {
					basket.setX(xOlder - 15);
				}
				// cout << basket.getX();
				break;
			case VK_RIGHT:
				xOlder = basket.getX();
				if(xOlder < (SCREEN_WIDTH - basket.getWidth())) {
					basket.setX(xOlder + 15);
				}
				// cout << basket.getX();
				break;
			case (int)'g':
			case (int)'G':
				addNewAnimal(ID_GA_PNG);
				break;
			case (int)'v':
			case (int)'V':
				addNewAnimal(ID_VIT_PNG);
				break;
			case (int)'n':
			case (int)'N':
				addNewAnimal(ID_NGAN_PNG);
				break;
			case VK_DOWN:
				break;
			case VK_SPACE:
				if(gameState == isGameOver) {
					onStart();
				}
				break;
			}
			break;
		}
    case WM_MOUSEMOVE:
        //Get mouse coords
        coords = MAKEPOINTS (lParam);
		if(gameState == isPlaying) {
			if(coords.x < (SCREEN_WIDTH - basket.getWidth())) {
				basket.setX(coords.x);
			} else {
				basket.setX(SCREEN_WIDTH - basket.getWidth());
			}
		}
        break;

    case WM_LBUTTONDOWN:
        //Get mouse coords
        coords = MAKEPOINTS (lParam);
        if(gameState == isGameOver) {
			onStart();
		}
        break;	

    case WM_LBUTTONUP:
        //Get mouse coords
        coords = MAKEPOINTS (lParam);
        break;

    case WM_RBUTTONDOWN:
        //Get mouse coords
        coords = MAKEPOINTS (lParam);
        break;

    case WM_RBUTTONUP:
        //Get mouse coords
        coords = MAKEPOINTS (lParam);
        break;	
    }
}

void GameScr::addNewAnimal(int type) {
	Animal animal = Animal(type, rand() % 400, rand() % 100 + 30, rand() % 3 + 1);
	listAnimal.push_back(animal);
}

void GameScr::onStart() {
	onInit();
	super::onStart();
}

void GameScr::onResume() {
	super::onResume();
}

void GameScr::onPause() {
	super::onPause();
}

void GameScr::onGameOver() {
	if(gameState != isGameOver) {
		 MessageBox(NULL, "Game over. De choi lai, ban chon bat ky vao man hinh hoac bam phim Space (phim cach)", "GameOver", MB_OK);
		super::onGameOver();
	}
}

void GameScr::onDestroy() {
	//basket.texture.texture = NULL;
}
