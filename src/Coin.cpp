#include "Coin.h"
#include "EnemySmart.h"

int Coin::m_coins = 0;

Coin::Coin()
{}
//-------------------------------------------
Coin::Coin(const sf::Sprite sprite)
	: Present::Present(sprite)
{
	m_coins++;
}
//-------------------------------------
Coin::~Coin()
{
	m_coins--;
}
//-----------------------------------------
void Coin::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this)
		return;
	gameObject.handleCollision(*this);
}
//------------------------------------
void Coin::handleCollision(Wall& gameObject)
{
}
//-------------------------------------------
void Coin::handleCollision(Player& gameObject)
{
	Sounds::instance().makeSound(COIN);
	m_isDisposed = true; // for delete
	gameObject.handleCollision(*this);
}
//------------------------------------------------
void Coin::handleCollision(EnemyBoring& gameObject)
{
}
//--------------------------------------------
void Coin::handleCollision(EnemyRandom& gameObject)
{
}
void Coin::handleCollision(EnemySmart& gameObject)
{
	gameObject.handleCollision(*this);
}
//-----------------------------------------
void Coin::handleCollision(Floor& gameObject)
{
}
//-------------------------------------------
void Coin::handleCollision(Coin& gameObject)
{
}
//------------------------------------
void Coin::handleCollision(Ladder& gameObject)
{
}
//-----------------------------------
void Coin::handleCollision(Pole& gameObject)
{
}
//------------------------------------------------
void Coin::handleCollision(PresentGood& gameObject)
{
}
//--------------------------
void Coin::handleCollision(PresentBad& gameObject)
{
}
//----------------------
int Coin::getCoin()// static function
{
	return m_coins;
}
//----------------------------------