#include "StaticObject.h"

StaticObject::StaticObject()
{
}
//----------------------------------------------------
StaticObject::StaticObject(const sf::Sprite sprite)
	: GameObject::GameObject(sprite)
{
}
//------------------------------------------
void StaticObject::setUnDrawable()
{
	m_isUndrawable = true;
}
//---------------------------
void StaticObject::setDrawable()
{
	m_isUndrawable = false;
}
//-------------------------------
void StaticObject::setTime()
{
	m_clock.restart();
}
//--------------------------------------------
bool StaticObject::getUnDrawableStatus() const
{
	return m_isUndrawable;
}
//--------------------------------------
sf::Time StaticObject::getTime() const
{
	return m_clock.getElapsedTime();
}
//-------------------------------------