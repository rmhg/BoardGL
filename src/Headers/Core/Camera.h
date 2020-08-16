#ifndef CAMERA_H
#define CAMERA_H


class Camera {

private :
	vec3f right, up, down,pos;
	Matrix<float> view;
public:
	bool on = false;

	Camera();
	void setOrigin(vec3f);

	void moveUp(float);
	void moveDown(float);
	void moveLeft(float);
	void moveRight(float);

	void moveAhead(float);
	void moveBack(float);

	void rotX(float);
	void rotY(float);
	void rotZ(float);

	Matrix<float>& getView();
};

Camera::Camera() {
	on = true;
	view = Matrix<float>::getIdentity(4);
}


void Camera::setOrigin(vec3f org) {
}

void Camera::moveUp(float mag) {
	view *= Transform::Translate(vec3f(0.0f, mag, 0.0f));
}
void Camera::moveDown(float mag) {
	view *= Transform::Translate(vec3f(0.0f, -mag, 0.0f));
}
void Camera::moveLeft(float mag) {
	view *= Transform::Translate(vec3f(-mag, 0.0f, 0.0f));
}
void Camera::moveRight(float mag) {
	view *= Transform::Translate(vec3f(mag, 0.0f, 0.0f));
}

void Camera::moveAhead(float mag) {
	view *= Transform::Translate(vec3f(0.0f, 0.0f, -mag));
}
void Camera::moveBack(float mag) {
	view *= Transform::Translate(vec3f(0.0f, 0.0f, mag));
}

void Camera::rotX(float deg) {
	view *= Transform::Rotate(vec3f(1.0f, 0.0f, 0.0f), deg);
}
void Camera::rotY(float deg) {
	view *= Transform::Rotate(vec3f(0.0f, 1.0f, 0.0f), deg);
}
void Camera::rotZ(float deg) {
	view *= Transform::Rotate(vec3f(0.0f, 0.0f, 1.0f), deg);
}

Matrix<float>& Camera::getView() {
	return view;
}




#endif
