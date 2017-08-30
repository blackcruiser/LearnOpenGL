#pragma once

#include <glm/include/glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void setEye(const glm::vec3 &eye);
	void lookAt(const glm::vec3 &center);

	glm::mat4 getViewMatrix();


private:
	bool _isDirty;

	glm::vec3 _eye, _center;
	glm::mat4 _viewMat;
};

