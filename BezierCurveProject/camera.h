#pragma once
// most of this camera class copyright : Antoine Lafon

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

enum MouseButton {
	LeftClick = 0,
	RightClick,
	MiddleClick
};

class Camera
{
public:

	Camera(float width, float height, glm::vec3 position);
	void resize(float width, float height);
	void translate(glm::vec3 translation);
	void rotate(float yaw, float pitch);
	void lookAt(glm::vec3 target);
	float Camera::getZoom();

	glm::mat4 getView();
	glm::mat4 getProjection() { return _projection; }
	glm::vec3 getPosition() { return _position; }
	glm::vec3 getDirection() { return _cameraFront; }

	void mousePressEvent(MouseButton button, float xPos, float yPos);
	void mouseReleaseEvent(MouseButton button, float xPos, float yPos);
	void mouseMoveEvent(MouseButton button, float xPos, float yPos);
	void wheelEvent(float y, float x);

	float _width, _height;
	float _zoom;
	glm::mat4 _projection;
	glm::mat4 _view;
	glm::vec3 _position;
private:

	float _yaw, _pitch;
	float _previousX, _previousY;

	glm::vec3 _cameraRight;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraUp;

};

