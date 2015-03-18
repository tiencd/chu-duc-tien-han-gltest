package game.framework.impl;

import game.framework.Audio;
import game.framework.FileIO;
import game.framework.Game;
import game.framework.GameScreen;
import game.framework.Graphics;
import game.framework.Input;
import game.view.GameScr;
import android.app.Activity;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.content.res.AssetManager;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.os.Bundle;
import android.os.PowerManager;
import android.view.KeyEvent;
import android.view.Window;
import android.view.WindowManager;

public abstract class AndroidGame extends Activity implements Game {
	public static AndroidGame game;
	AndroidFastRenderView renderView;
	Graphics graphics;
	Audio audio;
	Input input;
	FileIO fileIO;
	GameScreen gameScreen;
//	WakeLock wakeLock;
	public static boolean isLandscape;
	public static int widthScreen, heightScreen;
	public ActivityInfo mActivityInfo;
	public static float scaleX = 1, scaleY = 1;
	// check connect internet
//	public static boolean isConnect;

	// AssetManager
	public static AssetManager assets;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		try {
			super.onCreate(savedInstanceState);

			requestWindowFeature(Window.FEATURE_NO_TITLE);
			getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
					WindowManager.LayoutParams.FLAG_FULLSCREEN);
			game = this;
			// setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);

			isLandscape = getResources().getConfiguration().orientation == Configuration.ORIENTATION_SQUARE;

			int width = getWindowManager().getDefaultDisplay().getWidth();
			int height = getWindowManager().getDefaultDisplay().getHeight();

			widthScreen = width;
			heightScreen = height;
			if(widthScreen < 480) {
					widthScreen = 480;
					heightScreen = 800;
			}
			scaleX = (float) widthScreen / width;
			scaleY = (float) heightScreen / height;
			GameScreen.SCREEN_WIDTH = widthScreen;
			GameScreen.SCREEN_HEIGHT = heightScreen;

			assets = getAssets();
			Bitmap frameBuffer = Bitmap.createBitmap(widthScreen, heightScreen, Config.RGB_565);

			renderView = new AndroidFastRenderView(this, frameBuffer);
			graphics = new AndroidGraphics(getAssets(), frameBuffer);
			fileIO = new AndroidFileIO(getAssets());
			audio = new AndroidAudio(this);
			input = new AndroidInput(this, renderView, scaleX, scaleY);

			setContentView(renderView);
			PowerManager powerManager = (PowerManager) getSystemService(Context.POWER_SERVICE);
		} catch (Exception e) {
			// Log.i("Exception", e.toString());
			e.printStackTrace();
		}
	}

	@Override
	public void onResume() {
		super.onResume();
//		wakeLock.acquire();
		if(gameScreen != null)
			gameScreen.resume();
		else {
			GameScr gameCanvas = new GameScr(this);
	        gameScreen = gameCanvas;
		}
		renderView.resume();
	}
	
	@Override
	public void onPause() {
		super.onPause();
//		wakeLock.release();
		renderView.pause();
		if(gameScreen!=null)
			gameScreen.pause();
		else {
			GameScr gameCanvas = new GameScr(this);
	        gameScreen = gameCanvas;
		}

		if (isFinishing())
			gameScreen.dispose();
	}

	@Override
	public Input getInput() {
		return input;
	}

	@Override
	public FileIO getFileIO() {
		return fileIO;
	}

	@Override
	public Graphics getGraphics() {
		return graphics;
	}

	@Override
	public Audio getAudio() {
		return audio;
	}

	@Override
	public void setScreen(GameScreen gameScreen) {
		if (gameScreen == null)
			throw new IllegalArgumentException("Screen must not be null");
		if(this.gameScreen != null) {
			this.gameScreen.pause();
			this.gameScreen.dispose();
		}
//		gameScreen.resume();
//		gameScreen.update();
		this.gameScreen = gameScreen;
	}

	public AndroidGame getThis() {
		return this;
	}

	@Override
	public GameScreen getCurrentScreen() {
		return gameScreen;
	}

	@Override
	public GameScreen getStartScreen() {
		return null;
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// return super.onKeyDown(keyCode, event);
		return false;
	}

	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		// return super.onKeyUp(keyCode, event);
		return false;
	}

	@Override
	public void finish() {
		super.finish();
		onDestroy();
	}

}