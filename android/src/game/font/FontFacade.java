package game.font;

import game.framework.Graphics;
import android.graphics.Color;

/**
 * <p>FontFacade allows to use native fonts and bitmaps fonts against conditions.</p>
 * 
 * <p>FontFacade stores an instance of the BitmapFont or Font, and allows to draw and measure
 * characters and strings.</p>
 * 
 * <p>This code is a part of the Mobile Fonts Project (http://sourceforge.net/projects/mobilefonts)</p>
 * 
 * @author Sergey Tkachev <a href="http://sergetk.net">http://sergetk.net</a>
 */
public class FontFacade {
	private Object font;
	private boolean isBitmapFont;

	/**
	 * Creates an instance of the FontFacade
	 * @param font the font. It must be an instance of Font or BitmapFont
	 */
	public FontFacade(Object font) {
		setFont(font);
	}

	/**
	 * Sets the font.
	 * @param font the font. It must be an instance of Font or BitmapFont
	 */
	public void setFont(Object font) {
		this.font = font;
		isBitmapFont = font instanceof BitmapFont;
	}

	/**
	 * Gets the current font.
	 * @return the font
	 */
	public Object getFont(){
		return font;
	}

	/**
	 * Draws the string.
	 * @param g the graphics context
	 * @param text the string to be drawn
	 * @param x the x coordinate of the anchor point
	 * @param y the y coordinate of the anchor point
	 * @param anchors the anchor point for positioning of the text
	 * @return the x coordinate for the next string
	 */
	 public void drawString(Graphics g, String text, int x, int y, float fontSize, int color, int anchors) {
		 BitmapFont.drawBoldFont(g, text, x, y, fontSize, color, anchors);
	}
	 
	 public void drawString(Graphics g, String text, int x, int y, float fontSize, String color, int anchors) {
		 BitmapFont.drawBoldFont(g, text, x, y, fontSize, Color.parseColor(color), anchors);
	}

	/**
	 * Gets the string width.
	 * @param str the string to width measure
	 * @return the width in pixels
	 */
	public int stringWidth(String str) {
		return substringWidth(str, 0, str.length());
	}

	/**
	 * Gets the substring width.
	 * @param str the string to measure
	 * @param offset zero-based index of a first character
	 * @param length the number of characters to measure
	 * @return the width in pixels
	 */
	public int substringWidth(String str, int offset, int length) {
		return ((BitmapFont)font).substringWidth(str, offset, length);
	}


	/**
	 * Draws the string with a limitation by the width.
	 * @param g the graphics context
	 * @param text the text to be drawn
	 * @param x the x coordinate of the anchor point
	 * @param y the y coordinate of the anchor point
	 * @param width the width limit in pixels
	 * @param anchors the anchor point for positioning the text
	 */
//	public void drawTrimmedString(Graphics g, String text, int x, int y, int width, int anchors) {
//		int textWidth = stringWidth(text);
//
//		if (textWidth <= width) {
//			drawString(g, text, x, y, anchors);
//		} else {
//			textWidth = 3 * charWidth('.');
//			int n = 0;
//			for (; n < text.length(); n++) {
//				textWidth += charWidth(text.charAt(n));
//				if (textWidth > width) {
//					break;
//				}
//			}
//			x = drawString(g, text.substring(0, n) + "...", x, y, anchors);
//		}
//	}

	/**
	 * Draws the string with a limitation by the width.
	 * @param g the graphics context
	 * @param outlineColor the color of text outline
	 * @param text the text to be drawn
	 * @param x the x coordinate of the anchor point
	 * @param y the y coordinate of the anchor point
	 */
	public void drawOutlinedString(Graphics g, String outlineColor, String text, int x, int y,
			float fontSize, int anchor) {
		int textColor = g.getColor();
		g.setColor(outlineColor);
		for (int dy = -1; dy <= 1; dy++) {
			for (int dx = -1; dx <= 1; dx++) {
				if (x != 0 || y != 0) {
					drawString(g, text, x + dx, y + dy, textColor, outlineColor, anchor);
				}
			}
		}
		g.setColor(textColor);
		drawString(g, text, x, y, fontSize, textColor, anchor);
	}

	public void drawOutlinedString(Graphics g, int outlineColor, String text, int x, int y, float fontSize, int anchor) {
		int textColor = g.getColor();
//		System.out.println("textColor = " + textColor);
//		System.out.println("outlineColor = " + Integer.parseInt(outlineColor.replace("0x","#")));
		g.setColor(outlineColor);
		for (int dy = -1; dy <= 1; dy++) {
			for (int dx = -1; dx <= 1; dx++) {
				if (x != 0 || y != 0) {
					drawString(g, text, x + dx, y + dy, fontSize, outlineColor, anchor);
				}
			}
		}
		g.setColor(textColor);
		drawString(g, text, x, y, fontSize, textColor, anchor);
	}
}
