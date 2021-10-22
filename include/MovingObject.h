#pragma once
#include "Utilities.h"
#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	MovingObject();
	MovingObject(const sf::Sprite sprite);
	virtual ~MovingObject() = default;

	virtual void Move(const sf::Time& currTime) = 0;

protected:
	sf::Vector2f m_direction;
	sf::Vector2f m_lastLocation;
private:
	
};
