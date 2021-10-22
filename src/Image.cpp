#include "Image.h"

Image::Image()
{
	loadImages();
}
//---------------------------------
void Image::loadImages()
{
	m_texture.resize(13);
	m_texture[0].loadFromFile("player.png");
	m_texture[1].loadFromFile("enemy.png");
	m_texture[2].loadFromFile("wall.png");
	m_texture[3].loadFromFile("coin.png");
	m_texture[4].loadFromFile("ladder.png");
	m_texture[5].loadFromFile("empty.png");
	m_texture[6].loadFromFile("pole.png");
	m_texture[7].loadFromFile("present.png");
	m_texture[8].loadFromFile("presentBad.png");
	m_texture[9].loadFromFile("floor.png");
	m_texture[10].loadFromFile("play.jpg");// "playGame.png");
	m_texture[11].loadFromFile("quit.jpg");// QuitButton.png");
	m_texture[12].loadFromFile("winGame.png");

	m_sprites.resize(14);
	m_sprites[0].setTexture(m_texture[0]);
	m_sprites[1].setTexture(m_texture[1]);
	m_sprites[2].setTexture(m_texture[2]);
	m_sprites[3].setTexture(m_texture[3]);
	m_sprites[4].setTexture(m_texture[4]);
	m_sprites[5].setTexture(m_texture[5]);
	m_sprites[6].setTexture(m_texture[6]);
	m_sprites[7].setTexture(m_texture[7]);
	m_sprites[8].setTexture(m_texture[8]);
	m_sprites[9].setTexture(m_texture[9]);
	m_sprites[10].setTexture(m_texture[10]);
	m_sprites[11].setTexture(m_texture[11]);
	m_sprites[12].setTexture(m_texture[12]);

	m_font.loadFromFile("resources/sansation.ttf");
}
//------------------------------------
Image& Image::instance()
{
	static Image inst;
	return inst;
}
//-----------------------------------------
const sf::Sprite Image::getSprite(const char c) const
{
	switch (c)
	{
	case PLAYER: 	 return m_sprites[0]; 	break;
	case ENEMY:		 return m_sprites[1];	break;
	case WALL:	     return m_sprites[2];	break;
	case COIN:	 	 return m_sprites[3];	break;
	case LADDER:	 return m_sprites[4];	break;
	case EMPTY_CELL: return m_sprites[5];   break;
	case POLE:	     return m_sprites[6];	break;
	case PRESENT:    return m_sprites[7];	break;
	case BAD_PRESENT:return m_sprites[8];   break;
	case FLOOR:		 return m_sprites[9];   break;
	case PLAY_BUTTON:return m_sprites[10];  break;
	case QUIT_BUTTON:return m_sprites[11];  break;
	case WIN_GAME:   return m_sprites[12];  break;
	}
	return m_sprites[5];
}
//--------------------------------------
const sf::Font Image::getFont() const
{
	return m_font;
}
//--------------------------------------------------------------



























