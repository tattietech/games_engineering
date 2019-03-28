#include <memory>
#include "scene.h"
#include "pacman.h"
#include "system_renderer.h"
#include <sstream>
#include "player.h"
#include "ghost.h"

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

MenuScene::MenuScene()
{
}

//pacman.cpp
void MenuScene::update(double dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	text.setString("Almost Pacman");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {
	text.setCharacterSize(50);
	text.setPosition(200, 200);
}

void GameScene::respawn() {
	// To do
}

void GameScene::update(double dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render() {
	Scene::render();
}


Player player;
void GameScene::load() {
	// Adds player to entity manager
	_ents.list.push_back(std::shared_ptr<Player>(&player));

	// Creates 4 ghosts and adds them to entity manager
	for (int i = 0; i < 4; i++) {
		Ghost* ghost = new Ghost();
		ghost->setColour(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		_ents.list.push_back(std::shared_ptr<Entity>(ghost));
	}

	// Sets player position
	_ents.list[0]->setPosition(sf::Vector2f(700, 500));
}
