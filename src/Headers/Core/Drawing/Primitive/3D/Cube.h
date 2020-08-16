#pragma once
#ifndef CUBE_H
#define CUBE_H

class Cube : public Drawable {
public :
	Cube(vec3f = vec3f(), float = 0.2f, vec4f = BGL::Color::WHITE, unsigned int = 0);
};

Cube::Cube(vec3f start, float a, vec4f Color, unsigned int tid) : Drawable(8) {
	InitVertexData({start, vec3f(start.x + a, start.y, start.z), vec3f(start.x + a, start.y + a, start.z),vec3f(start.x, start.y  + a, start.z),
		vec3f(start.x, start.y, start.z - a), vec3f(start.x + a, start.y, start.z - a), vec3f(start.x + a, start.y + a, start.z - a),vec3f(start.x, start.y + a, start.z - a) }, {}, {0, 1, 2, 0, 3, 2,  3, 0, 4, 3, 7, 4, 7, 6, 5, 7, 4, 5, 6, 5, 1, 2, 1, 5}, {}, tid, {});
	setColor(Color);
}


#endif