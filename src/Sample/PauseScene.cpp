#include "PauseScene.h"
#include <iostream>

#include "Enemy.h"
#include "Utils.h"
#include "Debug.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "SampleScene.h"
#include "Camera.h"


void PauseScene::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();
	m_pauseMenu = CreateEntity<Entity>(AM.CreateSprite("pause"));

	m_buttonContinue = CreateEntity<Entity>(350, 65, sf::Color::Transparent);
	m_buttonRestart = CreateEntity<Entity>(350, 65, sf::Color::Transparent);
	
	m_buttonSave = CreateEntity<Entity>(350, 65, sf::Color::Transparent);
	m_buttonSettings = CreateEntity<Entity>(350, 65, sf::Color::Transparent);
	m_buttonExit = CreateEntity<Entity>(100, 65, sf::Color::Transparent);
	
}

void PauseScene::OnEvent(const sf::Event& event)
{
    GameManager* gm = GameManager::Get();

    if (!gm) return;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (m_buttonContinue->IsInside(mousePos.x, mousePos.y))
        {
            SceneManager::getInstance().ChangeScene("LEVEL");
        }

        if (m_buttonExit && m_buttonExit->IsInside(mousePos.x, mousePos.y))
        {
            if (gm && gm->GetWindow())
                gm->GetWindow()->close();
        }

        if (m_buttonRestart->IsInside(mousePos.x, mousePos.y))
        {
            GameManager::Get()->ClearCurrentSceneEntities();
            OnInitialize();
        }
    }
}

void PauseScene::OnUpdate()
{
    GameManager* gm = GameManager::Get();
    if (!gm) return;

    gm->SetFixedView();

    float winW = static_cast<float>(gm->GetWindow()->getSize().x);
    float winH = static_cast<float>(gm->GetWindow()->getSize().y);

    float centerX = winW / 2.f;
    float centerY = winH / 2.f;

    if (m_pauseMenu && m_pauseMenu->HasSprite() && m_pauseMenu->GetSprite())
    {
        sf::Sprite* sprite = m_pauseMenu->GetSprite();
        sf::Vector2u texSize = sprite->getTexture()->getSize();

        float scale = std::min(winW / float(texSize.x), winH / float(texSize.y));
        sprite->setScale(scale, scale);

        sf::FloatRect bounds = sprite->getGlobalBounds();
        sprite->setPosition(centerX - bounds.width / 2.f, centerY - bounds.height / 2.f);
    }

    float btnWidth = 350.f;
    if (m_buttonContinue) m_buttonContinue->SetPosition(centerX - 16, centerY - 60);
    if (m_buttonRestart)  m_buttonRestart->SetPosition(centerX - 16, centerY + 35);
    if (m_buttonSave)     m_buttonSave->SetPosition(centerX - 16, centerY + 128);
    if (m_buttonSettings) m_buttonSettings->SetPosition(centerX - 16, centerY + 222);
    if (m_buttonExit)     m_buttonExit->SetPosition(centerX + 410, centerY + 290);
}
