#pragma once
#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#define VERTEX_SIZE 2500000 //1MB
#include <cstdarg>
struct MetaSubVertex {
	unsigned int c_s;
	
};

template <typename type>
class VertexBuffer {
private :

	unsigned int id;
	unsigned int target;
	unsigned int usage;
	unsigned int e_size;
	unsigned int mv_w;


	const unsigned int e_vertex = VERTEX_SIZE;
	unsigned int c_vertex = 0;

	std::vector<type> data;
	std::vector<MetaSubVertex> mv;

public :
	VertexBuffer(unsigned int = GL_ARRAY_BUFFER, unsigned int = GL_DYNAMIC_DRAW);

	void Bind();
	void unBind();
	
	void Resize(unsigned int);
	void ResizeV(unsigned int);
	void updData(type*, unsigned int, int);
	void Draw();

	void VertexAttrib(int,...);
	void InitVertex(std::vector<type>);
	void delVertex(unsigned int,unsigned int = 1);
    unsigned int addVertex(std::vector<type>);
	unsigned int addVertexV(std::vector<Vector<type> >);
	inline void updVertex(unsigned int,std::vector<type>);
	void updVertex(unsigned int);
	inline void updBufferV(unsigned int, unsigned int);
	void at(unsigned int, type);
	void Done();
	static void WireFrameMode(bool);

	void Destroy();
	unsigned int getW();
	unsigned int getVertices();
	unsigned int getSize();

	void Print();

	unsigned int getID();

};
template <typename type>
VertexBuffer<type>::VertexBuffer(unsigned int atype, unsigned int ausage) : target(atype), usage(ausage) {
	e_size = sizeof(type);
	mv_w = 1;
	glGenBuffers(1, &id);
	glBindBuffer(target, id);
	glBufferData(target, e_size * e_vertex, NULL, usage);
}

template <typename type>
void VertexBuffer<type>::Bind() {
	glBindBuffer(target, id);
}
template <typename type>
void VertexBuffer<type>::unBind() {
	glBindBuffer(target, 0);
}

template <typename type>
void VertexBuffer<type>::Resize(unsigned int a_size_in_byte) {
	glBufferData(target, a_size_in_byte, NULL, usage);
}

template<typename type>
unsigned int VertexBuffer<type>::getID() { 
	return id; 
}

template <typename type>
void VertexBuffer<type>::WireFrameMode(bool toggle) {
	if (toggle)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}


template<typename type>
void VertexBuffer<type>::updData(type* data, unsigned int e_count, int offset) {
	glBufferSubData(target, offset * e_size, e_count * e_size, data);
}

template<typename type>
void VertexBuffer<type>::updBufferV(unsigned int start, unsigned int e_count) {
	glBufferSubData(target, start * e_size * mv_w, e_count * e_size * mv_w, &data[start * mv_w]);
}
template<typename type>
void VertexBuffer<type>::VertexAttrib(int n, ...) {
	va_list va;
	va_start(va, n);
	int w = 0;
	for (int i = 0; i < n;i++) {
		MetaSubVertex tmp;
		int a = va_arg(va, int);
		tmp.c_s = a;
		w += a;

		mv.push_back(tmp);
	}
	mv_w = w;
	int s = 0;
	for (int i = 0; i < n;i++) {
		s += mv[i].c_s;
		glVertexAttribPointer(i, mv[i].c_s, GL_FLOAT, GL_FALSE, w * e_size, (void*)((s - mv[i].c_s)*e_size));
		glEnableVertexAttribArray(i);
	}
	va_end(va);
}

template <typename type>
void VertexBuffer<type>::InitVertex(std::vector<type> adata) {
	c_vertex = adata.size();
	for (type val : adata)
		data.push_back(val);
	updData(&data[0], data.size(), 0);
	
}
template<typename type>
unsigned int VertexBuffer<type>::addVertex(std::vector<type> adata) {
	if (c_vertex > e_vertex / mv_w) {
		std::cout << "Overflow !\n";
	}
	adata.resize(mv_w);
	unsigned int pos = 0;
	for (type vals : adata)
		data.push_back(vals);
	pos = data.size() / mv_w;
	c_vertex++;
	return pos - 1;
}

template<typename type>
void VertexBuffer<type>::delVertex(unsigned int vid, unsigned int n) {
	c_vertex -= n;
	del<type>(vid * mv_w, mv_w * n, data);
}

template<typename type>
void VertexBuffer<type>::updVertex(unsigned int vid, std::vector<type> adata) {
	if (vid * mv_w >= data.size()) {
		std::cout << vid << " is Out Of Bounds !\n";
		return;
	}
	for (unsigned int i = 0; i < adata.size(); i++) {
		data[vid * mv_w + i] = adata[i];
	}
}

template<typename type>
void VertexBuffer<type>::updVertex(unsigned int vid) {
	glBufferSubData(target, vid * mv_w * e_size , mv_w * e_size, &data[vid * mv_w]);
}

template<typename type>
void VertexBuffer<type>::Draw() {
	switch (target) {
	case GL_ELEMENT_ARRAY_BUFFER: glDrawElements(GL_TRIANGLES, data.size() , GL_UNSIGNED_INT, 0);
		break;
	case GL_ARRAY_BUFFER: glDrawArrays(GL_TRIANGLES, 0, data.size()/mv_w);
		break;
	}
}

template<typename type>
void VertexBuffer<type>::at(unsigned int index, type val) {
	if (index > data.size() - 1) {
		std::cout << index << " Out Of Bound ! \n";
		return;
	}
	data[index] = val;
}

template<typename type>
void VertexBuffer<type>::Done() {
	if (data.size())
		glBufferSubData(target, 0, data.size() * e_size, &data[0]);
}

template<typename type>
void VertexBuffer<type>::Print() {
	int i = 0;
	for (type vals : data) {
		i++;
		std::cout << vals << " " ;
		if (!(i % mv_w))
			std::cout << LF;
	}
}

template<typename type>
unsigned int VertexBuffer<type>::getW() {
	return mv_w;
}

template<typename type>
unsigned int VertexBuffer<type>::getVertices() {
	return data.size()/mv_w;
}

template<typename type>
unsigned int VertexBuffer<type>::getSize() {
	return data.size();
}

template<typename type>
void VertexBuffer<type>::ResizeV(unsigned int v) {
	glBufferData(target, v * mv_w * e_size, NULL, usage);
}

template <typename type>
void VertexBuffer<type>::Destroy() {

}

#endif 