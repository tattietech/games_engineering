#pragma once
#include <SFML/Graphics.hpp>
class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	// Default constructor is hidden
	Ship();
	bool _exploded;
	bool _visible;

public:
	// Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);

	// Pure virtual deconstructor -- makes this an abstract class
	virtual ~Ship() = 0;

	// Update, virtual so can be overrided but not pure virtual
	virtual void Update(const float &dt);

	bool is_exploded() const;
	virtual void Explode();

	bool is_visible() const;
	virtual void Remove();

	float explode_time;
};

// Invader class
class Invader : public Ship {
public:
	static bool direction;
	static float speed;
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float &dt) override;
};

// Player Class
class Player : public Ship {
public:
	Player();
	Player(float playerSpeed);
	void Update(const float &dt) override;
	float playerSpeed;
	const sf::Keyboard::Key controls[3] = {
	sf::Keyboard::A,	// Player moves left
	sf::Keyboard::D,	// Player move right
	sf::Keyboard::W,	//Shoots
	};
};