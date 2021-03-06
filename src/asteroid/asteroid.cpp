#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <utility>
#include <array>
#include "asteroid.h"

const CustomTexture Asteroid::texture{ "./images/asteroid.png" };

// Compute a random spawn point external to the windows
static sf::Vector2f compute_random_spawn_point(const sf::Vector2u& windows_size)
{
	// Window Sides
	//				1
	//		  |-------------|
	//		0 |			    | 2
	//		  |			    |
	//		  |-------------|
	//				3
	enum class Sides : std::size_t
	{
		LEFT = 0,
		UP,
		RIGHT,
		DOWN,
		SIDE_NUM
	};

	constexpr int OFFSET = 50;

	// For each side I define a starting point and a max offset (first and second value of each pair).
	// I'll use them to randomly generate a point as start + (x * offset) where x is a random value int [0, 1]
	using underlying_side_type = std::underlying_type_t<Sides>;
	const Sides choosen_side = static_cast<Sides>(std::rand() % static_cast<underlying_side_type>(Sides::SIDE_NUM));
	sf::Vector2f start, max_offset;
	switch (choosen_side)
	{
	case Sides::LEFT:
		start = { -OFFSET, 0 };
		max_offset = { 0, static_cast<float>(windows_size.y) };
		break;

	case Sides::UP:
		start = { 0, -OFFSET };
		max_offset = { static_cast<float>(windows_size.x), 0 };
		break;

	case Sides::RIGHT:
		start = { static_cast<float>(windows_size.x + OFFSET), 0 };
		max_offset = { 0, static_cast<float>(windows_size.y) };
		break;

	case Sides::DOWN:
		start = { 0, static_cast<float>(windows_size.y + OFFSET) };
		max_offset = { static_cast<float>(windows_size.x), 0 };
		break;

	default:
		assert(false);
		break;
	}

	const sf::Vector2f point = start + (max_offset * (static_cast<float>(std::rand()) / RAND_MAX));
	return point;
}

// Initialize asteroid with random speed and rot_speed
Asteroid::Asteroid(const sf::Vector2u& windows_size) :
	GameEntity(),
	alive(true)
{
	// Compute the starting random point
	const sf::Vector2f start = compute_random_spawn_point(windows_size);

	// Compute the random destination point
	// Avoiding point with same x or y of the start point
	sf::Vector2f destination = compute_random_spawn_point(windows_size);
	while (destination.x == start.x || destination.y == start.y)
	{
		destination = compute_random_spawn_point(windows_size);
	}

	// Compute the direction
	const sf::Vector2f direction = destination - start;
	const float module = std::sqrtf((direction.x * direction.x) + (direction.y * direction.y));
	const sf::Vector2f speed_versor{ direction.x / module, direction.y / module };

	const int random_number = std::rand();
	speed = speed_versor * static_cast<float>(random_number % 100);
	rot_speed = static_cast<float>(random_number % 360);

	const float scale = 0.2f + ((static_cast<float>(std::rand()) / RAND_MAX) * (0.8f));

	sprite.setTexture(texture);
	const sf::Vector2u texture_size = texture.getSize();
	sprite.setOrigin(texture_size.x / 2.0f, texture_size.y / 2.0f);
	sprite.setPosition(start.x, start.y);
	sprite.setScale(scale, scale);
}

void Asteroid::update(const sf::Time& t1)
{
	// Update position using speed along x and y
	const float delta_time_in_sec = t1.asSeconds();
	sprite.move(speed * delta_time_in_sec);

	// update angle using rot_speed
	sprite.rotate(rot_speed * delta_time_in_sec);
}

void Asteroid::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void Asteroid::HasBeenHit()
{
	// React to an hit
	alive = false;
	return;
}

const sf::Image& Asteroid::GetImage() const
{
	return texture.GetImage();
}
