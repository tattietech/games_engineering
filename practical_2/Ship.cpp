#include "Ship.h"
#include "bullet.h"
#include "game.h"
#include <iostream>

bool Invader::direction = true;
float Invader::speed = 50.0f;

Ship::Ship() {};


Ship::Ship(sf::IntRect ir) : sf::Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

bool Ship::is_exploded() const
{
	return _exploded;
}

void Ship::Explode()
{
	setTextureRect(sf::IntRect(128, 32, 32, 32));
	_exploded = true;
}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;


//////////// Invader Class ///////////////////////
Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	// Applies any generic updates from ship
	Ship::Update(dt);

	// If direction is true then move forwards, if not, backwards
	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	// Change direction when the group of invaders reaches either wall
	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
			direction = !direction;
			for (int i = 0; i < ships.size(); i++) {
				ships[i]->move(0, 24);
				}
			//speed += 10;
	}
}

/////////////////// Player Class ////////////////////////
Player::Player(float playerSpeed) : Ship(sf::IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.f });
	this->playerSpeed = playerSpeed;
}

void Player::Update(const float &dt) {
	// Apllies ship updates
	Ship::Update(dt);

	// Fire mechanism
	static float firetime = 0.0f;
	firetime -= dt;

	// Moves player
	float direction = 0.0f;
	if (sf::Keyboard::isKeyPressed(controls[0])) {
		direction--;
	}
	else if (sf::Keyboard::isKeyPressed(controls[1])) {
		direction++;
	}
	
	if (firetime <= 0 && sf::Keyboard::isKeyPressed(controls[2])) {
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}

	// Prevents player from going out of bounds
	if (getPosition().x < 0) {
		direction++;
	}
	else if (getPosition().x > gameWidth - 32) {
		direction--;
	} else if (getPosition().y > gameHeight - 32) {
		setPosition({ getPosition().x, gameHeight - 32.f });
	}


	move(direction * playerSpeed * dt, 0);
};