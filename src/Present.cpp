#include "Present.h"

Present::Present()
{}
//-------------------------------------------
Present::Present(const sf::Sprite sprite)
	: VariableStaticObj::VariableStaticObj(sprite)
{}
//------------------------------
bool Present::isTaken() const
{
	return m_isTaken;
}
//-------------------------------------------