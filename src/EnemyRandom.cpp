#include "EnemyRandom.h"
#include "Board.h"

//-------------------------------------------
EnemyRandom::EnemyRandom(const sf::Sprite sprite , Player* player, const Board& board)
	: Enemy::Enemy(sprite , player, board), m_rand(1), m_clock(sf::Clock())
{ }
//--------------------------------------------
void EnemyRandom::Move(const sf::Time& currTime)
{
	if (m_clock.getElapsedTime().asSeconds() >= 2)
	{
		m_rand = rand() % 2; // 0 or 1
		m_clock.restart();
	}
	else m_rand = 2;

	switch (m_rand)
	{
	case 0: m_direction = sf::Vector2f(-1, 0); break;
	case 1: m_direction = sf::Vector2f(1, 0);  break;
	case 2:   break;
	}

	const auto speedPerSec = currTime.asSeconds() * SPEED_ENEMY;
	sf::Vector2f location(getLocation().x + (m_direction.x * speedPerSec),
		                  getLocation().y + (m_direction.y * speedPerSec));

	m_lastLocation = getLocation(); // save in case need to use
	if (location.x >= 0 && location.y >= 0 && location.x <= m_board.getSize().x * OBJECT_SIZE - OBJECT_SIZE
		                                   && location.y <= m_board.getSize().y * OBJECT_SIZE - OBJECT_SIZE)
	    setLocation(location);// if not out of the level board
	if (location.x <= 0 || location.x >= m_board.getSize().x * OBJECT_SIZE)
	{
		if (m_direction == sf::Vector2f(-1, 0))
			m_direction = sf::Vector2f(1, 0);
		else if (m_direction == sf::Vector2f(1, 0))
			m_direction = sf::Vector2f(-1, 0);
	}
}
//--------------------------------------------------------
void EnemyRandom::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	gameObject.handleCollision(*this);
}
//------------------------------------------
void EnemyRandom::handleCollision(Wall& gameObject)
{
	if (m_direction == sf::Vector2f(-1, 0))
		m_direction = sf::Vector2f(1, 0);
	else if (m_direction == sf::Vector2f(1, 0))
		m_direction = sf::Vector2f(-1, 0);
	setLocation(m_lastLocation);
}
//----------------------------------------------
void EnemyRandom::handleCollision(Player& gameObject)
{
	Sounds::instance().makeSound(ENEMY);
	gameObject.handleCollision(*this);
}
//--------------------------------------------------------
void EnemyRandom::handleCollision(Floor& gameObject)
{
	if (m_direction == sf::Vector2f(-1, 0))
		m_direction = sf::Vector2f(1, 0);
	else if (m_direction == sf::Vector2f(1, 0))
		m_direction = sf::Vector2f(-1, 0);
	setLocation(m_lastLocation);
}
//----------------------------------------


