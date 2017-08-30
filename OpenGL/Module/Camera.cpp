#include "stdafx.h"
#include "Camera.h"

#include <glm/include/glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::setEye(const glm::vec3 &eye)
{
	if (_eye == eye)
		return;

	_isDirty = true;
	_eye = eye;
}

void Camera::lookAt(const glm::vec3 &center)
{
	if (center == _center)
		return;

	_isDirty = true;
	_center = center;
}

glm::mat4 Camera::getViewMatrix()
{
	if (true == _isDirty)
		_viewMat = glm::lookAt(_eye, _center, glm::vec3(0, 1, 0));

	return _viewMat;
}


