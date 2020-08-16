#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public Drawable{
public :
	Rectangle(vec3f, vec2f, vec4f = BGL::Color::WHITE, unsigned int = 0);
	Rectangle(std::vector<vec3f>, vec4f = BGL::Color::WHITE, unsigned int = 0);
};

Rectangle::Rectangle(vec3f Start, vec2f size, vec4f Color, unsigned int tid) : Drawable(4) {
	InitVertexData({ Start, vec3f(Start.x + size.x, Start.y, Start.z), vec3f(Start.x + size.x,Start.y - size.y, Start.z), vec3f(Start.x, Start.y - size.y, Start.z) }, {}, { 0, 1, 2, 0, 2, 3 }, {}, tid, {vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f), vec2f(0.0f, 0.0f), vec2f(1.0f, 0.0)});
	setColor(Color);
}
Rectangle::Rectangle(std::vector<vec3f> pos, vec4f Color, unsigned int tid) : Drawable(4) {
	InitVertexData(pos, {}, { 0, 1, 2, 1, 2, 3 }, {}, tid, { vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f), vec2f(1.0f, 1.0f), vec2f(1.0f, 0.0) });
	setColor(Color);
}

#endif