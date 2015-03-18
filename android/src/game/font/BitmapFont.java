package game.font;

import game.framework.Graphics;
import game.view.GameScr;

import java.util.Vector;

import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Typeface;

public class BitmapFont {
	public static BitmapFont m_bmNormalFont;
	public static BitmapFont m_bmFont;
	public static FontFacade m_facedeFont, m_facedeFontNormal;
	private static Paint paint = new Paint();

	Typeface font;
	// Rect bounds = new Rect();

	static {
		// BitmapFont.m_bmFont = new BitmapFont("cambriab.ttf");
		// BitmapFont.m_bmNormalFont = new BitmapFont("cambria.ttc");
		BitmapFont.m_bmFont = new BitmapFont();
		BitmapFont.m_bmNormalFont = new BitmapFont();
		m_facedeFont = new FontFacade(m_bmFont);
        m_facedeFontNormal = new FontFacade(m_bmNormalFont);
	}

	public static void drawBoldFont(Graphics g, String text, int x, int y, float fontSize,
			int color, int anchors) {
		paint.setColor(color);
		paint.setAntiAlias(true);
		paint.setFakeBoldText(true);
		paint.setTextSize(fontSize);
		paint.setTypeface(Typeface.create("serif", Typeface.BOLD));
		// paint.setTypeface(Typeface.SERIF);
		m_bmFont.drawString(g, text, x, y, paint, anchors);
	}

	public static void drawBoldFont(Graphics g, String text, int x, int y, float fontSize,
			String color, int anchors) {
		paint.setColor(Color.parseColor(color));
		paint.setAntiAlias(true);
		paint.setFakeBoldText(true);
		paint.setTextSize(fontSize);
		paint.setTypeface(Typeface.create("serif", Typeface.BOLD));
		// paint.setTypeface(Typeface.SERIF);
		m_bmFont.drawString(g, text, x, y, paint, anchors);
	}

	public static void drawNormalFont(Graphics g, String text, int x, int y, float fontSize,
			int color, int anchors) {
		paint.setAntiAlias(true);
		paint.setFakeBoldText(true);
		paint.setColor(color);
		paint.setTypeface(Typeface.SERIF);
		paint.setTextSize(fontSize);
		m_bmNormalFont.drawString(g, text, x, y, paint, anchors);
	}

	public static void drawNormalFont(Graphics g, String text, int x, int y, float fontSize,
			String color, int anchors) {
		paint.setAntiAlias(true);
		paint.setFakeBoldText(true);
		paint.setColor(Color.parseColor(color));
		paint.setTypeface(Typeface.SERIF);
		paint.setTextSize(fontSize);
		m_bmNormalFont.drawString(g, text, x, y, paint, anchors);
	}

	public static void drawOutlinedString(Graphics g, String text, int x, int y, float fontSize,
			String contentColor, String boundColor, int anchors) {
		g.setColor(contentColor);
		m_facedeFont.drawOutlinedString(g, boundColor, text, x, y, fontSize, anchors);
	}

    public static void drawOutlinedStringNormal(Graphics g, String text, int x, int y,  float fontSize, String contentColor, String boundColor, int anchors) {
        g.setColor(contentColor);
        m_facedeFontNormal.drawOutlinedString(g, boundColor, text, x, y, fontSize, anchors);
    }
	
	// ////////////////////////////////////////////////////////////

	public void drawString(Graphics g, String text, int x, int y, Paint paint, int anchors) {
		y += BitmapFont.m_bmFont.getHeight();
		g.drawText(text, x, y, paint, anchors);
	}

	public BitmapFont() {
		// paint.setTypeface(Typeface.DEFAULT);
	}

	// public BitmapFont(String fontPath) {
	// paint.setTypeface(Typeface.createFromAsset(AndroidGame.game.getAssets(),fontPath));
	// }

	public int substringWidth(String str, int offset, int length) {
		return (int) paint.measureText(str, offset, length);
		// return 0;
	}

	public static int stringWidth(String na) {
		// TODO Auto-generated method stub
		// return 0;
		return (int) paint.measureText(na, 0, na.length());
	}

