#pragma once
#include "MovingObject.h"
#include "Player.h"
#include "Utilities.h"
#include "Pole.h"
#include "Ladder.h"
#include "Coin.h"
#include "PresentGood.h"
#include "PresentBad.h"

class Board;

class Enemy : public MovingObject
{
public:
	Enemy(const sf::Sprite sprite , Player* player, const Board& board);

protected:
	Player* m_player;
	const Board& m_board;
private:
	
};