#include "Wall.h"


Wall::Wall()
{}
//-------------------------------------------
Wall::Wall(const sf::Sprite sprite)
	: ConstStaticObj::ConstStaticObj(sprite)
{ }
//--------------------------------------------
void Wall::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	gameObject.handleCollision(*this);
}
//---------------------------------------------
void Wall::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}
//------------------------------------------
void Wall::handleCollision(EnemyBoring& gameObject)
{
	gameObject.handleCollision(*this);
}
//------------------------------------------------
void Wall::handleCollision(EnemyRandom& gameObject)
{
	gameObject.handleCollision(*this);
}
//---------------------------------------
void Wall::handleCollision(EnemySmart& gameObject)
{
	gameObject.handleCollision(*this);
}
//---------------------------------------
