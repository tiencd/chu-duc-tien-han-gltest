package game.util;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import game.framework.Image;
import game.framework.impl.AndroidGame;
import game.framework.impl.AndroidPixmap;

public class ImageResource {
	static Map<String, Image> listImage = new HashMap<String, Image>();
	public static Image getImage(String imageName) {
		if(listImage.containsKey(imageName)) {
			return listImage.get(imageName);
		} else {
			try {
				InputStream inputStream = AndroidGame.game.getFileIO().readAsset(imageName);
				Image image = new AndroidPixmap(BitmapFactory.decodeStream(inputStream));
				listImage.put(imageName, image);
				return image;
			} catch (IOException e) {
				e.printStackTrace();
			}
			return null;
		}
	}

	public static Image getImage(String imageName, int w, int h) {
		if(listImage.containsKey(imageName)) {
			return listImage.get(imageName);
		} else {
			try {
				InputStream inputStream = AndroidGame.game.getFileIO().readAsset(imageName);
				Image image = new AndroidPixmap(BitmapFactory.decodeStream(inputStream));
				listImage.put(imageName, image);
				
				int width = image.getPixmap().getWidth();
			    int height = image.getPixmap().getHeight();
			    float scaleWidth = ((float) w) / width;
			    float scaleHeight = ((float) h) / height;
			    // create a matrix for the manipulation
			    Matrix matrix = new Matrix();
			    // resize the bit map
			    matrix.postScale(scaleWidth, scaleHeight);
			    // recreate the new Bitmap
			    Bitmap resizedBitmap = Bitmap.createBitmap(image.getPixmap(), 0, 0, width, height, matrix, false);
			    
				return new AndroidPixmap(resizedBitmap);
			} catch (IOException e) {
				e.printStackTrace();
			}
			return null;
		}
	}
}
