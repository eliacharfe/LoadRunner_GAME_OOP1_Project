#include "GameObject.h"

GameObject::GameObject()
{ }
//--------------------------------------------
GameObject::GameObject(const sf::Sprite sprite)
	   : m_sprite(sprite)
{ }
//-------------------------------------------------
void GameObject::Draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}
//--------------------------------------------------------
bool GameObject::collidesWith(GameObject& gameObject) const
{
	return m_sprite.getGlobalBounds().intersects(gameObject.m_sprite.getGlobalBounds());
}
//--------------------------------------
void GameObject::setLocation(sf::Vector2f location)
{
	m_sprite.setPosition(location);
}
//------------------------------------------
void GameObject::setSprite(sf::Sprite sprite)
{
	m_sprite = sprite;
}
//---------------------------------------------
void GameObject::setLastLocation(sf::Vector2f location)
{
	m_LastLocation = location;
}
//---------------------------
void GameObject::setInPit()
{
	m_isInPit = true;
}
//---------------------------------
void GameObject::setNotInPit()
{
	m_isInPit = false;
}
//------------------------------
sf::Vector2f GameObject::getLocation() const
{
	return m_sprite.getPosition();
}
//--------------------------------------------------
sf::Vector2f GameObject::getLastLocation() const 
{
	return m_LastLocation;
}
//------------------------------------
bool GameObject::getIsInPitStatus() const
{
	return m_isInPit;
}
//--------------------------------------
bool GameObject::isDisposed() const
{
	return m_isDisposed;
}
//----------------------------------
