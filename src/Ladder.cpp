#include "Ladder.h"
#include "Player.h"
#include "EnemySmart.h"

Ladder::Ladder()
{}
//-------------------------------------------
Ladder::Ladder(const sf::Sprite sprite)
	: ConstStaticObj::ConstStaticObj(sprite)
{ }
//--------------------------------------
void Ladder::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	gameObject.handleCollision(*this);
}
//------------------------------------
void Ladder::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}
//------------------------------------
void Ladder::handleCollision(EnemySmart& gameObject)
{
	gameObject.handleCollision(*this);
}
//---------------------------------------
