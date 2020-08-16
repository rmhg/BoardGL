#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle : public Drawable {
private :
public :
	Triangle(std::vector<vec3f>, vec4f = BGL::Color::WHITE, unsigned int = 0);

};
Triangle::Triangle(std::vector<vec3f> pos, vec4f Color, unsigned int tid) : Drawable(3) {
	InitVertexData(pos, {}, {}, {}, tid, {vec2f(0.0f, 0.0f), vec2f(1.0f, 0.0f), vec2f(0.0f, 1.0f)});
	setColor(Color);
}

#endif