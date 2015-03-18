package game.framework.impl;

import game.framework.Graphics;
import game.framework.Image;
import game.framework.Graphics.PixmapFormat;
import game.view.GameScr;

import java.io.ByteArrayInputStream;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;

public class AndroidPixmap implements Image {
    Bitmap bitmap;
    PixmapFormat format;
    
    public AndroidPixmap(Bitmap bitmap, PixmapFormat format) {
        this.bitmap = bitmap;
        this.format = format;
    }
    
    public AndroidPixmap(Bitmap bitmap) {
        this.bitmap = bitmap;
    }
    
    public AndroidPixmap(int width,int height){
    	this.bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
    	this.format = PixmapFormat.ARGB8888;
    }
    
    public AndroidPixmap(byte[] data){
    	ByteArrayInputStream in = new ByteArrayInputStream(data);
    	this.bitmap = BitmapFactory.decodeStream(in);
    	this.format = PixmapFormat.ARGB8888;
    }
    
    @Override
    public int getWidth() {
        return bitmap.getWidth();
    }

    @Override
    public int getHeight() {
        return bitmap.getHeight();
    }

    @Override
    public PixmapFormat getFormat() {
        return format;
    }

    @Override
    public void dispose() {
        bitmap.recycle();
    }

	@Override
	public Bitmap getPixmap() {
		// TODO Auto-generated method stub
		return this.bitmap;
	}
	
	@Override
	public void setPixmap(Bitmap mBitmap) {
		// TODO Auto-generated method stub
		this.bitmap =  mBitmap;
	}
	
	public static Image createImage(int width, int height) {
		Image img = new AndroidPixmap(width, height);
		return img;
	}

	public static Image createImage(byte[] imageData, int imageOffset, int imageLength) {
		Bitmap bmp;
		bmp = BitmapFactory.decodeByteArray(imageData, imageOffset, imageLength);
		return new AndroidPixmap(bmp);
	}

	public Bitmap getResizedBitmap(Bitmap bm, int newHeight, int newWidth)
	{
	    int width = bm.getWidth();
	    int height = bm.getHeight();
	    float scaleWidth = ((float) newWidth) / width;
	    float scaleHeight = ((float) newHeight) / height;
	    // create a matrix for the manipulation
	    Matrix matrix = new Matrix();
	    // resize the bit map
	    matrix.postScale(scaleWidth, scaleHeight);
	    // recreate the new Bitmap
	    Bitmap resizedBitmap = Bitmap.createBitmap(bm, 0, 0, width, height, matrix, false);
	    return resizedBitmap;
	}
	
	public Graphics getGraphics() {
		return new AndroidGraphics(bitmap);
	}
}
