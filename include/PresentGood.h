#pragma once
#include "Present.h"
#include "Player.h"

class PresentGood : public Present
{
public:
	PresentGood();
	PresentGood(const sf::Sprite sprite);

	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Wall& gameObject) override {};
	void handleCollision(Player& gameObject) override ;
	void handleCollision(EnemyBoring& gameObject)  override {};
	void handleCollision(EnemyRandom& gameObject)  override {};
	void handleCollision(EnemySmart& gameObject)  override ;
	void handleCollision(Floor& gameObject) override {};
	void handleCollision(Coin& gameObject) override {};
	void handleCollision(Ladder& gameObject) override {};
	void handleCollision(Pole& gameObject) override {};
	void handleCollision(PresentGood& gameObject) override {};
	void handleCollision(PresentBad& gameObject) override {};

	static void setPresentTakenStatus();
	static bool getPresentTakenStatus();
private:
	static bool m_isPresentTaken;
};
