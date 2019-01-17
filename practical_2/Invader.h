#pragma once
#include <SFML/Graphics.hpp>
# include "Ship.h"

class Invader : public Ship {
public:
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();

	// Overrides the virtual method in the abstract ship class
	void Update(const float &dt) override;
};