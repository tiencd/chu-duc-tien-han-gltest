#include "GameScr.h"
#include <string>

using namespace std;

GameScr::GameScr()
{
	timeDisplayText = Utils::getTimeNow();
}

int marginTop = 5, widthButton = 80, heightText = 20;
//toa do x, y, do cao - do rong, khoang cach giua cac image them dong vat moi
int xImageAddAnimal, yImageAddAnimal1, heightImageAddAnimal1, distanceBetweenAddAnimal;

int GameScr::onInit() {
	dem = 0;
	gameState = isFree;
	level = 2;
    yImageAddAnimal1 = SCREEN_HEIGHT - 250;
    xImageAddAnimal = SCREEN_WIDTH - 80;
    distanceBetweenAddAnimal = 80;
	heightImageAddAnimal1 = 70;
	for (int i = 1; i <= TOTAL_TYPE_ANIMAL; i++) {
		string strTmp = imgAddAnimal + to_string(i) + ".png";
		char *str =(char *)strTmp.c_str();
    	textureAddAnimal[i-1].Init(str, heightImageAddAnimal1, heightImageAddAnimal1);
	}
	if(!textureBg.Init(imgBg, 0, 0))
		return FALSE;
	if(!texturePause.Init(imgPause, widthButton, widthButton))
		return FALSE;
	if(!texturePlay.Init(imgPlay, widthButton, widthButton))
		return FALSE;
	string strTmp = imgItemDrop + to_string(ID_EGG_PNG) + ".png";
	char *str =(char *)strTmp.c_str();
	if(!textureEgg.Init(str, 25, 27))
		return FALSE;

	strTmp = imgItemDrop + to_string(ID_SHIT_PNG) + ".png";
	char *str1 =(char *)strTmp.c_str();
	if(!textureShit.Init(str1, 30, 30))
		return FALSE;

	scoreEat = 0;
	scoreDropEggs = 0;
	scoreEatShit = 0;
	listAnimal.clear();
	listItemDrop.clear();
	basket = Object();
	basket.setTexture(imgBasket, 120, 100);
	basket.setXY((SCREEN_WIDTH - basket.getWidth()) >> 1, SCREEN_HEIGHT - basket.getHeight() - 40);
	return TRUE;
}

void GameScr::onPaint() {
	// paint score
	textureBg.Blit(0,0);
	if(gameState == isPause || gameState == isGameOver || gameState == isFree) {
		texturePlay.Blit(SCREEN_WIDTH - widthButton, 0);
		long timeNow = Utils::getTimeNow();
		if(timeNow - timeDisplayText <= 500) {
			if(gameState == isPause) {
				DrawString("CONTINUE", 450, marginTop + 3, 150, heightText, D3DCOLOR_ARGB(255,255,0,0));
			} else if(gameState == isGameOver) {
				DrawString("PLAY AGAIN", 430, marginTop + 3, 150, heightText, D3DCOLOR_ARGB(255,255,0,0));
			}else if(gameState == isFree) {
				DrawString("Click to start game", 360, marginTop, 150, heightText, D3DCOLOR_ARGB(255,255,0,0));
			}
		} else if(timeNow - timeDisplayText >= 1000) {
			timeDisplayText = Utils::getTimeNow();
		}
		if(dem >= 60) dem = 0;
	} else if(gameState == isPlaying) {
		texturePause.Blit(SCREEN_WIDTH - widthButton, 0);
	}
	DrawString("Score:", 5, marginTop, 70, heightText, D3DCOLOR_ARGB(255,0,0,0));
	string strTmp = to_string(scoreEat) + "";
	char* sScore = (char *)strTmp.c_str();
	DrawString(sScore, 73, marginTop, 50, heightText, D3DCOLOR_ARGB(255,50,2,255));
	// paint score drop egg
	textureEgg.Blit(130, marginTop);
	strTmp = to_string(scoreDropEggs) + "";
	char* sScore1 = (char *)strTmp.c_str();
	DrawString(sScore1, 160, marginTop, 30, heightText, D3DCOLOR_ARGB(255,255,2,62));
	// paint score eat shit
	textureShit.Blit(200, marginTop);
	strTmp = to_string(scoreEatShit) + "";
	char* sScore2 = (char *)strTmp.c_str();
	DrawString(sScore2, 230, marginTop, 30, heightText, D3DCOLOR_ARGB(255,255,2,62));
	DrawString("Level", 255, marginTop, 70, heightText, D3DCOLOR_ARGB(255,0,0,0));
	strTmp = to_string(level-1) + "";
	char* sScore3 = (char *)strTmp.c_str();
	DrawString(sScore3, 320, marginTop, 50, heightText, D3DCOLOR_ARGB(255,50,2,255));

	list<Animal>::iterator iter_name; // Khai báo con trỏ để duyệt
	for (iter_name = listAnimal.begin(); iter_name != listAnimal.end(); iter_name++) {
		(*iter_name).onPaint();
	}

	list<ItemDrop>::iterator iter_name2; // Khai báo con trỏ để duyệt
	for (iter_name2 = listItemDrop.begin(); iter_name2 != listItemDrop.end(); iter_name2++) {
		(*iter_name2).onPaint();
	}
	for (int i = 0; i < TOTAL_TYPE_ANIMAL; i++) {
		textureAddAnimal[i].Blit(xImageAddAnimal, yImageAddAnimal1 - i * distanceBetweenAddAnimal);
	}

	basket.onPaint();
}

