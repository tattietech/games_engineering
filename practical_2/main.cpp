#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "ship.h"
#include "bullet.h"

// Vector containing all of the ships
std::vector<Ship *> ships;
sf::Texture spritesheet;
Player player = Player(200.f);


void Load(sf::RenderWindow &window) {
	// Loads items to the screen at game beginning

	// Loads sprite sheet file
	if (spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		std::cerr << "Failed to load spritesheet!" << std::endl;
	}

	// Creates invader objects and adds them to ships
	for (int r = 0; r < invader_rows; ++r) {
		auto rect = sf::IntRect(32*r, 0, 32, 32);
		for (int c = 0; c < invader_columns; ++c) {
			sf::Vector2f position = { 50 * (float)(c+0.4), 40*(float)(r+0.4)};
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}

	// Adds player object to ships
	ships.push_back(&player);

	
}

void Update(sf::RenderWindow &window) {
	// Game logic, updates everything between frames
	// Reset clock, recalculate deltatime
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();

	// Check and consume events ,allows player to close and move window
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		if (evnt.type == sf::Event::Closed) {
			window.close();
			return;
		}
	}

	for (auto &s : ships) {
		s->Update(dt);
	}

	Bullet::Update(dt);
}

void Render(sf::RenderWindow &window) {
	// Draw everything to the screen
	for (const auto s : ships) {
		if (s->is_visible()) {
			window.draw(*s);
		}
	}
	Bullet::Render(window);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load(window);
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
