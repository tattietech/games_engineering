#include "Ship.h"
#include "game.h"

bool Invader::direction;
float Invader::speed;

Ship::Ship() {};


Ship::Ship(sf::IntRect ir) : sf::Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

// Invader Class
Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	// Applies any generic updates from ship
	Ship::Update(dt);

	// If direction is truee then move forwards, if not, backwards
	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	// Change direction when the group of invaders reaches either wall
	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
			direction = !direction;
			for (int i = 0; i < ships.size(); i++) {
				ships[i]->move(0, 24);
				}
	}
}