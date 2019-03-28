#include "ecm.h"
#include <iostream>

Entity::Entity()
{
}

void Entity::update(const double dt) {
	_shape->setPosition(_position);
	//std::cout << "test" << std::endl;
}

void Entity::render()
{
}

const sf::Vector2f Entity::getPosition() {
	return _position;
}

const sf::Vector2f & Entity::getPosition() const
{
	// TODO: insert return statement here
}

void Entity::setPosition(const sf::Vector2f & pos) {
	_position = pos;
}

bool Entity::is_fordeletion() const
{
	return false;
}

float Entity::getRotation() const
{
	return 0.0f;
}

void Entity::setRotation(float _rotation)
{
}

bool Entity::isAlive() const
{
	return false;
}

void Entity::setAlive(bool _alive)
{
}

void Entity::setForDelete()
{
}

bool Entity::isVisible() const
{
	return false;
}

void Entity::setVisible(bool _visible)
{
}

void Entity::move(const sf::Vector2f &pos) {
	_position += pos;
}

Entity::Entity(std::unique_ptr<sf::Shape> s) : _shape(std::move(s)) {}


void EntityManager::update(const double dt) {
	for (auto &e : list) {
		e->update(dt);
	}
}

void EntityManager::render() {
	for (auto &e : list) {
		e->render();
	}
}

Component::Component(Entity * const p)
{
}

bool Component::is_fordeletion() const
{
	return false;
}

void Component::update(double dt) {

}

void Component::render() {

}
