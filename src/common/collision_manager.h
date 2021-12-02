#pragma once

#include "game_entity.h"

class CollisionManager 
{
private:
	static bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b, const sf::Image& imgA, const sf::Image& imgB);

	template <typename Container_t>
	static typename Container_t::difference_type CheckForCollision(const GameEntity& first, const Container_t& container);

public:

	template <typename Container_t>
	static void ManageCollision(GameEntity& first, Container_t& container);
};

inline bool CollisionManager::PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b, const sf::Image& imgA, const sf::Image& imgB)
{
	sf::IntRect boundsA(a.getGlobalBounds());
	sf::IntRect boundsB(b.getGlobalBounds());
	sf::IntRect intersection;

	if (boundsA.intersects(boundsB, intersection))
	{
		const sf::Transform& inverseA(a.getInverseTransform());
		const sf::Transform& inverseB(b.getInverseTransform());

		const sf::Vector2u& sizeA(imgA.getSize());
		const sf::Vector2u& sizeB(imgB.getSize());

		const sf::Uint8* pixA = imgA.getPixelsPtr();
		const sf::Uint8* pixB = imgB.getPixelsPtr();

		sf::Vector2f point_a, point_b;
		const int xMax = intersection.left + intersection.width;
		const int yMax = intersection.top + intersection.height;

		for (int x = intersection.left; x < xMax; x++)
		{
			for (int y = intersection.top; y < yMax; y++)
			{
				point_a = inverseA.transformPoint((float)x, (float)y);
				point_b = inverseB.transformPoint((float)x, (float)y);

				// The returned value points to an array of RGBA pixels made of 8 bits integers components
				// The size of the array is width * height * 4.
				// Get the Idx to the pixel trasparency level
				int idxA = ((int)point_a.x + ((int)point_a.y) * sizeA.x) * 4 + 3;
				int idxB = ((int)point_b.x + ((int)point_b.y) * sizeB.x) * 4 + 3;

				if (point_a.x > 0 && point_a.y > 0 &&
					point_b.x > 0 && point_b.y > 0 &&
					point_a.x < sizeA.x && point_a.y < sizeA.y &&
					point_b.x < sizeB.x && point_b.y < sizeB.y &&
					pixA[idxA] > 0 &&
					pixB[idxB] > 0) 
				{
					return true;
				}
			}
		}
	}

	return false;
}

template<typename Container_t>
inline typename Container_t::difference_type CollisionManager::CheckForCollision(const GameEntity& first, const Container_t& container)
{
	const auto check_collision_lambda = [&first](const GameEntity& second) {
		return PixelPerfectCollision(first.GetSprite(), second.GetSprite(), first.GetImage(), second.GetImage());
	};

	auto itr = std::find_if(container.cbegin(), container.cend(), check_collision_lambda);
	if (itr != container.cend())
		return std::distance(container.cbegin(), itr);

	return std::distance(container.cbegin(), container.cend());
}

template <typename Container_t>
static void CollisionManager::ManageCollision(GameEntity& first, Container_t& container)
{
	typename Container_t::difference_type res = CheckForCollision(first, container);
	typename Container_t::iterator hit_element = container.begin();
	std::advance(hit_element, res);
	if (hit_element != container.end())
	{
		hit_element->HasBeenHit();
		first.HasBeenHit();
	}
}
