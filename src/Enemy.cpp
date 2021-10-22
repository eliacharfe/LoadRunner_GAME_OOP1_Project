#include "Enemy.h"
#include "Board.h"

Enemy::Enemy(const sf::Sprite sprite , Player* player, const Board& board)
	: MovingObject::MovingObject(sprite), m_player(player), m_board(board)
{
}
//------------------------------------------
