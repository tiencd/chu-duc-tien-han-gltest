package game.framework.impl;

import game.font.BitmapFont;
import game.framework.Graphics;
import game.framework.Image;
import game.view.GameScr;

import java.io.IOException;
import java.io.InputStream;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.graphics.Paint.Style;
import android.graphics.Rect;
import android.graphics.RectF;

public class AndroidGraphics implements Graphics {

	AssetManager assets;
	Bitmap frameBuffer;
	Canvas canvas;
	Paint paint;
	Rect srcRect = new Rect();
	Rect dstRect = new Rect();
	private Rect clip;
	int color;

	public AndroidGraphics(AssetManager assets, Bitmap frameBuffer) {
		this.assets = assets;
		this.frameBuffer = frameBuffer;
		this.canvas = new Canvas(frameBuffer);
		// this.canvas.clipRect(0, 0, frameBuffer.getWidth(),
		// frameBuffer.getHeight());
		this.paint = new Paint();
		this.clip = canvas.getClipBounds();
		this.canvas.save(Canvas.CLIP_SAVE_FLAG);
	}

	public AndroidGraphics(Bitmap frameBuffer) {
		// this.assets = assets;
		this.frameBuffer = frameBuffer;
		this.canvas = new Canvas(frameBuffer);
		this.paint = new Paint();
		// this.canvas.clipRect(0, 0, frameBuffer.getWidth(),
		// frameBuffer.getHeight());
		this.clip = canvas.getClipBounds();
		this.canvas.save(Canvas.CLIP_SAVE_FLAG);
	}

