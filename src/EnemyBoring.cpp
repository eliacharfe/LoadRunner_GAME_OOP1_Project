#include "EnemyBoring.h"
#include "Board.h"

//-------------------------------------------
EnemyBoring::EnemyBoring(const sf::Sprite sprite, Player* player, const Board& board)
	: Enemy::Enemy(sprite, player, board)
{
}
//--------------------------------------------
void EnemyBoring::Move(const sf::Time& currTime)
{
	if (m_direction == sf::Vector2f(-1, 0))
		m_direction == sf::Vector2f(-1, 0);
	else m_direction = sf::Vector2f(1, 0);

	const auto speedPerSec = currTime.asSeconds() * SPEED_ENEMY;
	sf::Vector2f location(getLocation().x + (m_direction.x * speedPerSec),
	                	  getLocation().y + (m_direction.y * speedPerSec));

	m_lastLocation = getLocation();
	if (location.x >= 0 && location.y >= 0  && location.x <= m_board.getSize().x * OBJECT_SIZE - OBJECT_SIZE
		                                    && location.y <= m_board.getSize().y * OBJECT_SIZE - OBJECT_SIZE)
		setLocation(location); // if not out of the level board

	if (location.x <= 0 || location.x >= m_board.getSize().x * OBJECT_SIZE - OBJECT_SIZE)
	{ // reaches end of board level (the limits if there are no walls)
		if (m_direction == sf::Vector2f(-1, 0))
			m_direction = sf::Vector2f(1, 0);
		else if (m_direction == sf::Vector2f(1, 0))
			m_direction = sf::Vector2f(-1, 0);
	}

	char c = m_board.getChar(location);
	if (c == EMPTY_CELL)// if reaches the edge of a floor --> change direction to not fall
	{
		if (m_direction == sf::Vector2f(-1, 0))
			m_direction = sf::Vector2f(1, 0);
		else if (m_direction == sf::Vector2f(1, 0))
			m_direction = sf::Vector2f(-1, 0);
	}

}
//--------------------------------------------------------
void EnemyBoring::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	gameObject.handleCollision(*this);
}
//------------------------------------------
void EnemyBoring::handleCollision(Wall& gameObject)
{
	if (m_direction == sf::Vector2f(-1, 0))
		m_direction = sf::Vector2f(1, 0);
	else if (m_direction == sf::Vector2f(1, 0))
	           m_direction = sf::Vector2f(-1, 0);
	setLocation(m_lastLocation);
}
//----------------------------------------------
void EnemyBoring::handleCollision(Player& gameObject)
{
	Sounds::instance().makeSound(ENEMY);
	gameObject.handleCollision(*this);
}
//----------------------------------------------
void EnemyBoring::handleCollision(Floor& gameObject)
{
	if (m_direction == sf::Vector2f(-1, 0))
		m_direction = sf::Vector2f(1, 0);
	else if (m_direction == sf::Vector2f(1, 0))
		m_direction = sf::Vector2f(-1, 0);
	setLocation(m_lastLocation);
}
//----------------------------------------
