package game.framework;

import game.framework.impl.AndroidGame;


public interface Game {
    public Input getInput();

    public FileIO getFileIO();

    public Graphics getGraphics();

    public Audio getAudio();

    public void setScreen(GameScreen gameScreen);

    public GameScreen getCurrentScreen();

    public GameScreen getStartScreen();
    
    public AndroidGame getThis();
    
}