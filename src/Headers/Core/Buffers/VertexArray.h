#pragma once
#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

class VertexArray {
private:
	unsigned int id;
public :
	VertexArray();
	void Bind();
	void unBind();

	unsigned int getID();
};

VertexArray::VertexArray() {
	id = 0;
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}

void VertexArray::Bind() {
	glBindVertexArray(id);
}

void VertexArray::unBind() {
	glBindVertexArray(0);
}


unsigned VertexArray::getID() {
	return id;
}
#endif