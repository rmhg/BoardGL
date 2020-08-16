#pragma once

class DynamicObject {
	float mass;vec3f tvel;
	vec3f avel;vec3f tacc;
	vec3f teacc;vec3f racc;
	Matrix<float> I;
public :
	DynamicObject();
	DynamicObject(float);
	void setMass(float m);
	float getMass();
	void applyImpulse(vec3f, float);
	void applyForce(vec3f);
	void stop();
	void setVelocity(vec3f);
	vec3f getVelocity();
    virtual void update();
};

DynamicObject::DynamicObject() {

}
DynamicObject::DynamicObject(float m) : mass(m) {

}
void DynamicObject::setMass(float m) {
	mass = m;
}
float DynamicObject::getMass() {
	return mass;
}
vec3f DynamicObject::getVelocity() {
	return tvel;
}
void DynamicObject::setVelocity(vec3f vel) {
	tvel = vel;
}
void DynamicObject::applyImpulse(vec3f force, float duration) {
	while (duration > 0) {
		applyForce(force);
		duration -= Params::TIMESTEP;
	}
}
void DynamicObject::applyForce(vec3f force) {
	teacc = force / mass;
	update();
	teacc *= 0.0f;
}
void DynamicObject::update() {
	tvel += tacc + teacc + vec3f(0.0f, -Params::GRAVITY, 0.0f);
}