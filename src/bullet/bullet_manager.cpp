#include "bullet/bullet_manager.h"

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
	static const auto remove_if_lambda = [](const Bullet& b) { return !b.IsAlive(); };
	std::remove_if(bullets.begin(), bullets.end(), remove_if_lambda);

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
