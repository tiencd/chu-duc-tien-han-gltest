package game.framework;

import android.graphics.Paint;

public interface Graphics {
    public static final int SOLID = 0;
    public static final int DOTTED = 1;
    public static final int HCENTER = 1;
    public static final int TOP = 16;
    public static final int VCENTER = 2;
    public static final int BOTTOM = 32;
    public static final int LEFT = 4;
    public static final int BASELINE = 64;
    public static final int RIGHT = 8;
    
    public static enum PixmapFormat {
        ARGB8888, ARGB4444, RGB565
    }

    public Image newPixmap(String fileName, PixmapFormat format);
    
    public Image newPixmap(String fileName);
    
    public Image newPixmap(int width,int height);
    
    public void translate(int x, int y);
    
    public void setClip(int x, int y, int width ,int height);
    
    public int getColor();
    
    public void clear(int color);

    public void drawPixel(int x, int y, int color);
    
    public void drawLine(int x, int y, int x2, int y2);

    public void drawRect(int x, int y, int width, int height);

    public void fillRect(int l, int t, int w, int h);

    public void fillRect(int l, int t, int w, int h, int alpha);
    
    public void drawRegion(Image image,int srcX, int srcY,
            int srcWidth, int srcHeight, int x, int y);

//    public void drawRegion(Image image, int srcX, int srcY, int srcWidth,int srcHeight, int sprite, int x, int y);
    
    public void drawRegion(Image image, int srcX, int srcY, int srcWidth,int srcHeight, int trans, int x, int y,int anchors);

    public void drawText(String text, float x, float y, Paint paint,int anchors);
//    public void drawText(String text, float x, float y, int color, String fontType);
    
    public void drawImage(Image image, int x, int y, int anchors);

    public void drawImage(Image pixmap, int x, int y, int w, int h, int anchors);
    
    public int getWidth();

    public int getHeight();

	public void setColor(int color);
	
	public void setColor(String color);

	public void fillArc(int tmpX, int tmpY, int i, int j, int k, int l);

	public float getTranslateX();

	public float getTranslateY();

	public void translate(float f, float g);

	public void fillRoundRect(int x, int y, int w, int h, int arcWidth, int arcHeigth);

	public void fillRoundRect(int x, int y, int w, int h, int arcWidth, int arcHeigth, int alpha);

	public void drawRoundRect(int x,int y,int width,int height,int arcWidth,int arcHeigth);
		
	public void setColor(int i, int j, int k);

}
