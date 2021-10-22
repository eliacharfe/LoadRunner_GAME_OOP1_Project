#include "Pole.h"
#include "Player.h"
#include "EnemySmart.h"

Pole::Pole()
{}
//-------------------------------------------
Pole::Pole(const sf::Sprite sprite)
	: ConstStaticObj::ConstStaticObj(sprite)
{
}
//---------------------------------
void Pole::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	gameObject.handleCollision(*this);
}
//---------------------------------------
void Pole::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}
//---------------------------------------
void Pole::handleCollision(EnemySmart& gameObject)
{
	gameObject.handleCollision(*this);
}
//---------------------------------------


