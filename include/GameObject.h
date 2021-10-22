#pragma once
#include "Utilities.h"
#include "Sounds.h"

class Player;
class Wall;
class EnemyBoring;
class EnemyRandom;
class EnemySmart;
class Floor;
class Coin;
class Ladder;
class Pole;
class PresentGood;
class PresentBad;

class GameObject
{
public:
	GameObject();
	GameObject(const sf::Sprite sprite);
	virtual ~GameObject() = default;

	void Draw(sf::RenderWindow& window) const;

	bool collidesWith(GameObject& gameObject) const;

	virtual void handleCollision(GameObject& gameObject) = 0;
	virtual void handleCollision(Wall& gameObject) = 0;
	virtual void handleCollision(Player& gameObject) = 0;
	virtual void handleCollision(EnemyBoring& gameObject) = 0;
	virtual void handleCollision(EnemyRandom& gameObject) = 0;
	virtual void handleCollision(EnemySmart& gameObject) = 0;
	virtual void handleCollision(Floor& gameObject) = 0;
	virtual void handleCollision(Coin& gameObject) = 0;
	virtual void handleCollision(Ladder& gameObject) = 0;
	virtual void handleCollision(Pole& gameObject) = 0;
	virtual void handleCollision(PresentGood& gameObject) = 0;
	virtual void handleCollision(PresentBad& gameObject) = 0;

	void setLocation(sf::Vector2f location);
	void setSprite(sf::Sprite sprite);
	void setLastLocation(sf::Vector2f location);
	void setInPit();
	void setNotInPit();

	sf::Vector2f getLocation()const;
	sf::Vector2f getLastLocation() const;
	bool getIsInPitStatus() const;
	bool isDisposed() const;
protected:
	sf::Sprite m_sprite;
	bool m_isDisposed = false;
private:
	sf::Vector2f m_LastLocation;
	bool m_isInPit = false;
};
