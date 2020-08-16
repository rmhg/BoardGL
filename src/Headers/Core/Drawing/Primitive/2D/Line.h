#pragma once
#ifndef LINE_H
#define LINE_H

class Line : public Drawable{

public :
	Line(vec3f, vec3f, vec4f = BGL::Color::WHITE,float = 0.3f);
	Line(vec3f, vec4f = BGL::Color::WHITE, float = 45.0f ,float = 0.3f, float = 0.3f );
};

Line::Line(vec3f First, vec3f Second, vec4f Color, float Width) : Drawable(4) {
	InitVertexData({ First, Second, vec3f(), vec3f() }, {}, { 0, 1, 2, 0, 2, 3 }, {});
	setColor(Color);
}
Line::Line(vec3f First, vec4f Color, float deg, float Height, float Width) : Drawable(4) {
	InitVertexData({ First, vec3f(), vec3f(), vec3f() }, {}, { 0, 1, 2, 0, 2, 3 }, {});
	setColor(Color);
}

#endif