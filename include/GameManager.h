#pragma once
#include "Utilities.h"
#include "Board.h"
#include "Sounds.h"

class GameManager
{
public:
	GameManager();
	void Run();

private:
	/// <private functions>
	void setSizeWindow(const sf::Vector2f size);
	void setBackgroundMusic();
	void handleLooseLevel();
	void handleWinLevel();
	void welcomeWindow();
	void winLevel();
	void looseGame();
	void winGame();
	void setMessage(sf::Text& msg, const char* str);
	void setLevelText(sf::Text& msg);
	void setLifeText(sf::Text& msg);
	void setScoreText(sf::Text& msg);
	void setMaxTimeText(sf::Text& msg);
	void setRunTimeText(sf::Text& msg);
	void setCoinsText(sf::Text& msg);
	/// </ end private functions>

	sf::RenderWindow m_window;
	Board m_board;
	sf::Clock m_clock;
	sf::Clock m_clockRunning;
	sf::Time m_timeRunning;
	sf::Music m_music;
	sf::Vector2f m_MousePos;
	sf::Event m_event;
	int m_counterLevels;
};
