#pragma once
#include <SFML/Graphics.hpp>

class camera_controller
{
private:
	sf::Vector2f m_cameraControllerXy;
	float m_cameraControllerSpeed = 5.f;

public:
	camera_controller();
	camera_controller(const sf::Vector2f center_pos, sf::Vector2f camera_size);

	//void set_camera_controller_xy(sf::Vector2f);
	void SetCameraControllerSpeed(float);

	sf::Vector2f GetCameraControllerPos();
	sf::Vector2f GetCameraControllerXy();
	float GetCameraControllerSpeed();

	void MoveCameraController(sf::Keyboard::Key);

	sf::View m_cameraView;
};