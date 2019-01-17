#include "Ship.h"
#include "game.h"

Ship::Ship() {};


Ship::Ship(sf::IntRect ir) : sf::Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}