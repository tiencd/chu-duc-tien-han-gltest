package game.view;

import game.font.BitmapFont;
import game.framework.Game;
import game.framework.GameScreen;
import game.framework.Graphics;
import game.framework.Image;
import game.framework.Input.KeyEvent;
import game.framework.Input.TouchEvent;
import game.framework.impl.AndroidPixmap;
import game.object.Object;
import game.object.Animal;
import game.object.ItemDrop;
import game.util.Constrain;
import game.util.ImageResource;
import game.util.Utils;

import java.util.ArrayList;
import java.util.List;

import android.graphics.Color;

public class GameScr extends GameScreen {

	Object basket;
	List<Animal> listAnimal = new ArrayList<Animal>();
	List<ItemDrop> listItemDrop  = new ArrayList<ItemDrop>();
	Image textureEgg, textureShit;
	Image texturePause, texturePlay, textureBg;
	Image textureAddAnimal[] = new AndroidPixmap[Constrain.TOTAL_TYPE_ANIMAL];
	int level;
	int scoreEat;
	int scoreDropEggs, scoreEatShit;
	long timeDisplayText;

	int marginTop = 5, widthButton = 50, heightText = 22, marginTopAlterText = 5, marginRightAlterText = 100;
	int speedDrop = 2;
	int yImageAddAnimal1, xImageAddAnimal, distanceBetweenAddAnimal;

    public GameScr(Game game) {
		super(game);
		timeDisplayText = System.currentTimeMillis();
		setGameState(GAME_STATE.isFree);
		if(SCREEN_WIDTH <= 480) {
			heightText = 22;
			marginTopAlterText = 30;
		}
		marginRightAlterText = SCREEN_WIDTH - widthButton - 10;
    }
    
    public void onInit() {
    	setGameState(GAME_STATE.isFree);
    	level = 1;
    	speedDrop = 5;
    	yImageAddAnimal1 = SCREEN_HEIGHT - 250;
    	xImageAddAnimal = SCREEN_WIDTH - 80;
    	distanceBetweenAddAnimal = 80;
    	for (int i = 1; i <= textureAddAnimal.length; i++) {
    		textureAddAnimal[i-1] = ImageResource.getImage(Constrain.imgAddAnimal + i + ".png", 70, 70);
		}
    	textureBg = ImageResource.getImage(Constrain.imgBg, SCREEN_WIDTH, SCREEN_HEIGHT);
    	texturePause = ImageResource.getImage(Constrain.imgPause, widthButton, widthButton);
    	texturePlay = ImageResource.getImage(Constrain.imgPlay, widthButton, widthButton);
    	String strTmp = Constrain.imgItemDrop + (Constrain.ID_EGG_PNG) + ".png";
    	textureEgg = ImageResource.getImage(strTmp, 30, 33);
    	strTmp = Constrain.imgItemDrop + (Constrain.ID_SHIT_PNG) + ".png";
    	textureShit = ImageResource.getImage(strTmp, 30, 33);
    	scoreEat = 0;
    	scoreDropEggs = 0;
    	scoreEatShit = 0;
    	listAnimal.clear();
    	listItemDrop.clear();
    	basket = new Object();
    	basket.setImage(ImageResource.getImage(Constrain.imgBasket));
    	basket.setWidth(120);
    	basket.setHeight(100);
    	basket.setXY((SCREEN_WIDTH - basket.getWidth()) >> 1, SCREEN_HEIGHT - basket.getHeight() - 60);
    	basket.onMoveToX(basket.getX());
    }
	    
