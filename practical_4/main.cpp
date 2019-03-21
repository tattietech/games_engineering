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
	em.list.push_back(std::shared_ptr<Entity>(&player));

	for (int i = 0; i < 4; i++) {
		Ghost* ghost = new Ghost();
		ghost->setColour(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		em.list.push_back(std::shared_ptr<Entity>(ghost));
	}

	em.list[0]->setPosition(Vector2f(700, 500));
}

void Update(RenderWindow &window) {
	// Game logic, updates everything between frames
	// Reset clock, recalculate deltatime
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();

	// Check and consume events ,allows player to close and move window
	Event evnt;
	while (window.pollEvent(evnt)) {
		if (evnt.type == Event::Closed) {
			window.close();
			return;
		}
	}

	for (auto &e : em.list) {
		e->update(dt);
	}
}

void Render(RenderWindow &window) {
	// Draw everything to the screen
	em.render(window);
	Renderer::render();
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Pacman");
	Load(window);
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
