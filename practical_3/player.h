// player.h
#pragma once
#include "entity.h"

class Player : public Entity {
	private:
	float _speed;

	public:
	void update(double dt) override;
	Player();
	void render(sf::RenderWindow &window) const override;
	const sf::Keyboard::Key controls[4] = {
		sf::Keyboard::A,	// Player moves left
		sf::Keyboard::D,	// Player move right
		sf::Keyboard::W,	// Player moves up
		sf::Keyboard::S,	// Player moves down
	};

	bool Player::validmove(sf::Vector2f pos);
};
