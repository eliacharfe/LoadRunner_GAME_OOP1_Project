#include "GameManager.h"

GameManager::GameManager() : m_window(sf::VideoMode(DEF_SIZE_WINDOW, DEF_SIZE_WINDOW),
	                         "DEFAULT", sf::Style::Default), m_counterLevels(1), m_event(sf::Event())
{ }
//----------------------------------------------
void GameManager::Run()
{
	welcomeWindow(); // open a welcome window with menu options
	m_board.openFile(); // open the file
	setSizeWindow(m_board.getSize()); // making size of window according to the current level board
	m_board.allocateBoard(); //allocate the board according to the level
	setBackgroundMusic();

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("bg.jfif");
	sf::RectangleShape Background;
	Background.setTexture(&backgroundTexture); // set background image
	Background.setSize(sf::Vector2f(m_board.getSize().x * OBJECT_SIZE, m_board.getSize().y * OBJECT_SIZE));
	/// <text data handle>
	auto font = Image::instance().getFont();
	sf::Text Message, Level, Life, Score, MaxTime, RunTime, Coins;
	Message.setFont(font);    Level.setFont(font);      Life.setFont(font); // set font
	Score.setFont(font);      MaxTime.setFont(font);    RunTime.setFont(font); Coins.setFont(font);
	setMessage(Message, "  Level: \t\n\n  Life: \t\n\n  Score: \t\n\n  MTime: \t\n\n  RTime: \t\n\n  Coins:\t\n");
	setLevelText(Level);      setLifeText(Life);     setScoreText(Score);     
	setMaxTimeText(MaxTime);  setRunTimeText(RunTime);  setCoinsText(Coins);
	/// </end text data handle>
	m_clock.restart(); // for movement
	m_clockRunning.restart();// for time of the level

	while (m_window.isOpen())
	{
		m_timeRunning = m_clockRunning.getElapsedTime(); // for time running of the level
		const auto currTime = m_clock.restart();// for speed move

		m_window.clear();
		m_window.draw(Background); // draw background image
		m_board.Update(currTime, m_timeRunning); // move and update
		m_board.Draw(m_window); // draw game objects
		m_window.draw(Message); m_window.draw(Level);   m_window.draw(Life); // text data
		m_window.draw(Score);   m_window.draw(MaxTime); m_window.draw(RunTime); m_window.draw(Coins);//text data
		m_window.display();

		while (m_window.pollEvent(m_event))
		{
			switch (m_event.type) {
			case sf::Event::Closed:
				m_window.close();	break;
			case sf::Event::KeyPressed:
				if (m_event.key.code == sf::Keyboard::X) // right pit
					m_board.floorDigged(sf::Vector2f(1, 0));
				if (m_event.key.code == sf::Keyboard::Z) // left pit
					m_board.floorDigged(sf::Vector2f(-1, 0));
				if (m_event.key.code == sf::Keyboard::Escape)
					exit(EXIT_SUCCESS);
				break;
			}
		}

		if (m_board.getRestartLevel()) // if true --> loose level --> restart level
			handleLooseLevel();
		if (m_board.getLevelStatus())
		{ // if true --> win level --> next level
			handleWinLevel();
			m_clock.restart();
			Background.setSize(sf::Vector2f(m_board.getSize().x * OBJECT_SIZE, m_board.getSize().y * OBJECT_SIZE));
			/// <text position handle according to the new board of the level>
			Message.setPosition(m_board.getSize().x * OBJECT_SIZE                    , OBJECT_SIZE);
			Level.setPosition(m_board.getSize().x   * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE);
			Life.setPosition(m_board.getSize().x    * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE * 2.7);
			Score.setPosition(m_board.getSize().x   * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE * 4.3);
			MaxTime.setPosition(m_board.getSize().x * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE * 6);
			RunTime.setPosition(m_board.getSize().x * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE * 7.7);
			Coins.setPosition(m_board.getSize().x   * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE * 9.3);
			/// </end text position handle...>
		}
		/// <update data text>
		Level.setString(to_string(m_board.getLevel())); Life.setString(to_string(m_board.getLife()));
		Score.setString(to_string(m_board.getScore())); MaxTime.setString(to_string((int)m_board.getTime()));
		RunTime.setString(to_string((int)m_timeRunning.asSeconds())); Coins.setString(to_string(m_board.getCoins()));
		/// </end update data text>
	}
}
//----------------------------------------------------
void GameManager::setSizeWindow(const sf::Vector2f size)
{ /*making size of window according to the current level board*/
	m_window.create(sf::VideoMode((int)(size.x * OBJECT_SIZE + 300), (int)(size.y * OBJECT_SIZE)),
		"LOAD RUNNER", sf::Style::Close | sf::Style::Titlebar);
}
//--------------------------------------------
void GameManager::setBackgroundMusic()
{
	m_music.openFromFile("musicBackground.ogg");// set background music
	m_music.setLoop(true);
	m_music.play();
}
//-----------------------------------
void GameManager::handleLooseLevel()
{
	m_music.pause();// pause background music (loose music is playing)
	m_board.setRestartLevel();
	m_timeRunning = m_clockRunning.restart();
	if (m_board.getEndGame())
		looseGame();//if no life --> Game Over
	m_music.play();
}
//-----------------------------------
void GameManager::handleWinLevel()
{
	m_music.pause(); // pause background music (win sound is playing)
	m_board.setLevelStatus();
	m_counterLevels++; // for check if it is a bonus level
	if (m_counterLevels == 3 && m_board.getLevel() == 3 || m_counterLevels == 6 && m_board.getLevel() == 5) {
		m_board.setLevel(-1)/* m_level -= 1 */; // --> bonus level
		Player::setLevelNum(m_board.getLevel());
	}
	setSizeWindow(m_board.getSize());// making size of window according to the current level board
	if (m_board.getWinGame())
		winGame(); // win the entire game!
	winLevel();//win curr level --> open a window menu between levels
	m_timeRunning = m_clockRunning.restart();
	m_music.play();
}
//------------------------------------------------------
void GameManager::welcomeWindow()
{ /* a welcome window for start game (or exit)*/
	sf::RenderWindow welcomeWindow(sf::VideoMode(DEF_SIZE_WINDOW, DEF_SIZE_WINDOW),
		                           "WELCOME TO LOAD RUNNER", sf::Style::Default);
	Sounds::instance().makeSound(WIN);

	auto font = Image::instance().getFont();
	sf::Text Message;
	Message.setFont(font); 
	setMessage(Message, "   Welcome to LOAD RUNNER!"
		"\n\nPress P / Space to start the game...\n    Press E / Escape to Exit game...\n\n\n\n\n\n\n    Or Click on Accurate Button");
	Message.setCharacterSize(CHARACTER_SIZE);
	Message.setOutlineColor(sf::Color::Black);
	Message.setFillColor(sf::Color::White);
	Message.setPosition(MSG_X_POS, MSG_Y_POS); 
	
	sf::Sprite spritePlayButton = Image::instance().getSprite(PLAY_BUTTON);
	spritePlayButton.setPosition(200, 500);
	sf::Sprite spriteQuitButton = Image::instance().getSprite(QUIT_BUTTON);
	spriteQuitButton.setPosition(600, 500);

	sf::Texture background;
	background.loadFromFile("welcomeImage.jpg");
	sf::RectangleShape recBackground;
	recBackground.setTexture(&background);
	recBackground.setSize(sf::Vector2f(DEF_SIZE_WINDOW, DEF_SIZE_WINDOW));

	while (welcomeWindow.isOpen())
	{
		welcomeWindow.clear();
		welcomeWindow.draw(recBackground);
		welcomeWindow.draw(Message);
		welcomeWindow.draw(spritePlayButton);
		welcomeWindow.draw(spriteQuitButton);
		welcomeWindow.display();

		while (welcomeWindow.pollEvent(m_event))
		{
			switch (m_event.type)
			{
			case sf::Event::Closed: 
				welcomeWindow.close(); 	break; 
			case sf::Event::KeyReleased: {
				if (m_event.key.code == sf::Keyboard::E || m_event.key.code == sf::Keyboard::Escape) {
					exit(EXIT_SUCCESS);
				}
				if (m_event.key.code == sf::Keyboard::P || (m_event.key.code == sf::Keyboard::Space)) {
					welcomeWindow.close();
				}
				break;
			}
			case sf::Event::MouseButtonReleased: {
				m_MousePos = welcomeWindow.mapPixelToCoords(sf::Mouse::getPosition(welcomeWindow));
				if (spritePlayButton.getGlobalBounds().contains(m_MousePos)) {
					welcomeWindow.close();
				}
				if (spriteQuitButton.getGlobalBounds().contains(m_MousePos)) {
					exit(EXIT_SUCCESS);
				}
				break;
			}
			}
		}
	}
}
//-----------------------------------------
void GameManager::winLevel()
{
	sf::RenderWindow winWindow(sf::VideoMode(DEF_SIZE_WINDOW, DEF_SIZE_WINDOW),
		                                     "WIN LEVEL", sf::Style::Default);
	Sounds::instance().makeSound(WIN);

	auto font = Image::instance().getFont();
	sf::Text Message;
	Message.setFont(font);
	setMessage(Message, "   \tCongratulation! \n\t\t\tYou win the Level! \n\nPress P / Space to start the game...\n    Press E / Escape to Exit game...\n\n\n\n\n\n\n    Or Click on Accurate Button\n");
	Message.setCharacterSize(CHARACTER_SIZE);
	Message.setOutlineColor(sf::Color::Black);
	Message.setFillColor(sf::Color::White);
	Message.setPosition(MSG_X_POS, MSG_Y_POS);

	sf::Sprite spritePlayButton = Image::instance().getSprite(PLAY_BUTTON);
	spritePlayButton.setPosition(200, 520);
	sf::Sprite spriteQuitButton = Image::instance().getSprite(QUIT_BUTTON);
	spriteQuitButton.setPosition(600, 520);

	sf::Texture background;
	background.loadFromFile("BackgroundC.jpg");
	sf::RectangleShape recBackground;
	recBackground.setTexture(&background);
	recBackground.setSize(sf::Vector2f(DEF_SIZE_WINDOW, DEF_SIZE_WINDOW));

	while (winWindow.isOpen())
	{
		while (winWindow.pollEvent(m_event))
		{
			switch (m_event.type)
			{
			case sf::Event::Closed:
				winWindow.close(); break;
			case sf::Event::KeyReleased: {
				if (m_event.key.code == sf::Keyboard::E || m_event.key.code == sf::Keyboard::Escape) {
					exit(EXIT_SUCCESS);
				}
				if (m_event.key.code == sf::Keyboard::P || (m_event.key.code == sf::Keyboard::Space)) {
					winWindow.close();
				}
				break;
			}
			case sf::Event::MouseButtonReleased: {
				m_MousePos = winWindow.mapPixelToCoords(sf::Mouse::getPosition(winWindow));
				if (spritePlayButton.getGlobalBounds().contains(m_MousePos)) {
					winWindow.close();
				}
				if (spriteQuitButton.getGlobalBounds().contains(m_MousePos)) {
					exit(EXIT_SUCCESS);
				}
				break;
			}
			}
		}
		winWindow.clear();
		winWindow.draw(recBackground);
		winWindow.draw(Message);
		winWindow.draw(spritePlayButton);
		winWindow.draw(spriteQuitButton);
		winWindow.display();
	}
}
//-------------------------------------------------------
void GameManager::looseGame()
{
	sf::RenderWindow looseGameWindow(sf::VideoMode(DEF_SIZE_WINDOW, DEF_SIZE_WINDOW),
		"LOOSE GAME", sf::Style::Default);

	Sounds::instance().makeSound(LOOSE);

	auto font = Image::instance().getFont();
	sf::Text Message;
	Message.setFont(font);
	setMessage(Message, "   \tYou Loose! \n\n\n\n\n\n\n\n\n\n Press E / Escape to Exit game...\n Or Click On Exit Button");
	Message.setCharacterSize(CHARACTER_SIZE);
	Message.setFillColor(sf::Color::White);
	Message.setPosition(MSG_X_POS, MSG_Y_POS);

	sf::Sprite spriteQuitButton = Image::instance().getSprite(QUIT_BUTTON);
	spriteQuitButton.setPosition(700, 820);

	sf::Texture background;
	background.loadFromFile("gameOverImage.jpg");
	sf::RectangleShape recBackground;
	recBackground.setTexture(&background);
	recBackground.setSize(sf::Vector2f(DEF_SIZE_WINDOW, DEF_SIZE_WINDOW));

	while (looseGameWindow.isOpen())
	{
		while (looseGameWindow.pollEvent(m_event))
		{
			switch (m_event.type)
			{
			case sf::Event::Closed:
				exit(EXIT_SUCCESS); break;
			case sf::Event::KeyReleased:
			{
				if (m_event.key.code == sf::Keyboard::E || m_event.key.code == sf::Keyboard::Escape) {
					exit(EXIT_SUCCESS);
				}
				break;
			}
			case sf::Event::MouseButtonReleased: {
				m_MousePos = looseGameWindow.mapPixelToCoords(sf::Mouse::getPosition(looseGameWindow));
				if (spriteQuitButton.getGlobalBounds().contains(m_MousePos)) {
					exit(EXIT_SUCCESS);
				}
				break;
			}
			}
		}
		looseGameWindow.clear();
		looseGameWindow.draw(recBackground);
		looseGameWindow.draw(Message);
		looseGameWindow.draw(spriteQuitButton);
		looseGameWindow.display();
	}
}
//--------------------------------------------
void GameManager::winGame()
{
	sf::RenderWindow winGameWindow(sf::VideoMode(DEF_SIZE_WINDOW, DEF_SIZE_WINDOW),
		"WIN THE GAME", sf::Style::Default);

	Sounds::instance().makeSound(WIN_GAME);

	auto font = Image::instance().getFont();
	sf::Text Message;
	Message.setFont(font);
	setMessage(Message, "     You Won The Game!!!  \n\n\n\n\n\n\n\n\n\n\n Press E / Escape to Exit game...\n Or Click On Exit Button");
	Message.setCharacterSize(CHARACTER_SIZE);
	Message.setPosition(MSG_X_POS, MSG_Y_POS);
	Message.setFillColor(sf::Color::Yellow);
	Message.setOutlineColor(sf::Color::Green);

	sf::Sprite spriteQuitButton = Image::instance().getSprite(QUIT_BUTTON);
	spriteQuitButton.setPosition(700, 850);

	sf::Texture background;
	background.loadFromFile("winGame.png");
	sf::RectangleShape recBackground;
	recBackground.setTexture(&background);
	recBackground.setSize(sf::Vector2f(DEF_SIZE_WINDOW, DEF_SIZE_WINDOW));

	while (winGameWindow.isOpen())
	{
		while (winGameWindow.pollEvent(m_event))
		{
			switch (m_event.type)
			{
			case sf::Event::Closed:
				exit(EXIT_SUCCESS); break;
			case sf::Event::KeyReleased: {
				if (m_event.key.code == sf::Keyboard::E || m_event.key.code == sf::Keyboard::Escape) {
					cout << "\nYou pressed Q / Escape\nExit Game!\n";
					exit(EXIT_SUCCESS);
				}
				break;
			}
			case sf::Event::MouseButtonReleased: {
				m_MousePos = winGameWindow.mapPixelToCoords(sf::Mouse::getPosition(winGameWindow));
				if (spriteQuitButton.getGlobalBounds().contains(m_MousePos)) {
					exit(EXIT_SUCCESS);
				}
				break;
			}
			}
		}
		winGameWindow.clear();
		winGameWindow.draw(recBackground);
		winGameWindow.draw(Message);
		winGameWindow.draw(spriteQuitButton);
		winGameWindow.display();
	}
}
//------------------------------------
void GameManager::setMessage(sf::Text& msg, const char* str)
{
	msg.setCharacterSize(CHARACTER_SIZE_TEXT);
	msg.setFillColor(sf::Color::Black);
	msg.setPosition(m_board.getSize().x * OBJECT_SIZE, (OBJECT_SIZE));
	msg.setOutlineThickness(OUTLINE_THIKNESS);
	msg.setOutlineColor(sf::Color::Green);
	msg.setString(str);
}
//--------------------------------------------
void GameManager::setLevelText(sf::Text& msg)
{
	msg.setCharacterSize(CHARACTER_SIZE_TEXT);
	msg.setFillColor(sf::Color::White);
	msg.setOutlineThickness(OUTLINE_THIKNESS);
	msg.setOutlineColor(sf::Color::Magenta);
	msg.setPosition(m_board.getSize().x * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE);
}
//--------------------------------
void GameManager::setLifeText(sf::Text& msg)
{
	msg.setCharacterSize(CHARACTER_SIZE_TEXT);
	msg.setFillColor(sf::Color::White);
	msg.setOutlineThickness(OUTLINE_THIKNESS);
	msg.setOutlineColor(sf::Color::Magenta);
	msg.setPosition(m_board.getSize().x * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE * 2.7);
}
//--------------------------------
void GameManager::setScoreText(sf::Text& msg)
{
	msg.setCharacterSize(CHARACTER_SIZE_TEXT);
	msg.setFillColor(sf::Color::White);
	msg.setOutlineThickness(OUTLINE_THIKNESS);
	msg.setOutlineColor(sf::Color::Magenta);
	msg.setPosition(m_board.getSize().x * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE * 4.3);
}
//-----------------------------------------------
void GameManager::setMaxTimeText(sf::Text& msg)
{
	msg.setCharacterSize(CHARACTER_SIZE_TEXT);
	msg.setFillColor(sf::Color::White);
	msg.setOutlineThickness(OUTLINE_THIKNESS);
	msg.setOutlineColor(sf::Color::Cyan);
	msg.setPosition(m_board.getSize().x * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE * 6);
}
//----------------------------------------------
void GameManager::setRunTimeText(sf::Text& msg)
{
	msg.setCharacterSize(CHARACTER_SIZE_TEXT);
	msg.setFillColor(sf::Color::White);
	msg.setOutlineThickness(OUTLINE_THIKNESS);
	msg.setOutlineColor(sf::Color::Cyan);
	msg.setPosition(m_board.getSize().x * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE * 7.7);
}
//------------------------------------------
void GameManager::setCoinsText(sf::Text& msg)
{
	msg.setCharacterSize(CHARACTER_SIZE_TEXT);
	msg.setFillColor(sf::Color::White);
	msg.setOutlineThickness(OUTLINE_THIKNESS);
	msg.setOutlineColor(sf::Color::Yellow);
	msg.setPosition(m_board.getSize().x * OBJECT_SIZE + (3 * OBJECT_SIZE), OBJECT_SIZE * 9.3);
}
//---------------------------------------------
