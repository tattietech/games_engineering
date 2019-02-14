#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

void Load(RenderWindow &window) {
	// Loads items to the screen at game beginning
}

void Update(RenderWindow &window) {
	// Game logic, updates everything between frames

	// Check and consume events ,allows player to close and move window
	Event evnt;
	while (window.pollEvent(evnt)) {
		if (evnt.type == Event::Closed) {
			window.close();
			return;
		}
	}
}

void Render(RenderWindow &window) {
	// Draw everything to the screen
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Game Title");
	Load(window);
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
