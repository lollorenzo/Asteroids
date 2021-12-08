#include "game_entity.h"

void GameEntity::CheckCollision(GameEntity& other)
{
	const sf::IntRect bounding_box_a(GetBoundingBox());
	const sf::IntRect bounding_box_b(other.GetBoundingBox());

	// Compute the intersection between the two bounding boxes
	sf::IntRect intersection;
	if (bounding_box_a.intersects(bounding_box_b, intersection))
	{
		for (int x = intersection.left; x < intersection.left + intersection.width; x++)
		{
			for (int y = intersection.top; y < intersection.top + intersection.height; y++)
			{
				const sf::Vector2f point{ static_cast<float>(x), static_cast<float>(y) };
				if (PixelLevelCollision(point) && other.PixelLevelCollision(point))
				{
					// Collision detected, notify both the entities
					HasBeenHit();
					other.HasBeenHit();
				}
			}
		}
	}
}

//bool GameEntity::PixelLevelCollision(const GameEntity& other) const
//{
//
//		// Get the images of the two sprites
//		const sf::Image& image_a = GetImage();
//		const sf::Image& image_b = other.GetImage();
//
//		// Get raw image buffer and image size
//		// The returned value of GetPixelPtr points to an array of RGBA pixels made of 8 bits integers components
//		// The size of the array is width * height * 4.
//		const sf::Vector2u& size_a(image_a.getSize());
//		const sf::Vector2u& size_b(image_b.getSize());
//
//		const sf::Uint8* pix_ptr_a = image_a.getPixelsPtr();
//		const sf::Uint8* pix_prt_b = image_b.getPixelsPtr();
//
//		// Get the inverse transform from the sprites
//		const sf::Transform& inverse_t_a(sprite_a.getInverseTransform());
//		const sf::Transform& inverse_t_b(sprite_b.getInverseTransform());
//
//		for (int x = intersection.left; x < intersection.left + intersection.width; x++)
//		{
//			for (int y = intersection.top; y < intersection.top + intersection.height; y++)
//			{
//				// For each pixel of the intersection
//				// Use the inverse transform to obtain the coordinates of the pixel into the original sprite image
//				const sf::Vector2f point_a = inverse_t_a.transformPoint(static_cast<float>(x), static_cast<float>(y));
//				const sf::Vector2f point_b = inverse_t_b.transformPoint(static_cast<float>(x), static_cast<float>(y));
//
//				const bool valid_a = point_a.x > 0 && point_a.y > 0 && point_a.x < size_a.x&& point_a.y < size_a.y;
//				const bool valid_b = point_b.x > 0 && point_b.y > 0 && point_b.x < size_b.x&& point_b.y < size_b.y;
//
//				if (valid_a && valid_b)
//				{
//					// Compute the pixel idx and check the image transparency value
//					// If both of the sprites have a value in the same pixel we have a collision
//					static const auto FromPointToIdx = [](int x, int y, int width) { return ((y * width + x) * 4) + 3; };
//					const int idx_a = FromPointToIdx(static_cast<int>(point_a.x), static_cast<int>(point_a.y), static_cast<int>(size_a.x));
//					const int idx_b = FromPointToIdx(static_cast<int>(point_b.x), static_cast<int>(point_b.y), static_cast<int>(size_b.x));
//
//					if (pix_ptr_a[idx_a] > 0 && pix_prt_b[idx_b] > 0)
//					{
//						return true;
//					}
//				}
//			}
//		}
//	}
//
//	return false;
//}
