#include "player.h"


void Player::update(double dt) {

	float directionX = 0.0f;
	float directionY = 0.0f;

	sf::Vector2f movement = sf::Vector2f(0.0f, 0.0f);

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

	movement.x = directionX * _speed * dt;
	movement.y = directionY * _speed * dt;
	move(movement);

	Entity::update(dt);
}

Player::Player()
	: _speed(300.0f), Entity(std::make_unique<sf::CircleShape>(12.5f)) {
	_shape->setFillColor(sf::Color::Yellow);
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}
