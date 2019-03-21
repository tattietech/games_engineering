#include <SFML/Graphics.hpp>
#include "player.h"
#include "ghost.h"
#include <iostream>
#include "system_renderer.h"
#include "pacman.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;
EntityManager em;

void Load(RenderWindow &window) {
	// Loads items to the screen at game beginning
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();

	// Start at main menu
	activeScene = gameScene;
	
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

	activeScene->update(dt);
}

void Render(RenderWindow &window) {
	// Call entity manager render method
	activeScene->render();

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
