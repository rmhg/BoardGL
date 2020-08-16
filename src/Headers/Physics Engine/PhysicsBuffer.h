#ifndef PHYSICS_BUFFER_H
#define PHYSICS_BUFFER_H


class PhysicsBuffer {
public:
	static float time;
	std::vector<PhysicsDrawable*> buffer;
	void addObject(PhysicsDrawable*);
	inline static void CollisionResponse(PhysicsDrawable*, PhysicsDrawable*);
	void Loop();
	bool set = true;
};

float PhysicsBuffer::time = 0.0f;

void PhysicsBuffer::CollisionResponse(PhysicsDrawable* obj1, PhysicsDrawable* obj2) {
	PhysicsDrawable* dy;
	if (obj1->isDynamic)
		dy = obj1;
	else
		dy = obj2;
	vec3f v = dy->getVelocity();
	dy->applyImpulse(vec3f(0.0f, v.y, 0.0f) * -1000000.f * Params::GRAVITY * dy->getMass(), 1.0f);
}

void PhysicsBuffer::addObject(PhysicsDrawable* obj) {
	buffer.push_back(obj);
}
void PhysicsBuffer::Loop() {
	for (unsigned int i = 0; i < buffer.size() - 1;i++) {
		for (unsigned int j = i + 1; j < buffer.size(); j++) {
			PhysicsDrawable* obj1 = buffer[i];
			PhysicsDrawable* obj2 = buffer[j];
			if (!(obj1->isDynamic || obj2->isDynamic))
				continue;
			if (AABB_Collision(obj1, obj2)) {
				PhysicsBuffer::CollisionResponse(obj1, obj2);
			}
			else {
			
			}
		}
	}
	time += Params::TIMESTEP;
}


#endif;
