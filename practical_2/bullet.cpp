#include "bullet.h"
#include "game.h"

unsigned char Bullet::bulletPointer;
Bullet Bullet::bullets[256];

Bullet::Bullet(){}

void Bullet::_Update(const float & dt)
{
	move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
}

void Bullet::Update(const float &dt) {
	for (Bullet& bullet : bullets) {
		bullet._Update(dt);
	}
}

void Bullet::Render(sf::RenderWindow &window)
{
	for (const Bullet &bullet : bullets) {
		window.draw(bullet);
	}
}

void Bullet::Fire(const sf::Vector2f & pos, const bool mode)
{
	// Fetch bullet from bullet pull
	if (bullets->bulletPointer == 256) {
		bullets->bulletPointer = 0;
	}
	Bullet& bullet = bullets[bulletPointer++];
	// Cut out of sprite sheet
	bullet.setTexture(spritesheet);
	bullet.setTextureRect(sf::IntRect(32, 32, 32, 32));
	bullet.setPosition(pos);
	bullet._mode = mode;
}
