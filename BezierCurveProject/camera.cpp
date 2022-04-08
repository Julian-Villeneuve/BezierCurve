#include "Camera.h"
#include <iostream>

Camera::Camera(float width, float height, glm::vec3 position) : _width(width), _height(height)
{
	_yaw = -90.0f;
	_pitch = 0.0f;
	_zoom = -3.0f;
	_position = position;
	_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	_cameraRight = glm::cross(_cameraFront, _cameraUp);

	_projection = glm::mat4(1.0f);
	_projection = glm::perspective(glm::radians(45.0f), _width / _height, 0.1f, 1000.0f);
	_view = glm::lookAt(_position, _position + _cameraFront, _cameraUp);
}

void Camera::resize(float width, float height)
{
	_width = width;
	_height = height;
	_projection = glm::mat4(1.0f);
	_projection = glm::perspective(glm::radians(45.0f), _width / _height, 0.01f, 100.0f);
}

void Camera::translate(glm::vec3 translation)
{
	float x = translation.x;
	float y = translation.y;
	float z = translation.z;

	_position += (x * _cameraRight);
	_position += (y * _cameraUp);
	_position += (z * _cameraFront);
}

void Camera::rotate(float yaw, float pitch) {
	_yaw += yaw;
	_pitch += pitch;
	_pitch = glm::clamp(_pitch, -89.0f, 89.0f);
	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_cameraFront = glm::normalize(front);
	_cameraRight = glm::normalize(glm::cross(_cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	_cameraUp = glm::normalize(glm::cross(_cameraRight, _cameraFront));
}

void Camera::lookAt(glm::vec3 target) {
	//compute new camera axis
	_cameraFront = glm::normalize(target - _position);
	_cameraRight = glm::normalize(glm::cross(_cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	_cameraUp = glm::normalize(glm::cross(_cameraRight, _cameraFront));
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(_position, _position + _cameraFront, _cameraUp);
}

float Camera::getZoom()
{
	return _zoom;
}

void Camera::mousePressEvent(MouseButton button, float xPos, float yPos)
{
	if (button == RightClick) {
		_previousX = xPos;
		_previousY = yPos;
	}
}

void Camera::mouseReleaseEvent(MouseButton button, float xPos, float yPos)
{

}

void Camera::mouseMoveEvent(MouseButton button, float xPos, float yPos)
{
	if (button == RightClick) {
		_position = glm::vec3(0.0f, 0.0f, 0.0f);
		lookAt(glm::vec3(0.0f, 0.0f, 1.0f));
		rotate(-(_previousX - xPos) * 0.4f, (_previousY - yPos) * 0.4f);
		translate(glm::vec3(0.0f, 0.0f, _zoom));
		_previousX = xPos;
		_previousY = yPos;

	}
}

void Camera::wheelEvent(float y, float x)
{
	float increment = (y > 0.0f) ? 0.05f : -0.05f;
	_zoom += increment;
	translate(glm::vec3(0.0f, 0.0f, increment));
}

