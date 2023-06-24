#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;

	int m_width, m_height;
	float m_fov;
	float m_yaw, m_pitch;

	float m_speed;

	float m_sensitivity;
	float last_x, last_y;

	bool firstMouse;

public:
	Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, int w, int h)
		: m_position(pos), m_front(front), m_up(up), m_speed(0.01f), 
		m_sensitivity(0.05f), m_width(w), m_height(h), m_fov(45.f),
		firstMouse(true) {
		m_pitch = glm::degrees(-asin(m_front.y));
		m_yaw = glm::degrees(atan2(m_front.z, m_front.x));
		last_x = 0;
		last_y = 0;
		}
	~Camera() {}

	inline glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(m_position, m_position + m_front, m_up);
	}

	inline glm::mat4 GetProjectionMatrix()
	{
		return glm::perspective(glm::radians(m_fov), (float)m_width / (float)m_height, 0.1f, 100.f);
	}

	void ProcessMouseWheelEvent(const float& x, const float& y);

	void ProcessInputs(const uint8_t* keyState, const float& mouse_x, const float& mouse_y);
};