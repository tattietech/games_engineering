#include "player.h"


void Player::update(double dt) {
	
	float directionX = 0.0f;
	float directionY = 0.0f;

	if (sf::Keyboard::isKeyPressed(controls[0])) {
		directionX--;
	}
	else if (sf::Keyboard::isKeyPressed(controls[1])) {
		directionX++;
	}

	if (sf::Keyboard::isKeyPressed(controls[2])) {
		directionY--;
	}
	else if (sf::Keyboard::isKeyPressed(controls[3])) {
		directionY++;
	}

	sf::Vector2f position(directionX * _speed * dt, directionY *_speed * dt);
	move(position);

	Entity::update(dt);
}

Player::Player()
	: _speed(200.0f), Entity(std::make_unique<sf::CircleShape>(25.f)) {
	_shape->setFillColor(sf::Color::Magenta);
	_shape->setOrigin(sf::Vector2f(25.f, 25.f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}