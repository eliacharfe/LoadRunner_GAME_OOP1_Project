#pragma once
#include "GameObject.h"
#include "Utilities.h"

class StaticObject : public GameObject
{
public:
	 StaticObject();
	 StaticObject(const sf::Sprite sprite);

	 void setUnDrawable();
	 void setDrawable();
	 void setTime();
	 bool getUnDrawableStatus() const;
	 sf::Time getTime() const;
private:
	bool m_isUndrawable = false;
	sf::Clock m_clock;
};