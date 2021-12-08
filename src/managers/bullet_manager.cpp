#include "managers/bullet_manager.h"

BulletManager::BulletManager()
{
}

const Bullet& BulletManager::create_bullet(const sf::Vector2f& position, float rotation)
{
	bullets.emplace_back(position, rotation);
	return bullets.back();
}

void BulletManager::update(const sf::Time& t1)
{
	// Remove all useless bullets
	static const auto remove_lamda = [](const Bullet& b) { return !b.IsAlive(); };
	bullets.remove_if(remove_lamda);

	for (auto& b : bullets)
	{
		b.update(t1);
	}
}

void BulletManager::draw(sf::RenderWindow& window) const
{
	for (auto& b : bullets)
	{
		b.draw(window);
	}
}
