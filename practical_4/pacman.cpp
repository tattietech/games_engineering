#include <memory>
#include "scene.h"
#include "pacman.h"
#include "system_renderer.h"
#include <sstream>

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

//pacman.cpp
void MenuScene::update(double dt) {
	Scene::update(dt);
	std::stringstream stream;
	text.setString("Almost Pacman");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load()
{

}

