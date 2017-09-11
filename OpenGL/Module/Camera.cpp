#include "stdafx.h"
#include "Camera.h"

#include <glm/include/glm/gtc/matrix_transform.hpp>

Camera::Camera():
	_yaw(-90.0f), _pitch(0.0f), _roll(0.0f)
{
	_projectionMat = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
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

void Camera::setYaw(double yaw)
{
	if (_yaw == yaw)
		return;

	_isDirty = true;
	_yaw = yaw;
}

double Camera::getYaw()
{
	return _yaw;
}

void Camera::setPitch(double pitch)
{
	if (_pitch == pitch)
		return;

	_isDirty = true;
	_pitch = pitch;
}

double Camera::getPitch()
{
	return _pitch;
}

void Camera::setRoll(double roll)
{
	if (_roll == roll)
		return;

	_isDirty = true;
	_roll = roll;
}

double Camera::getRoll()
{
	return _roll;
}

glm::mat4 Camera::getViewMatrix()
{
	if (true == _isDirty)
	{
		glm::vec3 front(cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)), sin(glm::radians(_pitch)), sin(glm::radians(_yaw)) * cos(glm::radians(_pitch)));
		front = glm::normalize(front);
		_viewMat = glm::lookAt(_eye, _eye + front, glm::vec3(0, 1, 0));
		_isDirty = false;
	}

	return _viewMat;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return _projectionMat;
}

void Camera::move(const glm::vec3 &distance)
{
	_eye += distance;
	_isDirty = true;
}
