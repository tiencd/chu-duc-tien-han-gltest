package game.framework.impl;

import game.view.GameScr;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class AndroidFastRenderView extends SurfaceView implements Runnable {
	final AndroidGame game;
	Bitmap framebuffer;
	Thread renderThread = null;
	SurfaceHolder holder;
	volatile boolean running = false;
	long delay = 100;
	long sleeptime;

	public AndroidFastRenderView(AndroidGame game, Bitmap framebuffer) {
		super(game);
		this.game = game;
		this.framebuffer = framebuffer;
		this.holder = getHolder();
	}

	public void resume() {
		running = true;
		renderThread = new Thread(this);
		renderThread.start();
	}

	public void run() {
		Rect dstRect = new Rect();
		// long startTime = System.nanoTime();

		while (running) {
			// time before update
			long beforeUpdate = System.nanoTime();
			if(game!=null && game.getCurrentScreen()!=null)
			game.getCurrentScreen().update();

			// paint
			Canvas c = null;
			try {
				c = holder.lockCanvas();
				synchronized (holder) {
					game.getCurrentScreen().paint(game.getGraphics());
					if (c!=null) {
						c.getClipBounds(dstRect);
						c.drawBitmap(framebuffer, null, dstRect, null);
					}
				}
			} catch (Exception e) {
				e.printStackTrace();
			} finally {
				if (c != null)
					holder.unlockCanvasAndPost(c);
			}

			// sleep time
			this.sleeptime = delay - ((System.nanoTime() - beforeUpdate) / 100000L);
			try {
				Thread.sleep((long)30);
			} catch (Exception e) {
			}

			/*
			 * try{ if(!holder.getSurface().isValid()) continue; // sleeptime =
			 * delay - ((System.nanoTime()-startTime) / 1000000L); //
			 * Log.e("AndroidFastRenderView", "deltaTime="+deltaTime); //
			 * startTime = System.nanoTime(); GameCanvas.gameTick++; if
			 * (GameCanvas.gameTick > 10000) { GameCanvas.gameTick = 0; } try {
			 * // if(sleeptime>0){ Thread.sleep((long)25); // } } catch
			 * (InterruptedException e) { // TODO Auto-generated catch block
			 * e.printStackTrace(); }
			 * 
			 * game.getCurrentScreen().update();
			 * game.getCurrentScreen().paint(game.getGraphics());
			 * 
			 * Canvas canvas = holder.lockCanvas();
			 * canvas.getClipBounds(dstRect); canvas.drawBitmap(framebuffer,
			 * null, dstRect, null); holder.unlockCanvasAndPost(canvas); }catch
			 * (Exception e) { // Log.i("Exception", "Failed in Run");
			 * e.printStackTrace(); }
			 */}
	}

	public void pause() {
		running = false;
		while (true) {
			try {
				renderThread.join();
				break;
			} catch (InterruptedException e) {
				// retry
			}
		}
	}
}