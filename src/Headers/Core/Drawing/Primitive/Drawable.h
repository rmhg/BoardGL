#pragma once
#ifndef DRAWABLE_H
#define DRAWABLE_H

struct VertexData {
	vec3f posData;
	vec4f colData;
	vec2f texData;
	float tid;

	float* getPtr() {
		float* tmp = (float*)malloc(sizeof(float) * 10);
		for (int i = 0; i < 10; i++) {
			if (i < 3)
				tmp[i] = posData[i];
			else if (i > 2 && i < 7)
				tmp[i] = colData[i - 3];
			else if (i > 6 && i < 9)
				tmp[i] = texData[i - 7];
			else
				tmp[i] = tid;
		}
		return tmp;
	}
};


class Drawable {
private:
	std::vector<VertexData> vertices;
	unsigned int vertex_c = 0;
	unsigned int texID = 0;
	std::vector<unsigned int> rib, aib;
public :
	Drawable(unsigned int);
	unsigned int id;

	void InitVertexData(std::vector<vec3f>, std::vector<vec4f>, std::vector<unsigned int> = std::vector<unsigned int>(), std::vector<unsigned int> = std::vector<unsigned int>(), unsigned int atexID = 0, std::vector<vec2f> = std::vector<vec2f>());
	void Prepare();

	void delThis();
	void setColor(vec4f);
	void setColors(std::vector<vec4f>);
	void setColorv(unsigned int,vec4f);
	void setTexID(unsigned int);

	VertexData* getVertexDataPtr();
	unsigned int* getRIBPtr();
	unsigned int* getAIBPtr();

	unsigned int getVertexCount();
	unsigned int getRIBSize();
	unsigned int getAIBSize();

	vec3f getVertex(unsigned int);
	void  setVertex(unsigned int,vec3f);
	vec4f getColor(unsigned int);
	vec4f getColor();
	void Scale(float);
	vec3f getCenter();
	void Rotate(vec3f , float);
	void RotateX(float);
	void RotateY(float);
	void RotateZ(float);
    void Translate(vec3f);
    void Translate(float, float, float);
};

Drawable::Drawable(unsigned int VertexCount) {
	vertex_c = VertexCount;
}

void Drawable::InitVertexData(std::vector<vec3f> posData, std::vector<vec4f> colData, std::vector<unsigned int> RelativeIndices, std::vector<unsigned int> AbsIndices, unsigned int TextureID, std::vector<vec2f> texCoords) {
	posData.resize(vertex_c);
	texCoords.resize(vertex_c);
	colData.resize(vertex_c);
	for (unsigned int i = 0; i < vertex_c; i++) {
		VertexData tmp = {
			   posData[i],
			   colData[i],
			   texCoords[i],
			   (float)TextureID
		};
		vertices.emplace_back(tmp);
	}
	rib = RelativeIndices;
	aib = AbsIndices;
	texID = TextureID;
}

void Drawable::Prepare() {}


void Drawable::delThis() {}

void Drawable::setColor(vec4f Color) {
	for (VertexData& vd : vertices)
		vd.colData = Color;
}
void Drawable::setColors(std::vector<vec4f> Colors) {
	if (Colors.size() > vertex_c)
		Colors.resize(vertex_c);
	for (unsigned int i = 0; i < Colors.size();i++) {
		vertices[i].colData = Colors[i];
	}
}
void Drawable::setColorv(unsigned int vid, vec4f Color) {
	if (vid >= vertex_c) {
		std::cout << vid << " Is Out Of Bounds\n";
		return;
	}
	vertices[vid].colData = Color;
}
void Drawable::setTexID(unsigned int id) {
	for (VertexData& vd : vertices) {
		vd.tid = (float)id;
	}
}

void Drawable::Scale(float sf) {
	Matrix<float> Mat = Transform::Scale(sf);
	for (VertexData& vert : vertices) {
		vec4f tmp = vert.posData;
		tmp[3] = 1.0f;
		tmp *= Mat;
		for (unsigned int i = 0; i < 2; i++)
			vert.posData[i] = tmp[i];
	}
}
void Drawable::Rotate(vec3f vc, float deg) {}
void Drawable::Translate(vec3f vt ){
	
	for (unsigned int i = 0; i < vertex_c;i++)
		vertices[i].posData += vt;
}

void Drawable::Translate(float x, float y, float z) {

	for (unsigned int i = 0; i < vertex_c;i++) {
		vertices[i].posData.x += x;
		vertices[i].posData.y += y;
		vertices[i].posData.z += z;
	}
}

VertexData* Drawable::getVertexDataPtr() {
	return &vertices[0];
}
unsigned int* Drawable::getRIBPtr() {
	return &rib[0];
}
unsigned int* Drawable::getAIBPtr() {
	return &aib[0];
}

unsigned int Drawable::getVertexCount() {
	return vertex_c;
}
unsigned int Drawable::getRIBSize() {
	return rib.size();
}
unsigned int Drawable::getAIBSize() {
	return aib.size();
}

vec3f Drawable::getVertex(unsigned int i) {
	return vertices[i].posData;
}

void Drawable::setVertex(unsigned int i, vec3f pos) {
	vertices[i].posData = pos;
}

vec4f Drawable::getColor(unsigned int i) {
	return vertices[i].colData;
}

vec4f Drawable::getColor() {
	return vertices[0].colData;
}

#endif