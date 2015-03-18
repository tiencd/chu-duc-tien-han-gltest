package game.framework;


public abstract class GameScreen {
	// my member
	public static int SCREEN_WIDTH, SCREEN_HEIGHT;
	public enum GAME_STATE {
		isFree,  isPlaying,  isPause,  isGameOver,
	};
	
	protected final Game game;
	
	private GAME_STATE gameState;

	public GameScreen(Game game) {
		this.game = game;
		
	}

	public void paint(Graphics g) {}
	
	public void update() {}

    public void start() {
		setGameState(GAME_STATE.isPlaying);
    }
    
	public void gameOver() {
		setGameState(GAME_STATE.isGameOver);
	}
	
	public void pause() {
		setGameState(GAME_STATE.isPause);
	}

	public void resume() {
		if(isPause()) {
			setGameState(GAME_STATE.isPlaying);
		}
	}

	public abstract void dispose();

	public GAME_STATE getGameState() {
		return gameState;
	}
	
	public boolean isPlaying() {
		return gameState.equals(GAME_STATE.isPlaying);
	}
	
	public boolean isFree() {
		return gameState.equals(GAME_STATE.isFree);
	}
	
	public boolean isPause() {
		return gameState.equals(GAME_STATE.isPause);
	}
	
	public boolean isGameOver() {
		return gameState.equals(GAME_STATE.isGameOver);
	}

	public void setGameState(GAME_STATE gameState) {
		this.gameState = gameState;
	}

}
