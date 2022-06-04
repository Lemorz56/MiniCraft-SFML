#include "CameraController.h"

#include <iostream>

camera_controller::camera_controller()
= default;

camera_controller::camera_controller(const sf::Vector2f center_pos, sf::Vector2f camera_size) //sf::Vector2f(400, 400), sf::Vector2f(200, 200)
{
	m_cameraControllerXy = center_pos;
	m_cameraControllerSpeed = 2.0f;
	m_cameraView = sf::View(center_pos, camera_size);
}

//void camera_controller::set_camera_controller_xy(sf::Vector2f)
//{
//}

void camera_controller::SetCameraControllerSpeed(const float speed)
{
	m_cameraControllerSpeed = speed;
}

sf::Vector2f camera_controller::GetCameraControllerPos()
{
	return {m_cameraControllerXy.x, m_cameraControllerXy.y};
}

sf::Vector2f camera_controller::GetCameraControllerXy()
{
	return {0, 0};
}

float camera_controller::GetCameraControllerSpeed()
{
	return 0;
}

void camera_controller::MoveCameraController(const sf::Keyboard::Key pressedKey) //int, int
{
	std::cout << "Sent: " << pressedKey << std::endl;
	if (pressedKey == sf::Keyboard::LShift)
		m_cameraControllerSpeed = m_cameraControllerSpeed * 3;

	if (pressedKey == sf::Keyboard::W)
		m_cameraView.move(0, -m_cameraControllerSpeed);

	if (pressedKey == sf::Keyboard::A)
		m_cameraView.move(-m_cameraControllerSpeed, 0);

	if (pressedKey == sf::Keyboard::S)
		m_cameraView.move(0, m_cameraControllerSpeed);

	if (pressedKey == sf::Keyboard::D)
		m_cameraView.move(m_cameraControllerSpeed, 0);
}