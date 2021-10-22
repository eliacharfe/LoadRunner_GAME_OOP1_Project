#include "MovingObject.h"

MovingObject::MovingObject()
{}
//--------------------------------------------
MovingObject::MovingObject(const sf::Sprite sprite)
	: GameObject::GameObject(sprite), m_direction(sf::Vector2f(0, 0)), m_lastLocation(sf::Vector2f(40, 40))
{ }
//----------------------------------------------------