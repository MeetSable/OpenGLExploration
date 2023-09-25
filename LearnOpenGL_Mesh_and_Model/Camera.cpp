#include "Camera.h"
#include <cmath>

#include <SDL3/SDL.h>
#include <iostream>

void Camera::ProcessMouseWheelEvent(const float& x, const float& y)
{
	m_fov += y;
	if (m_fov <= 1.0f)
		m_fov = 1.0f;
	else if (m_fov >= 45.f)
		m_fov = 45.f;
}

void Camera::ProcessInputs(const uint8_t* keyState, const float& mouse_x, const float& mouse_y)
{
	if (firstMouse)
	{
		last_x = mouse_x;
		last_y = mouse_y;
		firstMouse = false;
	}

	if (keyState[SDL_SCANCODE_W])
	{
		m_position += m_speed * m_front;
	}
	if (keyState[SDL_SCANCODE_S])
	{
		m_position -= m_speed * m_front;
	}
	if (keyState[SDL_SCANCODE_A])
	{
		m_position -= glm::normalize(glm::cross(m_front, m_up)) * m_speed;
	}
	if (keyState[SDL_SCANCODE_D])
	{
		m_position += glm::normalize(glm::cross(m_front, m_up)) * m_speed;
	}
	if (keyState[SDL_SCANCODE_Q])
	{
		m_position -= m_up * m_speed;
	}
	if (keyState[SDL_SCANCODE_E])
	{
		m_position += m_up * m_speed;
	}
	if (isRightButtonPressed)
	{
		float offset_x = (last_x - mouse_x) * m_sensitivity;
		float offset_y = (mouse_y - last_y) * m_sensitivity;

		m_yaw += offset_x;
		m_pitch += offset_y;

		if (m_pitch >= 89.0f)
			m_pitch = 89.0f;
		else if (m_pitch <= -89.f)
			m_pitch = -89.f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		direction.y = sin(glm::radians(m_pitch));
		direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = glm::normalize(direction);
		// std::cout << "\r(" << m_position.x << ", " << m_position.y << ", " << m_position.z << ")  (" << m_yaw << ", " << m_pitch << ")";
		isRightButtonPressed = false;
	}

	last_x = mouse_x;
	last_y = mouse_y;
}