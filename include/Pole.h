#pragma once
#include "ConstStaticObj.h"


class Pole : public ConstStaticObj
{
public:
	Pole();
	Pole(const sf::Sprite sprite);

	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Wall& gameObject) override {};
	void handleCollision(Player& gameObject)  override ;
	void handleCollision(EnemyBoring& gameObject)  override {};
	void handleCollision(EnemyRandom& gameObject)  override {};
	void handleCollision(EnemySmart& gameObject)  override ;
	void handleCollision(Floor& gameObject) override {};
	void handleCollision(Coin& gameObject) override {};
	void handleCollision(Ladder& gameObject) override {};
	void handleCollision(Pole& gameObject) override {};
	void handleCollision(PresentGood& gameObject) override {};
	void handleCollision(PresentBad& gameObject) override {};

private:
};
