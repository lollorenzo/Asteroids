#pragma once

#include <map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "scenes/scene.h"
#include "asset_manager/asset_manager.h"

enum class SceneId
{
	MENU = 0,
	PLAY
};

class GameEngine
{
public:
	GameEngine();

	void Run();
	void ChangeScene(const SceneId& scene);

private:
	using scene_map_type = std::map<SceneId, std::shared_ptr<Scene>>;

	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = (SCREEN_WIDTH * 9) / 16;

	sf::RenderWindow m_window;
	const AssetManager m_asset_manager;
	std::shared_ptr<Scene> m_current_scene;
	scene_map_type m_scenes;
};