#include "ghost.h"

void Ghost::update(double dt)
{
	sf::Vector2f movement = sf::Vector2f(0.0f, 0.0f);
	int random = rand() % 100;

	if (random == 0 && _movementCool <= 0) {
		directionX++;
		_movementCool += 2.f;
	}
	else if (random == 1 && _movementCool <= 0) {
		directionX--;
		_movementCool += 2.f;
	}
	else if (random == 2 && _movementCool <= 0) {
		directionY++;
		_movementCool += 2.f;
	}
	else if (random == 3 && _movementCool <= 0) {
		directionY--;
		_movementCool += 2.f;
	}

	_movementCool -= dt;

	movement.x = directionX * _speed * dt;
	movement.y = directionY * _speed * dt;
	move(movement);

	Entity::update(dt);
}

Ghost::Ghost()
	:_speed(299.f), Entity(std::make_unique<sf::CircleShape>(12.5f)) {
	_shape->setFillColor(_colour);
}


void Ghost::render(sf::RenderWindow & window) const {
	// Draws our ghost on the screen
	window.draw(*_shape);
}

void Ghost::setSpeed(float increase) {
	// used to increase speed / difficulty
}

void Ghost::setColour(sf::Color colour) {
	_shape->setFillColor(colour);
}