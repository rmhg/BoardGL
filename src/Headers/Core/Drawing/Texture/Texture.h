#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include "Extern/STB/stb_use.h"

struct MetaTexture {
	std::string file_name;
	int Width;int Height;
	int Channel;
	unsigned char* data;
};

class Texture {
private :
	unsigned int id;
	unsigned int type;
	unsigned int Slotid;
	MetaTexture TextureData;
	unsigned int Channel_Format;
	void Init();
public :
	static unsigned int t_c;
	static int MAX_SLOT;

	Texture(const std::string&);
	Texture(MetaTexture);
	Texture(Glyph);
	~Texture();


	void bind();
	void unbind();

	void BindTextureSlot(unsigned int);
	void Load2GPU();

	static int GET_MAX_SLOT();
	unsigned int getID();
	unsigned int getSID();

	void setBorderColor(vec4f);
	inline void setParams(unsigned int, unsigned int);
	inline static void TexturePixelAlign(int);
	static MetaTexture Load(const std::string&);
};

int Texture::MAX_SLOT = -1;
unsigned int Texture::t_c = 0;


Texture::Texture(const std::string& file) {
	TextureData = Texture::Load(file);
	Init();
	stbi_image_free(TextureData.data);
}
Texture::Texture(MetaTexture texture) {
	TextureData = texture;
	Init();
}

Texture::Texture(Glyph glyph) {
	TextureData.Channel = 1;
	TextureData.data = glyph.data;
	TextureData.Height = glyph.Height;
	TextureData.Width = glyph.Width;
	Init();
}
void Texture::Init() {
	if (!TextureData.data) {
		std::cout << TextureData.file_name <<  " Cant Load Texture!\n";
		return;
	}
	switch (TextureData.Channel) {
	case 1:Channel_Format = GL_RED;
		break;
	case 3: Channel_Format = GL_RGB;
		break;
	case 4: Channel_Format = GL_RGBA;
		break;
	}

	
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	Load2GPU();
}

void Texture::TexturePixelAlign(int i) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, i);
}

int Texture::GET_MAX_SLOT() {
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MAX_SLOT);
	return MAX_SLOT;
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}
void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Load2GPU() {
	glTexImage2D(GL_TEXTURE_2D, 0, Channel_Format, TextureData.Width, TextureData.Height, 0, Channel_Format, GL_UNSIGNED_BYTE, TextureData.data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

MetaTexture Texture::Load(const std::string& file) {

	stbi_set_flip_vertically_on_load(true);
	MetaTexture tmp;
	tmp.file_name = file;
	tmp.data = stbi_load(file.c_str(), &tmp.Width, &tmp.Height, &tmp.Channel, 0);

	return tmp;
}

void Texture::BindTextureSlot(unsigned int slot) {
	if (slot > (unsigned int)(MAX_SLOT - 1)) {
		std::cout << slot << " Is Out Of Bound ! \n";
		return;
	}
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
	Slotid = slot;
}

unsigned int Texture::getID() {
	return id;
}
unsigned int Texture::getSID() {
	return Slotid;
}

void Texture::setParams(unsigned int c, unsigned int type) {
	glTexParameteri(GL_TEXTURE_2D, c, type);
}
void Texture::setBorderColor(vec4f Color) {
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &Color[0]);
}

Texture::~Texture() {}

#endif




