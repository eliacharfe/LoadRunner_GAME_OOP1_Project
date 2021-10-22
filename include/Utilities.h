#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <experimental/vector>
#include <Windows.h>

using std::vector;
using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::make_shared;
using std::move;
using std::ifstream;
using std::ofstream;
using std::streamoff;
using std::to_string;
using std::cout;
using std::endl;
using std::cerr;

const int DEF_SIZE_WINDOW = 1100;
const int OUTLINE_THIKNESS = 3;
const int CHARACTER_SIZE = 55;
const int CHARACTER_SIZE_TEXT = 30;
const float MSG_X_POS = 100.f;
const float MSG_Y_POS = 80.f;

const float OBJECT_SIZE = 40.0f;
const int NUM_BUTTOMS = 10; 
const float SPEED_PLAYER = 230.0f; 
const float SPEED_ENEMY = 150.0f; 
const float SPEED_SMART_ENEMY = 190.0f; 
const int MAX_RAND = 1000;

const char MENU = 'M';
const char PLAYER = '@';
const char ENEMY = '%';
const char WALL = '#';
const char FLOOR = 'F';
const char LADDER = 'H';
const char POLE = '-';
const char COIN = '*';
const char PRESENT = '+';
const char BAD_PRESENT = 'X';
const char EMPTY_CELL = ' ';
const char WIN = 'W';
const char LOOSE = 'L';
const char WIN_GAME = 'V';
const char PLAY_BUTTON = 'P';
const char QUIT_BUTTON = 'Q';
const char DIG = 'D';


const int LIFE = 3;
const int PLAYER_INDEX = 0;

const int MAX_MESSAGE_SIZE = 200;
/*
enum objects_t {
	PLAYER = '@',
	ENEMY = '%',
	WALL = '#',
	POLE = '-',
	LADDER = 'H',
	PLAYER_ON_LADDER = 'S',
	COIN = '*',
	EMPTY_CELL = ' '
};
*/