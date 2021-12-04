#pragma once

#include "game_entity.h"

class CollisionManager 
{
public:
	template <typename Container_t>
	static void ManageCollision(GameEntity& current, Container_t& container);

};

template <typename Container_t>
static void CollisionManager::ManageCollision(GameEntity& current, Container_t& container)
{
	const auto DetectCollision = [&current](GameEntity& second) {
		return current.CheckCollision(second);
	};

	std::for_each(container.begin(), container.end(), DetectCollision);
}
