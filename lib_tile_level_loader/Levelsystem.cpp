//levelsystem.cpp
#include "LevelSystem.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

std::unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;
Vector2f LevelSystem::_offset(0.0f, 0.0f);
Vector2f LevelSystem::_startPosition;

float LevelSystem::_tileSize(100.f);
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;

std::map<LevelSystem::TILE, sf::Color> LevelSystem::_colours{ {WALL, Color::White}, {END, Color::Red} };

// Reads the map and assigns it a colour
sf::Color LevelSystem::getColor(LevelSystem::TILE t) {
	auto it = _colours.find(t);
	if (it == _colours.end()) {
		_colours[t] = Color::Transparent;
	}
	return _colours[t];
}

// Takes in a tile and a colour and sets the colour as the value of the tile key
void LevelSystem::setColor(LevelSystem::TILE t, Color c) {
	_colours[t] = c;
}

// Load in file to buffer
void LevelSystem::loadLevelFile(const string& path, float tileSize) {
	_tileSize = tileSize;
	size_t w = 0, h = 0;
	string buffer;

	// Load in file to buffer
	ifstream f(path);
	std::cout << f.good();
	if (f.good()) {
		f.seekg(0, ios::end);
		buffer.resize(f.tellg());
		f.seekg(0);
		f.read(&buffer[0], buffer.size());
		f.close();
	}
	else {
		std::cout << string("Couldn't open level file: ") + path <<std::endl;
	}

	// Reads through the file contents and creates tiles based on the letters
	vector<TILE> temp_tiles;
	for (int i = 0; i < buffer.size(); ++i) {
		const char c = buffer[i];
		switch (c) {
		case 'w':
			temp_tiles.push_back(WALL);
			break;
		case 's':
			temp_tiles.push_back(START);
			break;
		case 'e':
			temp_tiles.push_back(END);
			break;
		case ' ':
			temp_tiles.push_back(EMPTY);
			break;
		case '+':
			temp_tiles.push_back(WAYPOINT);
			break;
		case 'n':
			temp_tiles.push_back(ENEMY);
			break;
		case '\n':      // end of line
			if (w == 0) { // if we haven't written width yet
				w = i;      // set width
			}
			h++;
			break;
		default:
			cout << c << endl; // Don't know what the tile type is
		}
	}

	if (temp_tiles.size() != (w * h)) {
		throw string("Can't parse level file") + path;
	}

	// Creates array of final tiles with the dimensions of the map
	_tiles = make_unique <TILE[]>(w * h);
	_width = w;
	_height = h;
	copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
	cout << "Level " << path << " Loaded. " << w << " x " << h << endl;
	buildSprites();
}

// Nested for loop to loop through tiles x and y and render a rectangle
// of correct colour based on tile type
void LevelSystem::buildSprites() {
	_sprites.clear();
	for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
		for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
			auto s = make_unique<sf::RectangleShape>();
			s->setPosition(getTilePosition({ x, y }));
			s->setSize(Vector2f(_tileSize, _tileSize));
			s->setFillColor(getColor(getTile({ x, y })));
			_sprites.push_back(move(s));
			if (getTile({x, y}) == ls::START) {
				_startPosition.x = x*120;
				_startPosition.y = y*100;
			}
		}
	}
}

// Returns tile position
sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p) {
	return (Vector2f(p.x, p.y) * _tileSize);
}

// Returns and actual tile
LevelSystem::TILE LevelSystem::getTile(sf::Vector2ul p) {
	if (p.x > _width || p.y > _height) {
		throw string("Tile out of range: ") + to_string(p.x) + "," + to_string(p.y) + ")";
	}

	// This line coverts the 2d array position into a 1d index
	return _tiles[(p.y * _width) + p.x];
}

// Returns a tile at a specific screen coordinate
LevelSystem::TILE LevelSystem::getTileAt(Vector2f v) {
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		throw string("Tile out of range ");
	}
	return getTile(Vector2ul((v - _offset) / (_tileSize)));
}

size_t LevelSystem::getHeight()
{
	return _height;
}

size_t LevelSystem::getWidth()
{
	return _width;
}

sf::Vector2f LevelSystem::getStartPosition()
{
	return _startPosition;
}


// Renders map on screen
void LevelSystem::render(RenderWindow &window) {
	for (size_t i = 0; i < _width * _height; ++i) {
		window.draw(*_sprites[i]);
	}
}