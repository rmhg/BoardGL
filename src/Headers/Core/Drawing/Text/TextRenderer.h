#pragma once
#ifndef TEXTRENDERED_H
#define TEXTRENDERED_H

#include "FontLoader.h"
class TextRenderer {

	FontLoader f;
	DrawBuffer* dbuf;
	std::vector<Rectangle> chars;
public :
	std::string str;
	TextRenderer(DrawBuffer*);
	void DrawText(std::string, vec3f, vec2f, vec4f);
	void Render();

};
TextRenderer::TextRenderer(DrawBuffer* buf): f(RES"arial.ttf"), dbuf(buf) {
	Texture::TexturePixelAlign(1);
}
void TextRenderer::DrawText(std::string str, vec3f cd, vec2f size, vec4f Color) {
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str[i] == ' ')
			continue;
		Glyph tmp = f.LoadChar(str[i], 100);
		Texture t(tmp);
		t.BindTextureSlot(i+1);
		chars.push_back(Rectangle(vec3f(cd.x + 0.2f *i, cd.y , cd.z), vec2f(0.2f, 0.2f), Color,  i+1));
	}
	for (unsigned int i = 0; i < chars.size();i++)
		dbuf->addDrawable(&chars[i]);
}
void TextRenderer::Render() {
	for(unsigned int i = 0; i < chars.size(); i++)
		dbuf->updDrawable(chars[i].id);
}



#endif