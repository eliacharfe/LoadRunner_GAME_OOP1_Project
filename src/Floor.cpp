#include "Floor.h"

Floor::Floor()
{}
//-------------------------------------------
Floor::Floor(const sf::Sprite sprite)
	: VariableStaticObj::VariableStaticObj(sprite)
{
}
//---------------------------------------------
void Floor::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this)
	  return;
	gameObject.handleCollision(*this);
}
//-----------------------------------------
void Floor::handleCollision(Wall& gameObject)
{
}
//-----------------------------------------
void Floor::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}
//-------------------------------------------------
void Floor::handleCollision(EnemyBoring& gameObject)
{
	gameObject.handleCollision(*this);
}
//---------------------------------------------
void Floor::handleCollision(EnemyRandom& gameObject)
{
	gameObject.handleCollision(*this);
}
//----------------------------------------------
void Floor::handleCollision(EnemySmart& gameObject)
{
	gameObject.handleCollision(*this);
}
//------------------------------------------
void Floor::handleCollision(Floor& gameObject)
{
}
//------------------------------------
void Floor::handleCollision(Coin& gameObject)
{
}
//-----------------------------
void Floor::handleCollision(Ladder& gameObject)
{
}
//----------------------------------
void Floor::handleCollision(Pole& gameObject)
{
}
//--------------------------------------------
void Floor::handleCollision(PresentGood& gameObject)
{
}
//----------------------------------------
void Floor::handleCollision(PresentBad& gameObject)
{
}
//--------------------------------
