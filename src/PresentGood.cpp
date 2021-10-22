#include "PresentGood.h"
#include "EnemySmart.h"

bool PresentGood::m_isPresentTaken = false;

PresentGood::PresentGood()
{}
//-------------------------------------------
PresentGood::PresentGood(const sf::Sprite sprite)
	: Present::Present(sprite)
{
}
//-----------------------------------------------
void PresentGood::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	gameObject.handleCollision(*this);
}
//----------------------------------------------
void PresentGood::handleCollision(Player& gameObject)
{
	Sounds::instance().makeSound(PRESENT);
	m_isPresentTaken = true;
	m_isDisposed = true;
	gameObject.handleCollision(*this);
}
//------------------------------------
void PresentGood::handleCollision(EnemySmart& gameObject)
{
	gameObject.handleCollision(*this);
}
//---------------------------------------

void PresentGood::setPresentTakenStatus() // static function
{
	m_isPresentTaken = false;
}
//----------------------------------------
bool PresentGood::getPresentTakenStatus()// static function
{
	return m_isPresentTaken;
}
//--------------------------------------
