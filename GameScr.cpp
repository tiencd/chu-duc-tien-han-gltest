#include "GameScr.h"
#include "Animal.h"
#include <iostream>
#include <vector>

using namespace std;

vector<Animal> listAnimal;
GameScr::GameScr()
{
}

void GameScr::onInit() {
	basket = Object();
	basket.setTexture(imgBasket, 0, 0);
	basket.setXY((SCREEN_WIDTH - basket.getWidth()) << 1, SCREEN_HEIGHT - basket.getHeight());
	Animal ga = Animal(ID_GA_PNG, 0, 5, 2);
	listAnimal.push_back(ga);
	Animal vit = Animal(ID_VIT_PNG, 400, 50, 4);
	listAnimal.push_back(vit);
	Animal ngan = Animal(ID_NGAN_PNG, 200, 25, 5);
	listAnimal.push_back(ngan);
}

void GameScr::onPaint() {
	basket.onPaint();
	vector<Animal>::iterator iter_name; // Khai báo con trỏ để duyệt
	for (iter_name = listAnimal.begin(); iter_name != listAnimal.end(); iter_name++) {
		(*iter_name).onPaint();
	}
	/*for (int i = 0; i < listAnimal.size(); i++)
	{
		listAnimal.at(i).onPaint();
	}*/
}

void GameScr::onUpdate() {
	basket.onUpdate();
	vector<Animal>::iterator iter_name; // Khai báo con trỏ để duyệt
	for (iter_name = listAnimal.begin(); iter_name != listAnimal.end(); iter_name++) {
		(*iter_name).onUpdate();
	}
	/*for (int i = 0; i < listAnimal.size(); i++)
	{
		listAnimal.at(i).onUpdate();
	}*/
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
					basket.setX(xOlder - 10);
				}
				cout << basket.getX();
				break;
			case VK_RIGHT:
				xOlder = basket.getX();
				if(xOlder < (SCREEN_WIDTH - basket.getWidth())) {
					basket.setX(xOlder + 10);
				}
				cout << basket.getX();
				break;
			/*case VK_UP:
				break;
			case VK_DOWN:
				break;*/
			}
			break;
		}
    case WM_MOUSEMOVE:
        //Get mouse coords
        coords = MAKEPOINTS (lParam);
		//int xNew = coords.x;
		if(coords.x < (SCREEN_WIDTH - basket.getWidth())) {
			basket.setX(coords.x);
		} else {
			basket.setX(SCREEN_WIDTH - basket.getWidth());
		}
        break;

    case WM_LBUTTONDOWN:
        //Get mouse coords
        coords = MAKEPOINTS (lParam);
        //bRunning = false;
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

void GameScr::onDestroy() {
	//basket.texture.texture = NULL;
}
