#include "Sounds.h"

Sounds::Sounds()
{
	loadSounds();
}
//----------------------------
void Sounds::loadSounds() 
{
	m_soundBuffer.resize(8);
	m_soundBuffer[0].loadFromFile("enemySoundCollision.ogg");
	m_soundBuffer[1].loadFromFile("eatSound.ogg");
	m_soundBuffer[2].loadFromFile("soundPresent.ogg");
	m_soundBuffer[3].loadFromFile("badPresentSound.ogg");
	m_soundBuffer[4].loadFromFile("winLevel.wav");
	m_soundBuffer[5].loadFromFile("GameOverSound.ogg");
	m_soundBuffer[6].loadFromFile("soundWinGame.ogg");
	m_soundBuffer[7].loadFromFile("soundDig.ogg");

	m_sounds.resize(8);
	m_sounds[0].setBuffer(m_soundBuffer[0]);
	m_sounds[1].setBuffer(m_soundBuffer[1]);
	m_sounds[2].setBuffer(m_soundBuffer[2]);
	m_sounds[3].setBuffer(m_soundBuffer[3]);
	m_sounds[4].setBuffer(m_soundBuffer[4]);
	m_sounds[4].setVolume(50);
	m_sounds[5].setBuffer(m_soundBuffer[5]);
	m_sounds[6].setBuffer(m_soundBuffer[6]);
	m_sounds[7].setBuffer(m_soundBuffer[7]);
}
//-----------------------------
Sounds& Sounds::instance() 
{
	static Sounds inst;
	return inst;
}
//----------------------------------
void Sounds::makeSound(const char c)
{
	switch (c)
	{
	case ENEMY:       m_sounds[0].play(); break;
	case COIN:        m_sounds[1].play(); break;
	case PRESENT:     m_sounds[2].play(); break;
	case BAD_PRESENT: m_sounds[3].play(); break;
	case WIN:         m_sounds[4].play(); break;
	case LOOSE:       m_sounds[5].play(); break;
	case WIN_GAME:    m_sounds[6].play(); break;
	case DIG:         m_sounds[7].play(); break;
	}
}
//-------------------------------------
