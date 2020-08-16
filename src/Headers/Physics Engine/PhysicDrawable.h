#ifndef PHYSICS_DRAWABLE_H
#define PHYSICS_DRAWABLE_H

using namespace BGL;


class PhysicsDrawable : public Rectangle,public DynamicObject {
public :
	bool isDynamic = true;
	PhysicsDrawable();
	PhysicsDrawable(vec3f, vec2f, vec4f, float = 10, unsigned int = 0);
	void update() override;
};

PhysicsDrawable::PhysicsDrawable() : Rectangle(vec3f(0.0f, -0.3f, -1.0f), vec2f(0.2f, 0.2f), BGL::Color::BLUE) {
	setMass(100);
}
PhysicsDrawable::PhysicsDrawable(vec3f Start, vec2f size, vec4f Color, float mass, unsigned int tid) : Rectangle(Start, size, Color, tid) {
	setMass(mass);
}
void PhysicsDrawable::update() {
	if (isDynamic) {
		Translate(getVelocity());
		DynamicObject::update();
	}
}


#endif