void GameScr::onUpdate() {
	if(gameState == isPlaying) {
		if(KEY_LEFT_DOWN) {
				int xOlder = basket.getX();
				if(xOlder > 0) {
					basket.setX(xOlder - 10);
				}
		} else if(KEY_RIGHT_DOWN) {
				int xOlder = basket.getX();
				if(xOlder < (SCREEN_WIDTH - basket.getWidth())) {
					basket.setX(xOlder + 10);
				}
		} 
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
		}
		
		onCheckEat();
	}
}

bool GameScr::onCheckGameOver() {

	if(scoreDropEggs >= TOTAL_MAX_DROP_EDD || scoreEatShit >= TOTAL_MAX_EAT_SHIT) {
		onGameOver();
		return true;
	}
	return false;
}

void GameScr::onCheckEat() {
	list<ItemDrop>::iterator iter_name2;
	// xóa những vật chạy quá màn hình
	for (iter_name2 = listItemDrop.begin(); iter_name2 != listItemDrop.end(); iter_name2++) {
		if((*iter_name2).getY() >= SCREEN_HEIGHT) {
			(*iter_name2).onDestroy();
			if((*iter_name2).getTypeItem() == ID_EGG_PNG) {
				scoreDropEggs ++;
			}
			if(iter_name2 != --listItemDrop.end()) {
				listItemDrop.erase(iter_name2++);
			} else {
				listItemDrop.erase(iter_name2);
				break;
			}
		}
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
		if(x0 + w0> x1 + 20 && x0 + 40 < x1 + w1 && y0 + h0 > y1 + 40 && y0 + 60 < y1 + h1) {
			// la trứng thì cộng điểm
			if((*iter_name2).getTypeItem() == ID_EGG_PNG) {
				scoreEat ++;
				if(scoreEat % NUM_EGG_EAT_NEXT_LEVEL == 0) {
					level++;
				}
			} else {
				scoreEatShit ++;
			}
			(*iter_name2).onDestroy();
			if(iter_name2 != --listItemDrop.end()) {
				listItemDrop.erase(iter_name2++);
			} else {
				listItemDrop.erase(iter_name2);
				break;
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
	case WM_KEYUP:
		resetKeyboard();
		break;
	case WM_KEYDOWN:
		{
			switch (wParam) {
			case VK_LEFT:
				KEY_LEFT_DOWN = true;
				// cout << basket.getX();
				break;
			case VK_RIGHT:
				KEY_RIGHT_DOWN = true;
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
				doChangeStateGame();
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
		if(gameState == isGameOver || gameState == isFree) {
			onStart();
		}
		break;	

	case WM_LBUTTONUP:
		//Get mouse coords
		coords = MAKEPOINTS (lParam);
		if(coords.x > (SCREEN_WIDTH - widthButton) && coords.x < SCREEN_WIDTH &&
			coords.y > 0 && coords.y < widthButton) {
				doChangeStateGame();
		} else {
			if(gameState == isPlaying) {
				for (int i = 0; i < TOTAL_TYPE_ANIMAL; i++) {
					/*int y1 = yImageAddAnimal1 - (i * distanceBetweenAddAnimal);
					int y2 = y1 + heightImageAddAnimal1;*/
    				if(coords.x > xImageAddAnimal && coords.x < SCREEN_WIDTH 
    						&& coords.y > (yImageAddAnimal1 - (i * distanceBetweenAddAnimal)) 
    						&&  coords.y <  (yImageAddAnimal1 - i * distanceBetweenAddAnimal + heightImageAddAnimal1)) {
    					addNewAnimal(i + 1);
    				}
    			}
			}
		}
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

void GameScr::doChangeStateGame() {
	dem = 0;
	if(gameState == isPause) {
		onResume();
	} else if(gameState == isPlaying) {
		onPause();
	} else if(gameState == isGameOver || gameState == isFree) {
		onStart();
	}
}

void GameScr::addNewAnimal(int type) {
	Animal animal = Animal(type, rand() % SCREEN_WIDTH - 80, rand() % 100 + 30);
	listAnimal.push_back(animal);
}

void GameScr::onResetData() {
	dem = 0;
	gameState = isFree;
	level = 2;
	scoreEat = 0;
	scoreDropEggs = 0;
	scoreEatShit = 0;
	listAnimal.clear();
	listItemDrop.clear();
}

void GameScr::onStart() {
	onResetData();
	addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);
	addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);
	addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);
	addNewAnimal(rand()%TOTAL_TYPE_ANIMAL + 1);
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
		string strTmp = "Your score: " + to_string(scoreEat) + "\nPress the space key or on click the game screen to play again";
		char * str = (char *)strTmp.c_str();
		MessageBox(NULL, str, "Game over", MB_OK);
		super::onGameOver();
	}
}

void GameScr::onDestroy() {
	//basket.texture.texture = NULL;
}
