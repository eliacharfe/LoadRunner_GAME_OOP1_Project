#pragma once
#include "Utilities.h" 

class Sounds {
public:
	static Sounds& instance();
	void makeSound(const char c);

private:
	Sounds();
	Sounds(const Sounds&) = default;
	Sounds& operator=(const Sounds&) = default;
	void loadSounds();

	vector < sf::SoundBuffer > m_soundBuffer;
	vector < sf::Sound > m_sounds;
};
