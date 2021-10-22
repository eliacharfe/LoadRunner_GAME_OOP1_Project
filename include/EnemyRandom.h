#pragma once
#include "Enemy.h"

class Board;

class EnemyRandom : public Enemy
{
public:
	EnemyRandom(const sf::Sprite sprite , Player* player, const Board& board);

	void Move(const sf::Time& currTime) override;

	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Wall& gameObject) override;
	void handleCollision(Player& gameObject)  override;
	void handleCollision(EnemyBoring& gameObject)  override {};
	void handleCollision(EnemyRandom& gameObject)  override {};
	void handleCollision(EnemySmart& gameObject)  override {};
	void handleCollision(Floor& gameObject) override;
	void handleCollision(Coin& gameObject) override {};
	void handleCollision(Ladder& gameObject) override {};
	void handleCollision(Pole& gameObject) override {};
	void handleCollision(PresentGood& gameObject) override {};
	void handleCollision(PresentBad& gameObject) override {};

private:
	int m_rand;
	sf::Clock m_clock;
};
