#pragma once
#include "VariableStaticObj.h"

class Present : public VariableStaticObj
{
public:
	Present();
	Present(const sf::Sprite sprite);

	bool isTaken() const;
protected:
	bool m_isTaken = false;

private:
};
