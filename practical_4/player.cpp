#include "player.h"
#include <iostream>


void Player::update(double dt) {

	float directionX = 0.0f;
	float directionY = 0.0f;

	sf::Vector2f movement = sf::Vector2f(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(controls[0]) && getPosition().x >= 0) {
		directionX--;
		std::cout << "X: " << getPosition().x << " Y: " << getPosition().y << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(controls[1]) && getPosition().x <= 775) {
		directionX++;
		std::cout << "X: " << getPosition().x << " Y: " << getPosition().y << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(controls[2]) && getPosition().y >= 0) {
		directionY--;
		std::cout << "X: " << getPosition().x << " Y: " << getPosition().y << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(controls[3]) && getPosition().y <= 575) {
		directionY++;
		std::cout << "X: " << getPosition().x << " Y: " << getPosition().y << std::endl;
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
