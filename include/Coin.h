#pragma once
#include "Present.h"
#include "Sounds.h"
#include "Player.h"

class Coin : public Present
{
public:
	Coin();
	Coin(const sf::Sprite sprite);
	~Coin();

	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Wall& gameObject) override;
	void handleCollision(Player& gameObject)  override;
	void handleCollision(EnemyBoring& gameObject)  override;
	void handleCollision(EnemyRandom& gameObject)  override;
	void handleCollision(EnemySmart& gameObject)  override;
	void handleCollision(Floor& gameObject) override;
	void handleCollision(Coin& gameObject) override;
	void handleCollision(Ladder& gameObject) override;
	void handleCollision(Pole& gameObject) override;
    void handleCollision(PresentGood& gameObject) override;
	void handleCollision(PresentBad& gameObject) override;

	static int getCoin() ;
private:
	static int m_coins;
};
