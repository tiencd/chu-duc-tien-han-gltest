package game.object;

import game.framework.Graphics;
import game.framework.impl.AndroidGame;
import game.util.Constrain;
import game.util.ImageResource;
import game.util.Utils;

public class Animal extends Object {
	
	public Animal(int type, int x, int y) {
		isGoUp = Utils.getRandom()%2 == 0 ? true : false;
		isGoLeft = Utils.getRandom()%2 == 0 ? true : false;
		setTypeItem(type);
		setXY(x, y);
		speed = Utils.getRandom(0, 4);
		speedUp = Utils.getRandom(0, 3);
		timeChangeAnimation = timeSeconds = System.currentTimeMillis();
		w = getImage().getWidth();
		h = getImage().getHeight();
	}

	public Animal(int type, int x, int y, int speed) {
		super(type, x, y, speed);
	}

	public Animal(int type, int x, int y, int w, int h) {
		super(type, x, y, w, h);
	}
	
	public Animal(int type, int x, int y, int w, int h, int speed) {
		super(type, x, y, w, h, speed);
	}
	
	public void setTypeItem(int type) {
		super.setTypeItem(typeItem);
		String strImage = Constrain.imgAnimal + type + ".png";
		setImage(ImageResource.getImage(strImage));
	}


	public void onPaint(Graphics g) {
		g.drawImage(getImage(), x, y, Graphics.LEFT);
	}
	
	public void onUpdate() {
		if(System.currentTimeMillis() - timeChangeAnimation > Utils.getRandom(1000, 2000) + 2000) {
			timeChangeAnimation = System.currentTimeMillis();
			int ran = Utils.getRandom(0, 100) % 4;
			if(ran > 0) {
				speed = Utils.getRandom(5, 10);
				speedUp = Utils.getRandom(5, 10) % 3;
				isGoLeft = Utils.getRandom()%2 == 0 ? true : false;
				isGoUp = Utils.getRandom()%2 == 0 ? true : false;
			}
		}
		if(isGoLeft) {
			if(x <= 0) {
				x = 0;
				isGoLeft = false;
			} else {
				x -= speed;
			}
		} else {
			if(x >= AndroidGame.widthScreen - getWidth()) {
				isGoLeft = true;
			} else {
				x += speed;
			}
		}
		
		if(isGoUp) {
			if(y <= 30) {
				y = 30;
				isGoUp = false;
			} else {
				y -= speedUp;
			}
		} else {
			if(y >= 200) {
				isGoUp = true;
			} else {
				y += speedUp;
			}
		}
		
	}

	public boolean onPorm() {
		long timeSeconds = System.currentTimeMillis();
		if(timeSeconds - this.timeSeconds >= Constrain.TIME_ANIMAL_PORN * 1000) {
			this.timeSeconds = timeSeconds;
			return true;
		}
		return false;
	}


	@Override
	public void onDestroy() {
		
	}

}
