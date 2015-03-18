package game.object;

import game.framework.Graphics;
import game.util.Constrain;
import game.util.ImageResource;

public class ItemDrop extends Object {
	
	public ItemDrop(int type, int x, int y) {
		super(type, x, y);
	}
	
	public ItemDrop(int type, int x, int y, int speed) {
		super(type, x, y, speed);
		w = getImage().getWidth();
		h = getImage().getHeight();
	}

	public ItemDrop(int type, int x, int y, int w, int h) {
		super(type, x, y, w, h);
	}
	
	public ItemDrop(int type, int x, int y, int w, int h, int speed) {
		super(type, x, y, w, h, speed);
	}
	
	public void setTypeItem(int typeItem) {
		super.setTypeItem(typeItem);
		String strImage = Constrain.imgItemDrop + typeItem + ".png";
		setImage(ImageResource.getImage(strImage));
	}

	public void onPaint(Graphics g) {
		g.drawImage(getImage(), x, y, Graphics.LEFT);
	}

	@Override
	public void onUpdate() {
		y += speed;
	}

	@Override
	public void onDestroy() {
		
	}

}
