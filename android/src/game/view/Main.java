package game.view;

import game.framework.impl.AndroidGame;
import android.os.Bundle;

public class Main  extends AndroidGame {
	GameScr screen;
	@Override
	public void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		screen = new GameScr(this);
		setScreen(screen);
		screen.onInit();
	}
	
}
