#include <SFML/Graphics.hpp>
#include "player.h"
#include "ghost.h"
#include <iostream>
#include "system_renderer.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;
EntityManager em;
Player player;

void Load(RenderWindow &window) {
	// Loads items to the screen at game beginning

	// Adds player to entity manager
	em.list.push_back(std::shared_ptr<Entity>(&player));

	// Creates 4 ghosts and adds them to entity manager
	for (int i = 0; i < 4; i++) {
		Ghost* ghost = new Ghost();
		ghost->setColour(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		em.list.push_back(std::shared_ptr<Entity>(ghost));
	}

	// Sets player position
	em.list[0]->setPosition(Vector2f(700, 500));
}

void Update(RenderWindow &window) {
	// Game logic, updates everything between frames
	// Reset clock, recalculate deltatime
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();

	// Check and consume events, allows player to close and move window
	Event evnt;
	while (window.pollEvent(evnt)) {
		if (evnt.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Call entity manager update method
	em.update(dt);
}

void Render(RenderWindow &window) {
	// Call entity manager render method
	em.render();

	Renderer::render();
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Pacman");
	Renderer::initialise(window);
	Load(window);
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
