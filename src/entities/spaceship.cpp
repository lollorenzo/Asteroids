#include <cmath>
#include "spaceship.h"

Spaceship::Spaceship(const sf::Vector2u& window_size, const AssetManager& asset_manager) :
	GameEntity{},
	texture(asset_manager.GetTexture("spaceship")),
	texture_image(asset_manager.GetImage("spaceship")),
	sprite(),
	speed{ 0.0f, 0.0f },
	accelleration_step { 100.0f },
	rotation_step{ 180.0f },
	friction_coefficent{ 0.70f },
	brake_coefficent{ 0.85f },
	firing_frequency{ 0.20f },
	health_bar{ asset_manager, 100, 10 },
	bullet_manager(),
	time_accumulator(0)
{
	sprite.setTexture(texture);
	sprite.setPosition(window_size.x / 2.0f, window_size.y / 2.0f);

	const sf::Vector2u texture_size = texture.getSize();
	sprite.setOrigin(texture_size.x / 2.0f, texture_size.y / 2.0f);
	sprite.setScale(0.5f, 0.5f);
	sprite.setRotation(270);
}

void Spaceship::update(const sf::Time& t1)
{
	update_motion(t1);
	shoot(t1);
	bullet_manager.update(t1);
}

void Spaceship::update_motion(const sf::Time& t1)
{
	static const float DEG_RAD_SCALE_FACTOR = (3.1415f / 180);
	const bool is_down_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	const bool is_up_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

	// Compute the speed decrease related to the friction
	speed = speed - (speed * friction_coefficent * t1.asSeconds());

	if (is_up_pressed || is_down_pressed)
	{
		if (is_up_pressed)
		{
			// increase the speed using the acceleration_step (oriented like the spaceship)
			const float current_direction = (sprite.getRotation() * DEG_RAD_SCALE_FACTOR);
			const sf::Vector2f acceleration_versor{ std::cos(current_direction), std::sin(current_direction) };
			const sf::Vector2f acceleration = acceleration_versor * accelleration_step;
			const sf::Vector2f speed_delta = t1.asSeconds() * acceleration;
			speed = speed + speed_delta;
		}
		if (is_down_pressed)
		{
			// Compute the speed decrease related to the brake
			speed = speed - (speed * brake_coefficent * t1.asSeconds());
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		sprite.rotate(-rotation_step * t1.asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sprite.rotate(rotation_step * t1.asSeconds());
	}

	sprite.move(speed * t1.asSeconds());
}

void Spaceship::shoot(const sf::Time& t1)
{
	static const float DEG_RAD_SCALE_FACTOR = (3.1415f / 180);
	const bool is_s_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (is_s_pressed)
	{
		time_accumulator += t1.asSeconds();
		if (time_accumulator > firing_frequency)
		{
			// Compute the spawn point of the bullet
			static const float DEG_RAD_SCALE_FACTOR = (3.1415f / 180);
			const float rad_rotation = (sprite.getRotation() * DEG_RAD_SCALE_FACTOR);
			const sf::Vector2f distance_versor{ std::cos(rad_rotation), std::sin(rad_rotation) };
			const sf::Vector2f distance = distance_versor * ((texture.getSize().x * sprite.getScale().x) / 2.0f);

			while (time_accumulator > firing_frequency)
			{
				bullet_manager.create_bullet(sprite.getPosition() + distance, sprite.getRotation());
				time_accumulator = time_accumulator - firing_frequency;
			}
		}
	}
	else
	{
		time_accumulator = 0.0f;
	}
}

void Spaceship::HasBeenHit()
{
	// React to an hit
	health_bar.Decrease();
	return;
}

bool Spaceship::PixelLevelCollision(const sf::Vector2f& point) const
{
	return true;
}

const sf::FloatRect Spaceship::GetBoundingBox() const
{
	return sprite.getGlobalBounds();
}

void Spaceship::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
	health_bar.Draw(window);
	bullet_manager.draw(window);
}

void Spaceship::CheckBulletCollision(GameEntity& other)
{
	for (auto& b : bullet_manager.get_bullets())
	{
		if (b.IsAlive())
		{
			b.CheckCollision(other);
		}
	}
}
