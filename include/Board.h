#pragma once
#include "Utilities.h"
#include "GameObject.h"
#include "StaticObject.h"
#include "MovingObject.h"
#include "Wall.h"
#include "Floor.h"
#include "Ladder.h"
#include "Coin.h"
#include "Pole.h"
#include "PresentGood.h"
#include "PresentBad.h"
#include "Player.h"
#include "EnemyBoring.h"
#include "EnemyRandom.h"
#include "EnemySmart.h"
#include "Image.h"
#include "Sounds.h"

class Board
{
public:
	Board(); // c-tor
	void openFile();
	void allocateBoard();

	void Draw(sf::RenderWindow& window) const;
	void Update(const sf::Time& currTime, const sf::Time runTime);
	void floorDigged(const sf::Vector2f direction);

	void setLevel(int level);
	void setLevelStatus();
	void setRestartLevel();
	void setTime(const sf::Time runTime);

	sf::Vector2f getSize() const;
	char getChar(const sf::Vector2f location)const;
	bool getLevelStatus() const;
	bool getRestartLevel() const;
	int getLevel()const;
	int getLife()const;
	int getScore()const;
	float getTime() const;
	int getCoins()const;
	bool getEndGame() const;
	bool getWinGame() const;

private:
	/// <private functions>
	void readLevel();
	void handleCollisions(GameObject& obj);
	void handleFalls(GameObject& obj);
	void handleFallIntoPit(GameObject& obj);
	bool fallIntoRightPit(GameObject& movableObject, int i)const;
	bool fallIntoLeftPit(GameObject& movable, int i)const;
	void checkCoinsStatus();
	void checkPlayerStatus(const sf::Time runTime);
	void checkPresentStatus();
	void createObject(const char c, const sf::Sprite sprite, shared_ptr < Player >);
	shared_ptr< MovingObject > createMovableObject(const char c, const sf::Sprite sprite
		, shared_ptr < Player > player);
	unique_ptr< StaticObject > createUnmovableObject(const char c, const sf::Sprite sprite);
	void winLevel();
	void looseLevel();
	/// </end private functions>

	vector < string > m_charBoard;
	vector < shared_ptr < MovingObject >> m_movables;
	vector < unique_ptr < StaticObject >> m_statics;

	ifstream m_BoardFile;
	streamoff m_startLevelOnTextBoard;
	sf::Sprite m_sprite;
	sf::Vector2f m_sizeBoard;
	float m_time;
	int   m_level;
	int   m_rand;
	bool  m_pitFull = false;
	bool  m_newLevel = false;
	bool  m_restartLevel = false;
	bool  m_endGame = false;
	bool  m_winGame = false;
};