	@Override
	public Image newPixmap(String fileName, PixmapFormat format) {
		Config config = null;
		if (format == PixmapFormat.RGB565)
			config = Config.RGB_565;
		else if (format == PixmapFormat.ARGB4444)
			config = Config.ARGB_4444;
		else
			config = Config.ARGB_8888;

		Options options = new Options();
		options.inPreferredConfig = config;

		InputStream in = null;
		Bitmap bitmap = null;
		try {
			in = assets.open(fileName);
			bitmap = BitmapFactory.decodeStream(in);
			if (bitmap == null)
				throw new RuntimeException("Couldn't load bitmap from asset '"
						+ fileName + "'");
		} catch (IOException e) {
			throw new RuntimeException("Couldn't load bitmap from asset '"
					+ fileName + "'");
		} finally {
			if (in != null) {
				try {
					in.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}

		if (bitmap.getConfig() == Config.RGB_565)
			format = PixmapFormat.RGB565;
		else if (bitmap.getConfig() == Config.ARGB_4444)
			format = PixmapFormat.ARGB4444;
		else
			format = PixmapFormat.ARGB8888;

		return new AndroidPixmap(bitmap, format);
	}

	@Override
	public Image newPixmap(String fileName) {

		InputStream in = null;
		Bitmap bitmap = null;
		try {
			in = assets.open(fileName);
			bitmap = BitmapFactory.decodeStream(in);
			if (bitmap == null)
				throw new RuntimeException("Couldn't load bitmap from asset '"
						+ fileName + "'");
		} catch (IOException e) {
			throw new RuntimeException("Couldn't load bitmap from asset '"
					+ fileName + "'");
		} finally {
			if (in != null) {
				try {
					in.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}

		return new AndroidPixmap(bitmap, PixmapFormat.ARGB8888);
	}

	@Override
	public Image newPixmap(int width, int height) {

		Bitmap bitmap = Bitmap.createBitmap(width, height,
				Bitmap.Config.ARGB_8888);

		return new AndroidPixmap(bitmap);
	}

	@Override
	public int getColor() {
		return this.color;
	}

	@Override
	public void setColor(int color) {
		this.color = color;
	}

	public void setColor(int i, int j, int k) {
		this.color = Color.rgb(i, j, k);
	}
	
	public void setColor(String color) {
		this.color = Color.parseColor(color.replace("0x","#")); //Integer.parseInt(color.replace("0x",""), 16);
	}
	
	@Override
	public void clear(int color) {
		canvas.drawRGB((color & 0xff0000) >> 16, (color & 0xff00) >> 8,
				(color & 0xff));
	}

	@Override
	public void drawPixel(int x, int y, int color) {
		paint.setColor(color);
		canvas.drawPoint(x, y, paint);
	}
	
	@Override
	public void drawLine(int x, int y, int x2, int y2) {
		paint.setColor(this.color);
		canvas.drawLine(x, y, x2, y2, paint);
		// canvas.scale(sx, sy, px, py)
	}

	@Override
	public void drawRect(int x, int y, int width, int height) {
		paint.setColor(this.color);
		paint.setStyle(Style.STROKE);
		canvas.drawRect(x, y, x + width, y + height, paint);
	}

	@Override
	public void fillRect(int l, int t, int w, int h) {
		paint.setColor(this.color);
		paint.setStyle(Style.FILL);
		canvas.drawRect(l, t, l + w, t + h, paint);
	}

	@Override
	public void fillRect(int l, int t, int w, int h, int alpha) {
		paint.setColor(this.color);
		paint.setStyle(Style.FILL);
		paint.setAlpha(alpha);
		canvas.drawRect(l, t, l + w, t + h, paint);
	}

	@Override
	public void drawRegion(Image pixmap, int srcX, int srcY, int srcWidth,
			int srcHeight, int x, int y) {
		// srcRect: khung hình lấy ảnh con từ ảnh gốc
		try {
			srcRect.left = srcX;
			srcRect.top = srcY;
			srcRect.right = srcX + srcWidth;
			srcRect.bottom = srcY + srcHeight;
			// dstRect: khung hiển thị ảnh
			dstRect.left = x;
			dstRect.top = y;
			dstRect.right = x + srcWidth;
			dstRect.bottom = y + srcHeight;

				canvas.drawBitmap(((AndroidPixmap) pixmap).bitmap, srcRect,
						dstRect, null);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void drawRegion(Image pixmap, int srcX, int srcY, int srcWidth,
			int srcHeight, int sprite, int x, int y, int anchors) {
		try {

			// RectF src = new RectF(srcX, srcY, srcX + srcWidth - 1, srcY +
			// srcHeight - 1);
			// RectF dst = new RectF(x, y, x + srcWidth - 1, y + srcHeight - 1);

			Matrix matrix = new Matrix();
			switch (sprite) {
			case Sprite.TRANS_NONE:
				break;
			case Sprite.TRANS_MIRROR_ROT180:
				matrix.postRotate(180.0f);
				matrix.setScale(-1, 1);
				break;
			case Sprite.TRANS_MIRROR:
				matrix.setScale(-1, 1);
				break;
			case Sprite.TRANS_ROT180:
				matrix.postRotate(180.0f);
				break;
			case Sprite.TRANS_MIRROR_ROT270:
				matrix.setScale(-1, 1);
				matrix.postTranslate(x, y);
				matrix.postRotate(270.0f);
				break;
			case Sprite.TRANS_ROT90:
				matrix.postRotate(90.0f);
				break;
			case Sprite.TRANS_ROT270:
				matrix.postRotate(270.0f);
				break;
			case Sprite.TRANS_MIRROR_ROT90:
				matrix.setScale(-1, 1);
				matrix.postTranslate(x, y);
				matrix.postRotate(90.0f);
				break;
			}

			// begin modify
			// matrix.postScale(0.8f,0.8f);
			// if(GameCanvas.h <= 320)
			// {
			// matrix.postScale(0.5f,0.5f);
			// }
			// if(GameCanvas.w == 320 && GameCanvas.h == 480)
			// {
			// matrix.postScale(0.8f,0.8f);
			// }

			// end
			Bitmap bitmap = Bitmap.createBitmap(
					((AndroidPixmap) pixmap).bitmap, srcX, srcY, srcWidth, srcHeight, matrix, false);
//			canvas.drawBitmap(bitmap, src, dst, paint);
			canvas.drawBitmap(bitmap, x, y, null);
			// bitmap.recycle();
			bitmap = null;
			matrix = null;

		} catch (Exception e) {
			// Log.e(null, "Lỗi");
			e.printStackTrace();
		}
	}

	@Override
	public void fillArc(int tmpX, int tmpY, int i, int j, int k, int l) {
		paint.setColor(this.color);

		RectF rf = new RectF(tmpX, tmpY, tmpX + i, tmpY + j);
		canvas.drawArc(rf, k, l, true, paint);
	}

	@Override
	public void drawImage(Image pixmap, int x, int y, int anchors) {
		int xT = 0, yT = 0;
		switch (anchors) {
		case Graphics.RIGHT:
			xT = pixmap.getWidth();
			break;
//		case Graphics.TOP:
//			yT = - pixmap.getHeight();
//			break;
		case Graphics.HCENTER | Graphics.VCENTER:
			xT = - pixmap.getWidth() / 2;
			yT = - pixmap.getHeight() / 2;
			break;
		case Graphics.HCENTER:
			xT = - pixmap.getWidth() / 2;
			break;
		case Graphics.HCENTER | Graphics.BOTTOM:
			xT = - pixmap.getWidth() / 2;
			yT = - pixmap.getHeight();
			break;
		case Graphics.VCENTER:
			yT = - pixmap.getHeight() / 2;
			break;
		case Graphics.BOTTOM:
			yT = -pixmap.getHeight();
			break;
		}
		canvas.drawBitmap(((AndroidPixmap) pixmap).bitmap, x + xT, y + yT, null);
	}
	
	@Override
	public void drawImage(Image pixmap, int x, int y, int w, int h, int anchors) {
		if(w == 0 && h == 0) {
			drawImage(pixmap, x, y, anchors);
		} else {
			int xT = 0, yT = 0;
			switch (anchors) {
			case Graphics.RIGHT:
				xT = pixmap.getWidth();
				break;
			case Graphics.TOP:
				yT = - pixmap.getHeight();
				break;
			case Graphics.HCENTER | Graphics.VCENTER:
				xT = - pixmap.getWidth() / 2;
				yT = - pixmap.getHeight() / 2;
				break;
			case Graphics.HCENTER:
				xT = - pixmap.getWidth() / 2;
				break;
			case Graphics.HCENTER | Graphics.TOP:
				xT = - pixmap.getWidth() / 2;
				yT = - pixmap.getHeight();
				break;
			case Graphics.VCENTER:
				yT = - pixmap.getHeight() / 2;
				break;
			}
			RectF dest = new RectF(x + xT, y + yT, x + xT + w, y + yT + h);
			try {
				canvas.drawBitmap(pixmap.getPixmap(), null, dest, null);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	@Override
	public void drawText(String text, float x, float y, Paint paint, int anchors) {
		switch (anchors) {
		case Graphics.LEFT:
			paint.setTextAlign(Align.LEFT);
			break;
		case Graphics.RIGHT:
			paint.setTextAlign(Align.RIGHT);
			break;
		case Graphics.LEFT | Graphics.HCENTER:
		case Graphics.HCENTER:
			paint.setTextAlign(Align.CENTER);
			break;
		case Graphics.RIGHT | Graphics.HCENTER:
			paint.setTextAlign(Align.RIGHT);
			break;
		case Graphics.VCENTER | Graphics.HCENTER:
			y -= paint.getTextSize()/2;
			paint.setTextAlign(Align.CENTER);
			break;
		case Graphics.VCENTER | Graphics.RIGHT:
			y -= paint.getTextSize()/2;
			paint.setTextAlign(Align.RIGHT);
			break;
		case Graphics.VCENTER:
//		case Graphics.LEFT | Graphics.VCENTER:
			paint.setTextAlign(Align.CENTER);
//			x -= (BitmapFont.stringWidth(text) >> 1);
			break;
//		case Graphics.TOP:
//			paint.setTextAlign(Align.LEFT);
//			y -= paint.getTextSize();
//			break;
		case Graphics.TOP | Graphics.RIGHT:
			paint.setTextAlign(Align.RIGHT);
//			y -= paint.getTextSize();
			break;
		case Graphics.BOTTOM:
			paint.setTextAlign(Align.LEFT);
			y -= paint.getTextSize();
			break;
		default:
			paint.setTextAlign(Align.LEFT);
			break;
		}
		// paint.setTextSize(size);
		canvas.drawText(text, x, y, paint);
	}

	// @Override
	// public void drawText(String text, float x, float y, int color,String
	// fontPath) {
	// paint.setColor(color);
	// paint.setTypeface(Typeface.createFromAsset(assets,fontPath));
	// // paint.setTextSize(size);
	// canvas.drawText(text, x, y, paint);
	// }

	@Override
	public int getWidth() {
		return frameBuffer.getWidth();
	}

	@Override
	public int getHeight() {
		return frameBuffer.getHeight();
	}

	public void translate(float tx, float ty) {
		Matrix martix = canvas.getMatrix();
		martix.setTranslate((float) tx, (float) ty);
		canvas.concat(martix);
	}

	public void translate(int x, int y) {
		Matrix martix = canvas.getMatrix();
		martix.setTranslate((float) x, (float) y);
		canvas.concat(martix);
	}

	public float getTranslateX() {
		float[] values = new float[9];
		canvas.getMatrix().getValues(values);
		return values[Matrix.MTRANS_X];
	}

	public float getTranslateY() {
		float[] values = new float[9];
		canvas.getMatrix().getValues(values);
		return values[Matrix.MTRANS_Y];
	}

	public void setClip(Rect rect) {
		setClip(rect.left, rect.top, rect.width(), rect.height());
	}

	public void setClip(int x, int y, int width, int height) {
		if (x == clip.left && x + width == clip.right && y == clip.top
				&& y + height == clip.bottom) {
			return;
		}
		if (x < clip.left || x + width > clip.right || y < clip.top
				|| y + height > clip.bottom) {
			canvas.restore();
			canvas.save(Canvas.CLIP_SAVE_FLAG);
		}
		clip.left = x;
		clip.top = y;
		clip.right = x + width;
		clip.bottom = y + height;
		canvas.clipRect(clip);
	}

	@Override
	public void fillRoundRect(int x, int y, int w, int h, int arcWidth, int arcHeigth) {
		paint.setColor(this.color);
		paint.setStyle(Paint.Style.FILL);
		// canvas.drawRect(i, j, i + k, j + l, paint);
		canvas.drawRoundRect(new RectF(x, y, x + w, y + h), arcWidth, arcHeigth, paint);
	}

	@Override
	public void fillRoundRect(int x, int y, int w, int h, int arcWidth, int arcHeigth, int alpha) {
		paint.setColor(this.color);
		paint.setStyle(Paint.Style.FILL);
		paint.setAlpha(alpha);
		// canvas.drawRect(i, j, i + k, j + l, paint);
		canvas.drawRoundRect(new RectF(x, y, x + w, y + h), arcWidth, arcHeigth, paint);
	}

	@Override
	public void drawRoundRect(int x, int y, int width, int height,
			int arcWidth, int arcHeigth) {
		// TODO Auto-generated method stub
		paint.setColor(this.color);
		paint.setStyle(Paint.Style.STROKE);
		canvas.drawRoundRect(new RectF(x, y, x + width, y + height), arcWidth,
				arcHeigth, paint);
	}

	// @Override
	// public void translate(int x, int y) {
	// canvas.translate(x, y);
	// }
	//
	// public void setClip(int x, int y, int width ,int height){
	// canvas.clipRect(x, y, x+width, y+height);
	// }

}
