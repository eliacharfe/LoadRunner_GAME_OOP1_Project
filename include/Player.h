#pragma once
#include "Utilities.h"
#include "MovingObject.h"
#include "Sounds.h"
#include "Pole.h"
#include "Ladder.h"
#include "Coin.h"
#include "PresentGood.h"
#include "PresentBad.h"

class Board;

class Player : public MovingObject
{
public:
	Player() ;
	Player(const Board& board);
	Player(const sf::Sprite sprite, const Board& board)  ;

	void Move(const sf::Time& currTime) override;

	void handleCollision(GameObject& gameObject) override ;
	void handleCollision(Wall& gameObject) override;
	void handleCollision(Player& gameObject)  override {};
	void handleCollision(EnemyBoring& gameObject)  override;
	void handleCollision(EnemyRandom& gameObject)  override;
	void handleCollision(EnemySmart& gameObject)  override;
	void handleCollision(Floor& gameObject) override;
	void handleCollision(Coin& gameObject) override;
	void handleCollision(Ladder& gameObject) override ;
	void handleCollision(Pole& gameObject) override ;
	void handleCollision(PresentGood& gameObject) override {};
	void handleCollision(PresentBad& gameObject) override {};

	void setSpritePlayer(sf::Sprite sprite);

	static void setScore(int score);
	static void setLife(int life);
	static void setDeadStatusFalse();
	static void setDeadStatusTrue();
	static void setLevelNum(int numLevel);

	static int getLife() ;
	static int getScore() ;
	static bool isDead() ;

	sf::Vector2f getPlayerLocation() const;

private:
	void setDirectiomPlayer();

	const Board& m_board;

	static int m_life;
	static int m_score;
	static bool m_isDead ;
	static int m_numLevel;

};