    public void paint(Graphics g) {
    	g.drawImage(textureBg, 0, 0, 0);

    	for (Animal iter_name : listAnimal) {
    		iter_name.onPaint(g);
		}

    	for (ItemDrop iter_name : listItemDrop) {
    		iter_name.onPaint(g);
		}
    	
    	if(isPause() || isGameOver() || isFree()) {
    		g.drawImage(texturePlay, SCREEN_WIDTH - widthButton, 0, 0);
    		long timeNow = System.currentTimeMillis();
    		if(timeNow - timeDisplayText <= 500) {
    			if(isPause()) {
    				BitmapFont.drawBoldFont(g, "CONTINUE", marginRightAlterText, marginTopAlterText, heightText, Color.argb(255,255,0,0), Graphics.RIGHT);
    			} else if(isGameOver()) {
    				BitmapFont.drawBoldFont(g, "PLAY AGAIN", marginRightAlterText, marginTopAlterText, heightText, Color.argb(255,255,0,0), Graphics.RIGHT);
    			}else if(isFree()) {
    				BitmapFont.drawBoldFont(g, "Touch on screen to start game", SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1, heightText, Color.argb(255,255,0,0), Graphics.VCENTER);
    			}
    		} else if(timeNow - timeDisplayText >= 1000) {
    			timeDisplayText = System.currentTimeMillis();
    		}
    	} else if(isPlaying()) {
    		g.drawImage(texturePause, SCREEN_WIDTH - widthButton, 0, 0);
    	}
    	BitmapFont.drawBoldFont(g, "Score:", 5, marginTop, heightText, Color.argb(255,0,0,0), 0);
//    	String strTmp = scoreEat + "";
    	BitmapFont.drawBoldFont(g, scoreEat + "", 80, marginTop, heightText, Color.argb(255,50,2,255), 0);
    	// paint score drop egg
    	g.drawImage(textureEgg, 130, marginTop, 0);
    	BitmapFont.drawBoldFont(g, scoreDropEggs + "", 163, marginTop, heightText, Color.argb(255,255,2,62), 0);
    	// paint score eat shit
    	g.drawImage(textureShit, 200, marginTop, 0);
    	BitmapFont.drawBoldFont(g, scoreEatShit + "", 230, marginTop, heightText, Color.argb(255,255,2,62), 0);
    	BitmapFont.drawBoldFont(g, "Level", 255, marginTop, heightText, Color.argb(255,0,0,0), 0);
    	BitmapFont.drawBoldFont(g, (level) + "", 320, marginTop, heightText, Color.argb(255,50,2,255), 0);
    	
    	for (int i = 0; i < textureAddAnimal.length; i++) {
			g.drawImage(textureAddAnimal[i], xImageAddAnimal, yImageAddAnimal1 - i * distanceBetweenAddAnimal,
					Graphics.BOTTOM);
		}
    	
    	basket.onPaint(g);
    	
		if(isGameOver()) {
			g.setColor(0xff000000);
			g.fillRoundRect((SCREEN_WIDTH - 450) >> 1, (SCREEN_HEIGHT - 200) >> 1, 450, 200, 15, 15, 130);
			BitmapFont.drawBoldFont(g, "GAME OVER", SCREEN_WIDTH >> 1, (SCREEN_HEIGHT - (heightText * 4)) >> 1, heightText + 4, Color.argb(255,255,0,0), Graphics.VCENTER);
			BitmapFont.drawBoldFont(g, "Your score: " + scoreEat, SCREEN_WIDTH >> 1, (SCREEN_HEIGHT - (heightText)) >> 1, heightText + 4, "#ffffff", Graphics.VCENTER);
//			BitmapFont.drawBoldFont(g, "Touch on screen to play again", SCREEN_WIDTH >> 1, (SCREEN_HEIGHT + (heightText << 1)) >> 1, heightText, "#ffffff", Graphics.VCENTER);
			
		}

    }


