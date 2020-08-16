#ifndef COLLISION_H
#define COLLISION_H


namespace BGL {


	struct CObj {
		std::vector<vec3f> ContactPoints;
		vec2f offset;
		bool set = false;
	}cobj;

	bool SAT_Collision(PhysicsDrawable* obj1, PhysicsDrawable* obj2) {
		bool isColliding = false;
		return isColliding;
	}


	bool AABB_Collision(PhysicsDrawable* obj1, PhysicsDrawable* obj2) {
		bool isColliding = false;
		vec3f v11 = obj1->getVertex(0);
		vec3f v12 = obj1->getVertex(1);
		vec3f v14 = obj1->getVertex(2);
		vec3f v21 = obj2->getVertex(0);
		vec3f v22 = obj2->getVertex(1);
		vec3f v24 = obj2->getVertex(3);
		float x11 = v11.x + 1, x12 = v12.x + 1, x21 = v21.x + 1, x22 = v22.x + 1, y11 = 1 - v11.y, y14 = 1 - v14.y, y21 = 1 - v21.y, y24 = 1 - v24.y;
		if (((x11 >= x21 && x11 <= x22) || (x12 >= x21 && x12 <= x22)) && ((y11 >= y21 && y11 <= y24) || (y14 >= y21 && y14 <= y24))) {
			float yoff = y21 - y14;
	
			cobj.offset.y = yoff;
			isColliding = true;
		}
		else {
			isColliding = false;
		}

		

		return isColliding;
	}
	bool Circles_Collision(PhysicsDrawable* obj1, PhysicsDrawable* obj2) {
		bool isColliding = false;
		return isColliding;
	}


}

#endif
