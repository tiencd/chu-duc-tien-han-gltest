package game.object;

import game.framework.GameScreen;
import game.framework.Graphics;
import game.framework.Image;
import game.util.Constrain;

public class Object {
	
	protected int x, y, w, h, xT, yT;
	protected int speed, speedUp;
	private Image image;
	protected int typeItem;
	protected boolean isGoLeft, isGoUp;
	protected long timeChangeAnimation;
	protected long timeSeconds;

	public Object() {
		
	}

	public Object(int type, int x, int y) {
		setX(x);
		setY(y);
		xT = x; yT = y;
		setTypeItem(type);
	}
	
	public Object(int type, int x, int y, int speed) {
		setX(x);
		setY(y);
		setSpeed(speed);
		setTypeItem(type);
	}

	public Object(int type, int x, int y, int w, int h) {
		setX(x);
		setY(y);
		setWidth(w);
		setHeight(h);
		setTypeItem(type);
	}
	
	public Object(int type, int x, int y, int w, int h, int speed) {
		setX(x);
		setY(y);
		setWidth(w);
		setHeight(h);
		setSpeed(speed);
		setTypeItem(type);
	}

	public void onPaint(Graphics g) {
		g.drawImage(image, x, y, w, h, Graphics.LEFT);
	}
	
	public void onUpdate() {
		if(x != xT) {
			if(xT > x + Constrain.SPEED_BASKET) {
				x += Constrain.SPEED_BASKET;
			} else if(xT < x - Constrain.SPEED_BASKET) {
				x -= Constrain.SPEED_BASKET;
			} else {
				x = xT;
			}
		}
	}
	
	public void onDestroy() {
		
	}
	
	public void onMoveToX(int xTo) {
		if(xTo >= GameScreen.SCREEN_WIDTH - w) {
			xT = GameScreen.SCREEN_WIDTH - w;
		} else {
			xT = xTo;
		}
	}

	public void setWidth(int width) {
		w = width;
	}
	public void setHeight(int height) {
		h = height;
	}

	public int getWidth() {
		return w;
	}
	
	public int getHeight() {
		return h;
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void setY(int y) {
		this.y = y;
	}

	public void setXY(int x, int y) {
		this.x = x;
		this.y = y;
	}

	public int getSpeed() {
		return speed;
	}

	public void setSpeed(int speed) {
		this.speed = speed;
	}

	public int getSpeedUp() {
		return speedUp;
	}

	public void setSpeedUp(int speedUp) {
		this.speedUp = speedUp;
	}

	public Image getImage() {
		return image;
	}

	public void setImage(Image image) {
		this.image = image;
	}

	public int getTypeItem() {
		return typeItem;
	}

	public void setTypeItem(int typeItem) {
		this.typeItem = typeItem;
	}
	
}
