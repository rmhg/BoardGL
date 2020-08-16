#pragma once
class Circle : public Drawable {

public :
	Circle(vec3f = vec3f(0.0f, 0.0f, -1.0f), float = 0.3f, unsigned int = 4, vec4f = BGL::Color::WHITE, unsigned int = 0);
};

Circle::Circle(vec3f Center, float radius, unsigned int polyn, vec4f Color, unsigned int tid) : Drawable(polyn + 1){
	std::vector<vec3f> vd;
	vd.reserve(polyn + 1);
	std::vector<unsigned int> eb;
	unsigned int n = polyn;
	float cdeg = 360.0f / polyn;
	float deg = cdeg;
	vd.emplace_back(Center);
	eb.push_back(0);eb.push_back(1);eb.push_back(2);
	vec3f known = vec3f(Center.x + radius, Center.y, Center.z);
	n -= 1;
	vd.emplace_back(known);
	int i = 1;
	vec3f calc;
	while (n--) {
	    float rad = toRad(deg);
		calc.x = Center.x + radius * cos(rad);
		calc.y = Center.y + radius * sin(rad);
		calc.z = Center.z;
		i++;
		vd.emplace_back(calc);
		eb.emplace_back(0);
		eb.emplace_back(i);
		if (i == polyn)
			eb.push_back(1);
		else
		 eb.push_back((i+1));
		deg += cdeg;
	}

	InitVertexData(vd, {}, eb, {}, 0, {});
	setColor(Color);

}