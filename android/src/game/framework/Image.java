package game.framework;

import game.framework.Graphics.PixmapFormat;
import android.graphics.Bitmap;

public interface Image {
		
    public int getWidth();

    public int getHeight();

    public PixmapFormat getFormat();
    
    public Bitmap getPixmap();

    public void setPixmap(Bitmap mBitmap);
    
    public Graphics getGraphics();
    
    public void dispose();
}
