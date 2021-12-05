#include "game_engine.h"
#include "scenes/menu_scene.h"
#include "scenes/play_scene.h"

GameEngine::GameEngine() :
    m_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Asteroid", sf::Style::Titlebar | sf::Style::Close),
    m_asset_manager(),
    m_current_scene(std::make_shared<MenuScene>(this, &m_window, m_asset_manager)),
    m_scenes{ std::make_pair(SceneId::MENU, m_current_scene) }
{
    auto play_scene_ptr = std::make_shared<PlayScene>(this, &m_window, m_asset_manager);
    m_scenes.insert({ SceneId::PLAY, play_scene_ptr });
}

void GameEngine::Run()
{
    // run the program as long as the window is open
    while (m_window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            m_current_scene->DoAction(Action(event));
        }

        // clear the window with black color
        m_window.clear(sf::Color::Black);

        m_current_scene->Update();
        m_current_scene->Render();

        // end the current frame
        m_window.display();
    }
}

void GameEngine::ChangeScene(const SceneId& scene)
{
    auto it = m_scenes.find(scene);
    if (it == m_scenes.end())
    {
        // No scene found, manage this error
    }
    m_current_scene->Pause();
    m_current_scene = it->second;
    m_current_scene->Play();
}
