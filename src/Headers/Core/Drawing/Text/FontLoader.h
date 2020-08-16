#pragma once
#ifndef FontLOADER_H
#define FontLOADER_H

#include <ft2build.h>
#include FT_FREETYPE_H 


struct Glyph {
	char ch;
	int Width, Height;
	int bX, bY, adv;
	unsigned char* data;
};

class FontLoader {
	FT_Face face;
	FT_Library lib;
	std::string font;
public :
	FontLoader(const std::string&);
	~FontLoader();
	void InitFont(const std::string&);
	Glyph LoadChar(char, int);
	void Destroy();
};

FontLoader::FontLoader(const std::string& font_path) : font(font_path) {
	InitFont(font_path);
}

void FontLoader::InitFont(const std::string& font_path) {
	
	if (FT_Init_FreeType(&lib)) {
		std::cout << "Error FreeType | Cant Initialize!\n";
		return;
	}
	if (FT_New_Face(lib, font_path.c_str(), 0, &face)) {
		std::cout << "Error FreeType | Cant Initialize The Font!\n";
		return;
	}
	
}
Glyph FontLoader::LoadChar(char ch, int size) {
	FT_Set_Pixel_Sizes(face, 0, size);
	Glyph tmp = {'\0', -1, -1, -1, -1, -1, NULL};
	if (FT_Load_Char(face, ch, FT_LOAD_RENDER)) {
		std::cout << "Error FreeType | Cant Load Char : " << ch << " From " << font << LF;
		return tmp;
	}
	tmp.ch = ch;
	tmp.data = face->glyph->bitmap.buffer;
	tmp.Width = face->glyph->bitmap.width;
	tmp.Height = face->glyph->bitmap.rows;
	tmp.bX = face->glyph->bitmap_top;
	tmp.bY = face->glyph->bitmap_top;
	tmp.adv = face->glyph->advance.x;
	return tmp;
}
void FontLoader::Destroy() {
	FT_Done_Face(face);
	FT_Done_FreeType(lib);
}

FontLoader::~FontLoader() {
	Destroy();
}

#endif
