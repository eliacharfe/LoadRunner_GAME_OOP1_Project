#include "PresentBad.h"
#include "Player.h"
#include "EnemySmart.h"

bool PresentBad::m_isBadPresentTaken = false;

PresentBad::PresentBad()
{}
//-------------------------------------------
PresentBad::PresentBad(const sf::Sprite sprite)
	: Present::Present(sprite)
{}
//--------------------------------------------------
void PresentBad::handleCollision(GameObject & gameObject)
{
	if (&gameObject == this)
		return;
	gameObject.handleCollision(*this);
}
//--------------------------------------------
void PresentBad::handleCollision(Player& gameObject)
{
	Sounds::instance().makeSound(BAD_PRESENT);
	m_isBadPresentTaken = true;
	m_isDisposed = true;
	gameObject.handleCollision(*this);
}
//----------------------------------------
void PresentBad::handleCollision(EnemySmart& gameObject)
{
	gameObject.handleCollision(*this);
}
//---------------------------------------

void PresentBad::setBadPresentStatus() // static function
{
	m_isBadPresentTaken = false;
}
//------------------------------------
bool PresentBad::getBadPresentStatus() // static function
{
	return m_isBadPresentTaken;
}
//------------------------------------------