    public void update() {
		try {
			List<TouchEvent> touchEvents = game.getInput().getTouchEvents();
			int len = touchEvents.size();
			for (int i = 0; i < len; i++) {
				TouchEvent event = touchEvents.get(i);
				if (event.type == TouchEvent.TOUCH_DOWN) {
					pointerPressed(event.x, event.y);
				}
				if (event.type == TouchEvent.TOUCH_DRAGGED) {
					pointerDragged(event.x, event.y);
				}
				if (event.type == TouchEvent.TOUCH_UP) {
					pointerReleased(event.x, event.y);
				}
			}

			List<KeyEvent> keyEvents = game.getInput().getKeyEvents();

			for (int i = 0; i < keyEvents.size(); i++) {
				KeyEvent keyEvent = keyEvents.get(i);
				if (keyEvent.type == keyEvent.KEY_DOWN) {

				}
				if (keyEvent.type == keyEvent.KEY_UP) {

				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		if(isPlaying()) {
			basket.onUpdate();
			for (Animal iter_name : listAnimal) {
				(iter_name).onUpdate();
				if((iter_name).onPorm()) {
					int type = Utils.getRandom(0, 10) % 2;
					ItemDrop itemDrop = new ItemDrop(type + 1, 
						(iter_name).getX() +(iter_name).getWidth() / 2, 
						(iter_name).getY() + (iter_name).getHeight() / 2, speedDrop);

					listItemDrop.add(itemDrop);
				}
			}
			for (ItemDrop iter_name : listItemDrop) {
				(iter_name).onUpdate();
			}
			
			onCheckEat();
		}
	}

	boolean onCheckGameOver() {
	
		if(scoreDropEggs >= Constrain.TOTAL_MAX_DROP_EDD || scoreEatShit >= Constrain.TOTAL_MAX_EAT_SHIT) {
			gameOver();
			return true;
		}
		return false;
	}
	
	void onCheckEat() {
		for (int i = 0; i < listItemDrop.size(); i++) {
			ItemDrop iter_name2 = listItemDrop.get(i);
			if((iter_name2).getY() >= SCREEN_HEIGHT) {
				(iter_name2).onDestroy();
				if((iter_name2).getTypeItem() == Constrain.ID_EGG_PNG) {
					scoreDropEggs ++;
					if(onCheckGameOver()) {
						gameOver();
					}
				}
				listItemDrop.remove(i);
				i--;
			} else {
				int x0 = (iter_name2).getX();
				int y0 = (iter_name2).getY();
				int w0 = (iter_name2).getWidth();
				int h0 = (iter_name2).getHeight();
				int x1 = basket.getX();
				int y1 = basket.getY();
				int w1 = basket.getWidth();
				int h1 = basket.getHeight();
				if(x0 + w0> x1 + 20 && x0 + 30 < x1 + w1 && y0 + h0 > y1 + 40 && y0 + 60 < y1 + h1) {
					// la trứng thì cộng điểm
					if((iter_name2).getTypeItem() == Constrain.ID_EGG_PNG) {
						scoreEat ++;
						if(scoreEat % Constrain.NUM_EGG_EAT_NEXT_LEVEL == 0) {
							speedDrop += 3;
							level ++;
						}
					} else {
						scoreEatShit ++;
						if(onCheckGameOver()) {
							gameOver();
						}
					}
					listItemDrop.remove(i);
					i--;
				}
			}
		}
	}

	void doChangeStateGame() {
		if(isPause()) {
			resume();
		} else if(isPlaying()) {
			pause();
		} else if(isGameOver() || isFree()) {
			start();
		}
	}
	
	public void addNewAnimal(int type) {
		Animal animal = new Animal(type, Utils.getRandom(0, GameScreen.SCREEN_WIDTH - 100), Utils.getRandom(50, 150));
		listAnimal.add(animal);
	}
	
	void onResetData() {
		setGameState(GAME_STATE.isFree);
		level = 1;
		speedDrop = 5;
		scoreEat = 0;
		scoreDropEggs = 0;
		scoreEatShit = 0;
		listAnimal.clear();
		listItemDrop.clear();
	}

	public void start() {
		onResetData();
		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
//		addNewAnimal(Utils.getRandom(0, 100)%Constrain.TOTAL_TYPE_ANIMAL + 1);
		super.start();
	}


    protected void pointerDragged(int x, int y) {
    	if(y > 200) {
    		basket.onMoveToX(x);
    	}
    }

    protected void pointerPressed(int x, int y) {
    	if(isFree() || isGameOver()) {
    		start();
    	} else if(isPlaying()) {
    		if(x > SCREEN_WIDTH - widthButton - 5 && x < SCREEN_WIDTH && y < widthButton + 5) {
    			pause();
    		} else {
    			for (int i = 0; i < textureAddAnimal.length; i++) {
    				if(x > xImageAddAnimal && x < SCREEN_WIDTH 
    						&& y > (yImageAddAnimal1 - (i+1) * distanceBetweenAddAnimal) 
    						&&  y <  (yImageAddAnimal1 - i * distanceBetweenAddAnimal)) {
    					addNewAnimal(i + 1);
    				}
    			}
    		}
    	} else if(isPause()) {
    		if(x > SCREEN_WIDTH - widthButton - 5 && x < SCREEN_WIDTH && y < widthButton + 5) {
    			resume();
    		}
    	}
    }

    protected void pointerReleased(int x, int y) {

    }

	@Override
	public void gameOver() {
		super.gameOver();
	}

	@Override
	public void pause() {
		super.pause();
	}

	@Override
	public void resume() {
		super.resume();
	}

	@Override
	public void dispose() {
		
	}
}
