#include "bullet.h"
#include "game.h"
#include "Ship.h"

unsigned char Bullet::bulletPointer;
Bullet Bullet::bullets[256];

Bullet::Bullet(){}

void Bullet::_Update(const float & dt)
{
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		// off screen - do nothing
		return;
	}
	else {
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const sf::FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s == &player) {
				// Players nullets don't collide with player
				continue;
			}
			if (_mode && s != &player) {
				// Invader bullets don't collide with other invaders
				continue;
			}
			if (!s->is_exploded() &&
				s->getGlobalBounds().intersects(boundingBox)) {
				// Explode the ships
				s->Explode();
				// warp bullet off screen
				setPosition(-100, - 100);
				return;
			}
		}
	}
}

void Bullet::Update(const float &dt) {
	for (Bullet &bullet : bullets) {
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
	Bullet& bullet = bullets[++bulletPointer];
	// Cut out of sprite sheet
	bullet.setTexture(spritesheet);
	bullet.setTextureRect(sf::IntRect(32, 32, 32, 32));
	bullet.setPosition(pos);
	bullet._mode = mode;
}