	public int getHeight() {
		// TODO Auto-generated method stub
		// return (int)paint1.getTextSize();
		return (int) paint.descent() - (int) paint.ascent();
		// return 0;
	}

	public String[] splitFontBStrInLine(String st, int width) {
		Vector vector = new Vector();
		int i = 0, i1 = 0, w1 = 0, ispace = -1;
		char ch;
		while (i < st.length()) {
			ch = st.charAt(i);
			if (ch == ' ')
				ispace = i;
			w1 += stringWidth(String.valueOf(ch));

			if (w1 > width || ch == '\n') {
				if (ch != '\n' && ispace != -1)
					i = ispace;
				vector.addElement(st.substring(i1, i));

				if (st.charAt(i) == ' ' || ch == '\n')
					i++;
				i1 = i;
				w1 = 0;
				ispace = -1;
			} else
				i++;
		}
		if (i > i1)
			vector.addElement(st.substring(i1, i)); // end line

		String[] a = new String[vector.size()];
		for (i = 0; i < a.length; i++) {
			a[i] = (String) vector.elementAt(i);
		}
		return a;
	}

	public static String[] splitStrInLine(String src, int lineWidth) {
		Vector list = new Vector();
		int srclen = src.length();
		if (srclen <= 1) {
			return new String[] { src };
		}
		String tem = "";
		int start = 0, end = 0;
		while (true) {
			while (true) {
				if (getWidthOfWithSmiley(tem) > lineWidth) {
					if (end > 0) {
						end--;
					}
					break;
				}
				tem += src.charAt(end);
				end++;
				if (src.charAt(end) == '\n') {
					break;
				}
				if (end >= srclen - 1) {
					end = srclen - 1;
					break;
				}
			}
			if (end != srclen - 1 && (src.charAt(end + 1) != ' ')) {
				int endAnyway = end;
				while (true) {
					if (src.charAt(end + 1) == '\n') {
						break;
					}
					if (src.charAt(end + 1) == ' ' && src.charAt(end) != ' ') {
						break;
					}
					if (end == start) {
						break;
					}
					end--;
				}
				if (end == start) {
					end = endAnyway;
				}
			}
			String s = src.substring(start, end + 1);
			if (s.endsWith("\n")) {
				s = s.substring(0, s.length() - 1);
			}
			list.addElement(s);
			if (end == srclen - 1) {
				break;
			}
			start = end + 1;
			while (start != srclen - 1 && src.charAt(start) == ' ') {
				start++;
			}
			if (start == srclen - 1) {
				break;
			}
			end = start;
			tem = "";
		}
		String[] strs = new String[list.size()];
		for (int i = 0; i < list.size(); i++) {
			strs[i] = (String) list.elementAt(i);
		}
		return strs;
	}

	public static int getWidthOfWithSmiley(String str) {
		int w = 0;
		for (int i = 0; i < str.length(); i++) {
			w += getWidthOf(str.charAt(i));
		}
		return w;
	}

	public static int getWidthOf(char c) {
		if (c >= 30000) {
			return 20;
		}
		return m_facedeFont.stringWidth(String.valueOf(c));
	}

	public static String[] splitString(String _text, String _searchStr) {
		// String buffer to store str
		int count = 0, pos = 0;
		int searchStringLength = _searchStr.length();
		int aa = _text.indexOf(_searchStr, pos);
		while (aa != -1) {
			pos = aa + searchStringLength;
			aa = _text.indexOf(_searchStr, pos);
			count++;
		}
		String[] sb = new String[count + 1];
		// Search for search
		int searchStringPos = _text.indexOf(_searchStr);
		int startPos = 0;
		// Iterate to add string
		int index = 0;
		while (searchStringPos != -1) {
			sb[index] = _text.substring(startPos, searchStringPos);
			startPos = searchStringPos + searchStringLength;
			searchStringPos = _text.indexOf(_searchStr, startPos);
			index++;
		}
		sb[index] = _text.substring(startPos, _text.length());
		return sb;
	}
}
