#include "GameScr.h"

GameScr::GameScr()
{
}

void GameScr::onInit() {
	basket = Object();
	basket.setTexture(imgBasket, 100, 80);
	basket.setXY((SCREEN_WIDTH - basket.getWidth()) << 1, SCREEN_HEIGHT - basket.getHeight() - 20);
	addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);
	addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);
	addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);
	addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);
}

void GameScr::onPaint() {
	DrawString("o no", 0, 0,D3DCOLOR_ARGB(255,0,0,0));
	list<Animal>::iterator iter_name; // Khai báo con trỏ để duyệt
	for (iter_name = listAnimal.begin(); iter_name != listAnimal.end(); iter_name++) {
		(*iter_name).onPaint();
	}
	
	list<ItemDrop>::iterator iter_name2; // Khai báo con trỏ để duyệt
	for (iter_name2 = listItemDrop.begin(); iter_name2 != listItemDrop.end(); iter_name2++) {
		(*iter_name2).onPaint();
	}
	basket.onPaint();
}

void GameScr::onUpdate() {
	basket.onUpdate();
	list<Animal>::iterator iter_name; // Khai báo con trỏ để duyệt
	for (iter_name = listAnimal.begin(); iter_name != listAnimal.end(); iter_name++) {
		(*iter_name).onUpdate();
		if((*iter_name).onPorm()) {
			int type = rand() % 2;
			ItemDrop itemDrop = ItemDrop(type + 1, 
				(*iter_name).getX() +(*iter_name).getWidth() / 2, 
				(*iter_name).getY() + (*iter_name).getHeight() / 2, 3);
			
			listItemDrop.push_back(itemDrop);
		}
	}
	
	list<ItemDrop>::iterator iter_name2; // Khai báo con trỏ để duyệt
	for (iter_name2 = listItemDrop.begin(); iter_name2 != listItemDrop.end(); iter_name2++) {
		(*iter_name2).onUpdate();
	}
	
	for (iter_name2 = listItemDrop.begin(); iter_name2 != listItemDrop.end(); iter_name2++) {
		int x0 = (*iter_name2).getX();
		int y0 = (*iter_name2).getY();
		int w0 = (*iter_name2).getWidth();
		int h0 = (*iter_name2).getHeight();
		int x1 = basket.getX();
		int y1 = basket.getY();
		int w1 = basket.getWidth();
		int h1 = basket.getHeight();
		if(x0 > x1 - w0 && x0 < x1 + w0 && y0 > y1 - h0 && y0 < y1 + h1) {
			(*iter_name2).onDestroy();
			if(iter_name2 != --listItemDrop.end())
			listItemDrop.erase(iter_name2++);
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

void GameScr::addNewAnimal(int type) {
	Animal animal = Animal(type, rand() % 400, rand() % 150, rand() % 3 + 1);
	listAnimal.push_back(animal);
}

void GameScr::onDestroy() {
	//basket.texture.texture = NULL;
}
