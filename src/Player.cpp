#include "Player.h"
#include "Board.h"

bool Player::m_isDead = false;
int Player::m_life = LIFE;
int Player::m_score = 0;
int Player::m_numLevel = 1;

Player::Player()
	: m_board(Board())
{ }
//------------------------------------
Player::Player(const Board& board)
	: m_board(board)
{ }
//---------------------------------------
Player::Player(const sf::Sprite sprite, const Board& board)
	: MovingObject::MovingObject(sprite), m_board(board)
{ }
//------------------------------------------------------
void Player::Move(const sf::Time& currTime)
{
	setDirectiomPlayer();
	const auto speedPerSec = currTime.asSeconds() * SPEED_PLAYER ;
	sf::Vector2f location (getLocation().x + (m_direction.x * speedPerSec ),
		                   getLocation().y + (m_direction.y * speedPerSec));

	m_lastLocation = getLocation(); // in case collides wall/floor //  m_lastLocation is a protected memeber in MovingObject
	
	if (location.x >= 0 && location.y >= 0 && location.x <= m_board.getSize().x * OBJECT_SIZE - OBJECT_SIZE
		                                   && location.y <= m_board.getSize().y * OBJECT_SIZE - OBJECT_SIZE )
	    setLocation(location);

}
//---------------------------------------------
void Player::setDirectiomPlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_direction = sf::Vector2f(0, -1); // m_direction is a protected memeber in MovingObject
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_direction = sf::Vector2f(0, 1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_direction = sf::Vector2f(-1, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_direction = sf::Vector2f(1, 0);
	else m_direction =  sf::Vector2f(0, 0);
}
//--------------------------------------------------
void Player::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this)
		return;
	gameObject.handleCollision(*this);
}
//----------------------------------------------------------
void Player::handleCollision(Wall& gameObject)
{
	setLocation(m_lastLocation); // a protected func in GameObject 
}
//------------------------------------------------
void Player::handleCollision(EnemyBoring& gameObject)
{
	Sounds::instance().makeSound(ENEMY);
	m_isDead = true;
}
//--------------------------------------------------
void Player::handleCollision(EnemyRandom& gameObject)
{
	Sounds::instance().makeSound(ENEMY);
	m_isDead = true;
}
//----------------------------------------
void Player::handleCollision(EnemySmart& gameObject)
{
	Sounds::instance().makeSound(ENEMY);
	m_isDead = true;
}
//---------------------------------------
void Player::handleCollision(Floor& gameObject)
{
	setLocation(m_lastLocation);
}
//--------------------------------------
void Player::handleCollision(Coin& gameObject)
{
	m_score += 2 * m_numLevel;
}
//-------------------------------------
void Player::handleCollision(Ladder& gameObject)
{ 
	if (m_direction == sf::Vector2f(0, -1) || m_direction == sf::Vector2f(0, 1))
	{
		auto location = gameObject.getLocation();
		location.y = getLocation().y;
		setLocation(location);
	}
}
//-------------------------------------
void Player::handleCollision(Pole& gameObject)
{
	if (m_direction == sf::Vector2f(-1, 0) || m_direction == sf::Vector2f(1, 0))
	{
		auto location = gameObject.getLocation();
		location.x = getLocation().x;
		setLocation(location);
	}
}
//---------------------------------
void Player::setSpritePlayer(sf::Sprite sprite)
{
	setSprite(sprite);
}
//-----------------------------------------------
void Player::setScore(int score) // static function
{
	m_score += score;
}
//----------------------------
void Player::setLife(int life) // static function
{
	m_life += life;
}
//------------------------------
void Player::setDeadStatusFalse() // static function
{
	m_isDead = false;
}
//-----------------------------
void Player::setDeadStatusTrue() // static function
{
	m_isDead = true;
}
//---------------------------------
void Player::setLevelNum(int numLevel) // static function
{
	m_numLevel = numLevel;
}
//-------------------------------
int Player::getLife()  // static function
{
	return m_life;
}
//-----------------------------
int Player::getScore() // static function
{
	return m_score;
}
//-------------------------------
bool Player::isDead() // static function
{
	return m_isDead;
}
//-------------------------------------------
sf::Vector2f Player::getPlayerLocation() const
{
	return this->getLocation();
}


