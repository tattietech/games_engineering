#include <SFML/Graphics.hpp>
#include<iostream>
#include "player.h"


const int gameWidth = 800;
const int gameHeight = 600;
Player player;

void Load(sf::RenderWindow &window) {
	// Loads items to the screen at game beginning
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

	player.update(dt);
}

void Render(sf::RenderWindow &window) {
	// Draw everything to the screen
	player.render(window);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Game Title");
	Load(window);
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}

