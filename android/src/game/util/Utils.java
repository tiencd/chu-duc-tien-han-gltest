package game.util;

import java.util.Random;

public class Utils {

	public static Random random = new Random();

	public static int getRandom() {
		return random.nextInt();
	}

	public static int getRandom(int to) {
		return random.nextInt(to);
	}

	public static int getRandom(int from, int to) {
		if (from >= to) {
            return from;
        }
        return from + (random.nextInt(to - from + 1));
	}
	
}
