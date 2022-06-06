#pragma once
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"
#include "Gui.h"

class MainMenu : public Engine::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_gameTitle;

	// Buttons
	sf::Text m_playButton;
	bool m_isPlayButtonSelected;
	bool m_isPlayButtonPressed;

	sf::Text m_exitButton;
	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;

	// Sound
	sf::SoundBuffer m_buffer;
	sf::Sound m_menuSound;

public:
	MainMenu(std::shared_ptr<Context> &context);
	~MainMenu();

	virtual void Init() override;
	virtual void ProcessInput() override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void Draw() override;
};
