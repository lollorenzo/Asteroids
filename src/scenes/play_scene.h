#pragma once

#include <SFML/System/Time.hpp>
#include "scene.h"
#include "game_engine/game_engine.h"
#include "spaceship/spaceship.h"
#include "asteroid/asteroid_manager.h"
#include "asset_manager/asset_manager.h"

class PlayScene : public Scene
{
public:
	PlayScene(GameEngine* game_engine, sf::RenderWindow* window, const AssetManager& asset_manager);

	// Ereditato tramite Scene
	virtual void Update() override;
	virtual void Render() const override;
	virtual void DoAction(const Action& action) override;
	virtual void Pause() override;
	virtual void Play() override;

private:
	void ManageCollisions();

	sf::Clock m_clock;
	const AssetManager& m_asset_manager;
	AsteroidManager m_asteroid_manager;
	Spaceship m_spaceship;
};