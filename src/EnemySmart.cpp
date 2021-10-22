#include "EnemySmart.h"
#include "Board.h"

//-------------------------------------------
EnemySmart::EnemySmart(const sf::Sprite sprite , Player* player, const Board& board)
	: Enemy::Enemy(sprite , player, board)
{ }
//--------------------------------------------
void EnemySmart::Move(const sf::Time& currTime)
{
	m_direction = getDirectionEnemy();

	const auto speedPerSec = currTime.asSeconds() * SPEED_SMART_ENEMY;
	sf::Vector2f location(getLocation().x + (m_direction.x * speedPerSec),
		                  getLocation().y + (m_direction.y * speedPerSec));

	m_lastLocation = getLocation();
	if (location.x >= 0 && location.y >= 0 && location.x <= m_board.getSize().x * OBJECT_SIZE - OBJECT_SIZE
		                                   && location.y <= m_board.getSize().y * OBJECT_SIZE - OBJECT_SIZE)
	setLocation(location);// if not out of the level board
}
//---------------------------------------
sf::Vector2f EnemySmart::getDirectionEnemy() const
{
	const auto RowPlayer = m_player->getPlayerLocation().y;
	const auto ColPlayer = m_player->getPlayerLocation().x;
	const auto RowEnemy = getLocation().y;
	const auto ColEnemy = getLocation().x;

	int random_direction = rand() % 10;
	if (ColPlayer <= ColEnemy && RowPlayer <= RowEnemy) {
		if (random_direction % 2 == 0)
			return sf::Vector2f(0, -1);// up
		else return sf::Vector2f(-1, 0); //left
	}
	else if (ColPlayer <= ColEnemy && RowPlayer >= RowEnemy) {
		if (random_direction % 2 == 0)
			return sf::Vector2f(0, 1);// down
		else return sf::Vector2f(-1, 0);//left
	}
	else if (ColPlayer >= ColEnemy && RowPlayer <= RowEnemy) {
		if (random_direction % 2 == 0)
			return sf::Vector2f(0, -1); // up
		else return sf::Vector2f(1, 0);// right
	}
	else if (ColPlayer >= ColEnemy && RowPlayer >= RowEnemy){
		if (random_direction % 2 == 0)
			return sf::Vector2f(0, 1); // down
		else return sf::Vector2f(1, 0);//right
	}
	return sf::Vector2f(0, 0);// does not get here
}
//--------------------------------------------------------
void EnemySmart::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	gameObject.handleCollision(*this);
}
//------------------------------------------
void EnemySmart::handleCollision(Wall& gameObject)
{
	setLocation(m_lastLocation);
}
//----------------------------------------------
void EnemySmart::handleCollision(Player& gameObject)
{
	Sounds::instance().makeSound(ENEMY);
	gameObject.handleCollision(*this);
}
//-------------------------------------------------
void EnemySmart::handleCollision(Floor& gameObject)
{
	setLocation(m_lastLocation);
}
//----------------------------------------

