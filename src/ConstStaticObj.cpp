#include "ConstStaticObj.h"

ConstStaticObj::ConstStaticObj()
{
}
//----------------------------------------------------
ConstStaticObj::ConstStaticObj(const sf::Sprite sprite)
	: StaticObject::StaticObject(sprite)
{}
//-----------------------------------------