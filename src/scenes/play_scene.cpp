#include "play_scene.h"

PlayScene::PlayScene(GameEngine* game_engine, sf::RenderWindow* window, const AssetManager& asset_manager) :
	Scene(game_engine, window),
	m_asset_manager(asset_manager),
	m_clock(),
	m_asteroid_manager(window->getSize()),
	m_spaceship(window->getSize()) { }

void PlayScene::Update()
{
	if (m_paused)
		return;

	sf::Time time_elapsed = m_clock.restart();
	m_asteroid_manager.update(time_elapsed);
	m_spaceship.update(time_elapsed);
}

void PlayScene::Render() const
{
	m_asteroid_manager.draw(*m_window);
	m_spaceship.draw(*m_window);
}

void PlayScene::DoAction(const Action& action)
{
	switch (action.m_event.type)
	{
		case sf::Event::KeyReleased:
		{
			if (action.m_event.key.code == sf::Keyboard::Escape)
			{
				m_game_engine->ChangeScene(SceneId::MENU);
			}

			break;
		}
	}
}

void PlayScene::Pause()
{
	m_paused = true;
}

void PlayScene::Play()
{
	m_paused = false;
	m_clock.restart();
}
