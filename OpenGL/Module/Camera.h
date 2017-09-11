#pragma once

#include <glm/include/glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void setEye(const glm::vec3 &eye);

	void setYaw(double yaw);
	double getYaw();
	void setPitch(double pitch);
	double getPitch();
	void setRoll(double roll);
	double getRoll();


	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void move(const glm::vec3 &distance);


private:
	bool _isDirty;

	double _yaw, _pitch, _roll;
	glm::vec3 _eye;
	glm::mat4 _viewMat, _projectionMat;
};

