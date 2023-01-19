#pragma once
#include "../helpers/vmt.h"

#define PRINTF_FORMAT_STRING _Printf_format_string_

typedef unsigned long HFont;
typedef unsigned long VPANEL;
typedef unsigned long FontHandle;


enum FontFeature
{
	FONT_FEATURE_ANTIALIASED_FONTS = 1,
	FONT_FEATURE_DROPSHADOW_FONTS = 2,
	FONT_FEATURE_OUTLINE_FONTS = 6,
};

enum FontDrawType
{
	FONT_DRAW_DEFAULT = 0,

	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

enum FontFlags : int
{
	FONTFLAG_NONE = 0,
	FONTFLAG_ITALIC = (1 << 0),
	FONTFLAG_UNDERLINE = (1 << 1),
	FONTFLAG_STRIKEOUT = (1 << 2),
	FONTFLAG_SYMBOL = (1 << 3),
	FONTFLAG_ANTIALIAS = (1 << 4),
	FONTFLAG_GAUSSIANBLUR = (1 << 5),
	FONTFLAG_ROTARY = (1 << 6),
	FONTFLAG_DROPSHADOW = (1 << 7),
	FONTFLAG_ADDITIVE = (1 << 8),
	FONTFLAG_OUTLINE = (1 << 9),
	FONTFLAG_CUSTOM = (1 << 10),
	FONTFLAG_BITMAP = (1 << 11)
};

class ISurface
{
public:
	 void DrawSetColor(int r, int g, int b, int a = 255) 
	{
		vmt::callFunction<void>(this, 15, r, g, b, a);
	}

	void DrawFilledRect(int x, int y, int xx, int yy) 
	{
		vmt::callFunction<void>(this, 16, x, y, xx, yy);
	}

	 void DrawOutlinedRect(int x, int y, int xx, int yy) 
	{
		vmt::callFunction<void>(this, 18, x, y, xx, yy);
	}

	void DrawLine(int x0, int y0, int x1, int y1)
	{
		vmt::callFunction<void, int, int, int, int>(this, 19, x0, y0, x1, y1);
	}

	 void DrawSetTextFont(HFont font) {
		 vmt::callFunction<void>(this, 23,font);
	 }

	 void DrawSetTextPos(int x, int y) {
		 vmt::callFunction<void>(this, 26, x,y);

	 }

	 void SetTextColor(int r, int g, int b, int a = 255)
	 {
		 vmt::callFunction<void, int, int, int, int>(this, 25, r, g, b, a);
	 }

	 void DrawPrintText(const wchar_t* text, int textLen, FontDrawType drawType = FONT_DRAW_DEFAULT) 
	 {
		 vmt::callFunction<void>(this, 28, text,textLen,drawType);
	 }

	 std::pair<int,int> GetScreenSize()
	 {
		 int width{ }, height{ };
		 vmt::callFunction<void, int&, int&>(this, 44, width, height);
		 return std::make_pair(width, height);
	 }

	 unsigned long FontCreate()
	 {
		 return vmt::callFunction<unsigned long>(this, 71);
	 }

	 void SetFontGlyphSet(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	 {
		 vmt::callFunction<void>(this, 72, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	 }

	 bool AddCustomFontFile(const char* fontFileName)
	 {
		 return  vmt::callFunction<bool>(this, 73, fontFileName);
	 }
};
