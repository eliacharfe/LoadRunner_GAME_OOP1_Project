#include "Board.h"

Board::Board() : m_level(1), m_time(0.0f), m_rand(0), m_startLevelOnTextBoard('\n')
{ }
//---------------------------------------------------------
void Board::openFile()
{
	m_BoardFile.open("Board.txt"); //file to read from
	if (!m_BoardFile.is_open()) {
		cerr << "Cannot open file..." << endl;
		exit(EXIT_FAILURE); // if the file cannot be open
	}
	readLevel();
}
//------------------------------
void Board::readLevel()
{
	m_startLevelOnTextBoard = m_BoardFile.tellg(); //when crossing enemy - restart the level
	m_BoardFile >> m_sizeBoard.y >> m_sizeBoard.x >> m_time;
	m_BoardFile.get();	m_charBoard.clear();
	for (unsigned int row = 0; row < m_sizeBoard.y; row++)
	{	//build the updated game board from the rellevent screen
		string str;
		getline(m_BoardFile, str);
		m_charBoard.push_back(str); // save the line in a vector of strings
	}
}
//-----------------------------------------------------
void Board::allocateBoard()
{ // allocate according to the board level (according to the text)
	auto player = make_shared < Player >(*this);
	sf::Vector2f location(0.0f, 0.0f);
	for (unsigned int row = 0; row < m_sizeBoard.y; row++, location.y += OBJECT_SIZE)
	{
		for (unsigned int col = 0; col < m_sizeBoard.x; col++, location.x += OBJECT_SIZE)
		{
			m_sprite = Image::instance().getSprite(m_charBoard[row][col]); // get the accurate sprite
			m_sprite.setPosition(location);
			createObject(m_charBoard[row][col], m_sprite, player); // create object
		}
		location.x = 0.0f;
	}
}
//-------------------------------------------------------
void Board::Draw(sf::RenderWindow& window) const
{  // draw the statics  and movings of the level
	for (auto& staticObj : m_statics) {
		if (!staticObj->getUnDrawableStatus()) 
			staticObj->Draw(window); // draw all statics except from a pit digged in the floor
		if (staticObj->getTime().asSeconds() > 4) // for if a pit was digged --> can draw and update status
			staticObj->setDrawable();
	}
	for (auto& movableObj : m_movables)
		movableObj->Draw(window);
}
//-------------------------------------------------
void Board::Update(const sf::Time& currTime, const sf::Time runTime)
{
	for (auto& movableObj : m_movables) {
		movableObj->Move(currTime);// move the movable objects
		handleCollisions(*movableObj); // handle collisions
		handleFalls(*movableObj); // handle fall if is on the air
		handleFallIntoPit(*movableObj); // handle the movable if on an open pit
	}
	std::experimental::erase_if(m_statics, [](auto& staticObj) {
		return staticObj->isDisposed();  });

	checkCoinsStatus(); // check if all coins of the level are eaten --> handle accordingly
	checkPlayerStatus(runTime); // check if player is dead --> handle accordingly
	checkPresentStatus();// check if a present was taken --> handle accordingly
}
//-----------------------------------------------
void Board::handleCollisions(GameObject& movableObject)
{
	for (auto& staticObj : m_statics)
		if (movableObject.collidesWith(*staticObj)) // if the movable collides a static 
			movableObject.handleCollision(*staticObj); //-- > handle accordingly
	for (auto& movableObj : m_movables)
		if (movableObject.collidesWith(*movableObj))// if the movable collides another movable
			movableObject.handleCollision(*movableObj);//--> handle accordingly
}
//------------------------------------
void Board::handleFalls(GameObject& movableObject)
{
	sf::Vector2f LastLocation(movableObject.getLocation()); // save to when collides with a static object
	sf::Vector2f NewLocation(movableObject.getLocation().x, movableObject.getLocation().y + 1);// set row++
	movableObject.setLocation(NewLocation); // set location (1 down)
	for (auto& staticObj : m_statics)
		if (movableObject.collidesWith(*staticObj))
			movableObject.setLocation(LastLocation); // if collides --> set the location to the last place saved
}
//------------------------------------------------
void Board::handleFallIntoPit(GameObject& movableObject)
{ // check whether the movable object is on an open pit --> update accordigly
	for (int i = 0; i < m_statics.size(); i++)
	{ // passing on all static objects
		if (m_statics[i]->getUnDrawableStatus()) // if the static object is an open pit (floor open state)
		{
			if (m_statics[i]->getTime().asSeconds() > 3.5 && movableObject.getIsInPitStatus())
			{// if the time is past and this movable is inside --> exit from pit
				movableObject.setLocation(movableObject.getLastLocation());
				movableObject.setNotInPit(); // the movable is no more in pit
				m_statics[i]->setDrawable(); // now can draw this floor
				m_pitFull = false; 
				continue; // exit from pit --> continue to next static object
			}
			if (movableObject.getLocation().x < m_statics[i]->getLocation().x)
			{//if pit is on the right of the movable
				if (fallIntoRightPit(movableObject, i)) {
					m_pitFull = true; // the pit is full so no one else can fall into this pit
					if (!movableObject.getIsInPitStatus()) // if he is not in the pit already
						movableObject.setLastLocation(movableObject.getLocation()); //save location before the fall
					movableObject.setLocation(m_statics[i]->getLocation()); //fall
					movableObject.setInPit(); // set the movable status --> in the pit
				}
			}
			else if (movableObject.getLocation().x >= m_statics[i]->getLocation().x)
			{//if pit is on the left of the movable
				if (fallIntoLeftPit(movableObject, i)) {
					m_pitFull = true;// the pit is full so no one else can fall into this pit
					if (!movableObject.getIsInPitStatus())// if he is not in the pit already
						movableObject.setLastLocation(movableObject.getLocation()); //save location before the fall
					movableObject.setLocation(m_statics[i]->getLocation()); //fall
					movableObject.setInPit();// set the movable status --> in the pit
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------
bool Board::fallIntoRightPit(GameObject& movableObject, int i) const
{
	return (movableObject.getLocation().x >= m_statics[i]->getLocation().x - OBJECT_SIZE / 2
		    && m_statics[i]->getLocation().x <= movableObject.getLocation().x + OBJECT_SIZE
		    && movableObject.getLocation().y <= m_statics[i]->getLocation().y
		    && m_statics[i]->getLocation().y <= movableObject.getLocation().y + OBJECT_SIZE + 1
		    && !m_pitFull); // if found he is on the middle of the open pit
}
//------------------------------------------------------------------------
bool Board::fallIntoLeftPit(GameObject& movableObject, int i) const
{
	return (movableObject.getLocation().x <= m_statics[i]->getLocation().x - OBJECT_SIZE / 2
		    && m_statics[i]->getLocation().x >= movableObject.getLocation().x + OBJECT_SIZE
		    && movableObject.getLocation().y <= m_statics[i]->getLocation().y
		    && m_statics[i]->getLocation().y <= movableObject.getLocation().y + OBJECT_SIZE + 1
		    && !m_pitFull);// if found he is on the middle of the open pit
}
//-------------------------------------
void Board::checkCoinsStatus()
{
	if (!Coin::getCoin())  // win level 
		winLevel();// next level  
}
//--------------------------------
void Board::checkPlayerStatus(const sf::Time runTime)
{ // check if player is dead, and if dead check if dead complitely (no life)
	if (Player::isDead() || (runTime.asSeconds() >= getTime() && getTime() != -1)) {//loose level
		if (runTime.asSeconds() > getTime() && getTime() != -1)
			Player::setDeadStatusTrue();
		Player::setLife(-1);
		if (!Player::getLife())  // Game Over
			m_endGame = true; // to signal the GameManager (Controller)
		looseLevel(); // will restart the level
		Player::setDeadStatusFalse();
	}
}
//------------------------------------
void Board::checkPresentStatus()
{ // check if a present was taken and update accoridingly
	if (PresentGood::getPresentTakenStatus()/*true --> player collides with a present*/) {
		m_rand = rand() % 4;
		switch (m_rand) {
		case 0:  if (m_time != -1)  m_time += 30; else Player::setScore(10 * m_level); break;
		case 1: Player::setScore(10 * m_level); break;// += (10 * num of level)
		case 2: Player::setLife(1); break; // += 1
		case 3: if (m_time != -1) m_time += 30; else Player::setLife(1);; break;
		}
		PresentGood::setPresentTakenStatus(); // set false
	}
	if (PresentBad::getBadPresentStatus() /* true --> player collides with a bad present */ ) { 
		auto player = make_shared < Player >();
		m_sprite = Image::instance().getSprite(ENEMY);
		m_sprite.setPosition(sf::Vector2f(OBJECT_SIZE * (m_sizeBoard.x / 2), OBJECT_SIZE));
		createObject(ENEMY, m_sprite, player); // creating the new enemy
		PresentBad::setBadPresentStatus();//set false
	}
}
//-------------------------------------------
void Board::floorDigged(const sf::Vector2f direction)
{ // handle pit according to the user pressed (X or Y)
	Sounds::instance().makeSound(DIG);
	auto player = dynamic_cast <Player*>(m_movables[PLAYER_INDEX].get());
	auto location = player->getLocation(); // get the player location
	location.y += 1.0f; //under player locatin
	auto locationRight = location;  locationRight.x += 1.0f;// the place under player and right of him
	auto locationLeft = location;	locationLeft.x -= OBJECT_SIZE;// the place under player and left of him
	int arr[2], index = -1; arr[0] = -1; arr[1] = -1;

	for (int i = 0; i < m_statics.size(); i++)
	{
		if (locationRight.x <= m_statics[i]->getLocation().x // if static object is on the right down of player location
			&& m_statics[i]->getLocation().x <= (locationRight.x + OBJECT_SIZE)// between the accurate bounds
			&& locationRight.y <= m_statics[i]->getLocation().y
			&& m_statics[i]->getLocation().y <= (locationRight.y + OBJECT_SIZE))
			arr[0] = i;
		else if (locationLeft.x <= m_statics[i]->getLocation().x// if static object is on the left down of player location
			&& m_statics[i]->getLocation().x <= (locationLeft.x + OBJECT_SIZE)// between the accurate bounds
			&& locationLeft.y <= m_statics[i]->getLocation().y
			&& m_statics[i]->getLocation().y <= (locationLeft.y + OBJECT_SIZE))
			arr[1] = i;
	}
	if (direction == sf::Vector2f(1, 0))
		index = arr[0];
	else if (direction == sf::Vector2f(-1, 0))
		index = arr[1];
	if (index == -1 || !m_statics[index] || typeid(*m_statics[index]) != typeid(Floor))
		return; // not correct digging

	m_statics[index]->setUnDrawable(); // now cannot draw this static (if got here we know it's a floor and in the accurate place)
	m_statics[index]->setTime(); // restart the clock of this static
}
//--------------------------------
void Board::setLevel(int level)
{
	m_level += level;
}
//--------------------------
void Board::setLevelStatus()
{
	m_newLevel = false;
}
//--------------------------------------------
void Board::setRestartLevel()
{
	m_restartLevel = false;
}
//---------------------------------
void Board::setTime(const sf::Time runTime)
{
	m_time -= runTime.asSeconds() / 100;
}
//------------------------------
sf::Vector2f Board::getSize() const
{
	return m_sizeBoard;
}
//---------------------------------------------------
char Board::getChar(const sf::Vector2f location) const
{ // for EnemyBoring to know where the floor ends to not falling and change direction to other side
	auto loc = location;
	loc.x /= OBJECT_SIZE;
	loc.y /= OBJECT_SIZE;
	loc.y += 1;
	return m_charBoard[(int)loc.y][(int)loc.x];
}
//-------------------------------
bool Board::getLevelStatus() const
{
	return m_newLevel;
}
//---------------------------------
bool Board::getRestartLevel() const
{
	return m_restartLevel;
}
//-------------------------------------
int Board::getLevel() const
{
	return m_level;
}
//-----------------------------
int Board::getLife() const
{
	return Player::getLife();
}
//---------------------------------
int Board::getScore() const
{
	return Player::getScore();
}
//--------------------------
float Board::getTime() const
{
	return m_time;
}
//-----------------------------------
int Board::getCoins() const
{
	return Coin::getCoin();
}
//-----------------------------
bool Board::getEndGame() const
{
	return m_endGame;
}
//-----------------------------
bool Board::getWinGame() const
{
	return m_winGame;
}
//--------------------------------------------------------------------------
void Board::createObject(const char c, const sf::Sprite sprite, shared_ptr<Player> player)
{
	unique_ptr < StaticObject > staticObj = createUnmovableObject(c, sprite);
	if (staticObj) { m_statics.push_back(move(staticObj));  	 return; }
	shared_ptr < MovingObject > movableObj = createMovableObject(c, sprite, player);
	if (movableObj) { m_movables.push_back(move(movableObj));	 return; }
}
//----------------------------------------------------
shared_ptr < MovingObject > Board::createMovableObject(const char c, const sf::Sprite sprite, 
	                                                   shared_ptr < Player > player)
{
	switch (c)
	{
	case PLAYER:  	player->setSpritePlayer(sprite);
		            return player;   break;
	case ENEMY: {   m_rand = rand() % 3; 
		            switch (m_rand)
		            {
	            	case 0: return  make_shared < EnemyRandom >(sprite, player.get(), *this); break;
		            case 1: return  make_shared < EnemySmart > (sprite, player.get(), *this); break;
		            case 2: return  make_shared < EnemyBoring >(sprite, player.get(), *this); break;
		            }
		            break; }
	}
	return nullptr;
}
//-------------------------------------------------
unique_ptr < StaticObject > Board::createUnmovableObject(const char c, const sf::Sprite sprite)
{
	switch (c)
	{
	case WALL:		 return make_unique < Wall >(sprite);	     break;
	case FLOOR:      return make_unique < Floor >(sprite);       break;
	case LADDER:	 return make_unique < Ladder >(sprite);      break;
	case POLE:		 return make_unique < Pole >(sprite);        break;
	case PRESENT:    return make_unique < PresentGood >(sprite); break;
	case BAD_PRESENT:return make_unique < PresentBad >(sprite);  break;
	case COIN:       return make_unique < Coin >(sprite);        break;
	}
	return nullptr;
}
//---------------------------------------------
void Board::winLevel()
{ // win the level --> next level
	Player::setScore(50 * m_level);
	m_level++;
	Player::setLevelNum(m_level);
	m_charBoard.clear(); m_movables.clear(); m_statics.clear();
	m_BoardFile.get();
	m_startLevelOnTextBoard = m_BoardFile.tellg();
	m_BoardFile >> m_sizeBoard.y >> m_sizeBoard.x >> m_time;
	if (m_sizeBoard.y == 0 && m_sizeBoard.x == 0 && m_time == 0)
		m_winGame = true;// --> win the whole game --> signal the Game Manager
	else {
		m_BoardFile.get(); 
		for (unsigned int row = 0; row < m_sizeBoard.y; row++)
		{	//build the updated game board from the rellevent screen
			string str;
			getline(m_BoardFile, str);
			m_charBoard.push_back(str);
		}
		allocateBoard();
	}
	m_newLevel = true;
	m_pitFull = false;
}
//----------------------------------
void Board::looseLevel()
{// loose the level --> restart
	m_BoardFile.seekg(m_startLevelOnTextBoard);
	m_startLevelOnTextBoard = m_BoardFile.tellg(); //when crossing enemy - restart the level
	m_charBoard.clear(); m_movables.clear(); m_statics.clear();
	m_BoardFile >> m_sizeBoard.y >> m_sizeBoard.x >> m_time;
	m_BoardFile.get();
	for (unsigned int row = 0; row < m_sizeBoard.y; row++)
	{	//build the updated game board from the rellevent screen
		string str;
		getline(m_BoardFile, str);
		m_charBoard.push_back(str);
	}
	allocateBoard();
	m_restartLevel = true;
	m_pitFull = false;
}



























////------------------------------------
//void Board::PrintBoard()const
//{//Prints the game char board
//	//std::system("cls"); //clean screen
//	//for (unsigned int row = 0; row < m_sizeBoard.y; row++)
//	//	cout << m_charBoard[row] << std::endl;//Print board
//	cout << "LEVEL:     \t" << m_level << std::endl;
//	cout << "LIFE:      \t" << Player::getLife() << endl;
//	cout << "SCORE:     \t" << Player::getScore() << endl;
//	cout << "TIME:      \t" << m_time << endl;
//	cout << "SIZE BOARD:\t" << m_sizeBoard.x << " " << m_sizeBoard.y << std::endl;
//	//cout << "Coins left:\t" << m_coins << endl;
//	//cout << "size charBoard x: " << m_charBoard[0].size() << " size charBoard y: " << m_charBoard.size();
//}




