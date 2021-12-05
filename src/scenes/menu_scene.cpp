#include <array>
#include <string>
#include "menu_scene.h"

MenuScene::MenuScene(GameEngine* game_engine, sf::RenderWindow* window, const AssetManager& asset_manager) :
	Scene(game_engine, window),
	m_asset_manager(asset_manager),
	m_background(),
	m_clock(),
	m_asteroid_manager(window->getSize()),
	m_current_menu_voice(0)
{
	// Create an opaque rectangle shape over the entire window
	const sf::Vector2f image_size{
		static_cast<float>(m_window->getSize().x) ,
		static_cast<float>(m_window->getSize().y)
	};
	const sf::Vector2f image_center = image_size / 2.0f;
	m_background.setSize(image_size);
	m_background.setOrigin(image_center);
	m_background.setPosition(image_center);
	m_background.setFillColor(sf::Color(sf::Color::Black.r, sf::Color::Black.g, sf::Color::Black.b, 120));

	// Create the text for all the voices of the menu
	// I'll put the menù in the center of the image
	const sf::Font& font = m_asset_manager.GetFont("atari");
	const int STARTING_HEIGHT = (static_cast<int>(image_size.y) - MENU_HEIGHT) / 2;

	// Generate all texts
	for (auto& a : m_menu_voices)
	{
		m_texts.emplace_back();
		sf::Text& t = m_texts.back();
		t.setFont(font);
		t.setString(a);
		t.setCharacterSize(CHAR_HEIGHT);
		t.setFillColor(sf::Color::White);
		t.setOrigin(t.getGlobalBounds().width / 2.0f, 0);
	}

	SetTextPosition();
}

void MenuScene::SetTextPosition()
{
	// The first text bloxk will be anchored in (image_width / 2, starting_height)
	const float STARTING_HEIGHT = (m_window->getSize().y - MENU_HEIGHT) / 2.0f;
	sf::Vector2f anchor_position = { m_window->getSize().x / 2.0f, STARTING_HEIGHT };
	for (int idx = 0; idx < m_texts.size(); ++idx)
	{
		sf::Text& current_text = m_texts[idx];
		if (m_current_menu_voice == idx)
		{
			current_text.setCharacterSize(BIG_CHAR_HEIGHT);
			current_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
			current_text.setFillColor(sf::Color::White);
		}
		else
		{
			current_text.setCharacterSize(CHAR_HEIGHT);
			current_text.setStyle(sf::Text::Regular);
			const sf::Color color{ sf::Color::White.r, sf::Color::White.g, sf::Color::White.b, 180 };
			current_text.setFillColor(color);
		}

		current_text.setOrigin(current_text.getGlobalBounds().width / 2.0f, 0);
		current_text.setPosition(anchor_position);
		anchor_position = anchor_position + sf::Vector2f{ 0.0f, static_cast<float>(current_text.getCharacterSize() + CHAR_PADDING) };
	}
}

void MenuScene::Pause()
{
	m_paused = true;
}

void MenuScene::Play()
{
	m_paused = false;
	m_clock.restart();
}

void MenuScene::Update()
{
	if (m_paused)
		return;

	sf::Time time_elapsed = m_clock.restart();
	m_asteroid_manager.update(time_elapsed);
}

void MenuScene::Render() const
{
	m_asteroid_manager.draw(*m_window);
	m_window->draw(m_background);

	for (auto& a : m_texts)
	{
		m_window->draw(a);
	}
}

void MenuScene::DoAction(const Action& action)
{
	switch (action.m_event.type)
	{
		case sf::Event::KeyReleased:
		{
			if (action.m_event.key.code == sf::Keyboard::Up)
			{
				m_current_menu_voice = (m_current_menu_voice > 0) ? m_current_menu_voice - 1 : m_texts.size() - 1;
				SetTextPosition();
			}
			if (action.m_event.key.code == sf::Keyboard::Down)
			{
				m_current_menu_voice = (m_current_menu_voice + 1) % m_texts.size();
				SetTextPosition();
			}
			if (action.m_event.key.code == sf::Keyboard::Escape)
			{
				m_window->close();
			}
			if (action.m_event.key.code == sf::Keyboard::Enter)
			{
				if (m_menu_voices[m_current_menu_voice] == "PLAY")
				{
					m_game_engine->ChangeScene(SceneId::PLAY);
				}
				if (m_menu_voices[m_current_menu_voice] == "EXIT")
				{
					m_window->close();
				}
			}
			
			break;
		}

		case sf::Event::Closed:
		{
			m_window->close();
			break;
		}
	}
}

