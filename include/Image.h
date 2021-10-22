#pragma once
#include "Utilities.h"

class Image
{
public:
	void loadImages();
	static Image& instance();
	//const sf::Sprite& getImage(const char c) const;
	const sf::Sprite getSprite(const char c) const;
	const sf::Font getFont() const;

private:
	Image();
	Image(const Image&) = default;
	Image& operator=(const Image&) = default;

	vector<sf::Sprite> m_sprites;
	vector<sf::Texture> m_texture;

	sf::Font m_font;
};
