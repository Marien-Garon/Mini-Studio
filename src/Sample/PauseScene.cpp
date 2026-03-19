#include "PauseScene.h"
#include <iostream>
#include "Enemy.h"
#include "Utils.h"
#include "Debug.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "Button.h"
#include "SampleScene.h"
#include "Camera.h"


void PauseScene::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();
	m_pauseMenu = CreateEntity<Entity>(AM.LoadSprite("pause"), sf::Color::Transparent);
    m_pauseMenu->SetSpriteScale(0.67, 0.67);

    m_buttonContinue = CreateEntity<Button>(AM.LoadSprite("boutoncontinue"), sf::Color::White);
    m_buttonRestart = CreateEntity<Button>(AM.LoadSprite("boutonrestart"), sf::Color::White);
    m_buttonSettings = CreateEntity<Button>(AM.LoadSprite("boutonsettings"), sf::Color::White);
    m_buttonExit = CreateEntity<Button>(AM.LoadSprite("boutonrexit"), sf::Color::White);
	
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

        float scaleX = winW / float(texSize.x);
        float scaleY = winH / float(texSize.y);
        sprite->setScale(scaleX, scaleY);

        sf::FloatRect bounds = sprite->getGlobalBounds();
        sprite->setPosition(centerX - bounds.width / 2.f, centerY - bounds.height / 2.f);
    }

    float offsetX = 180.f; 
    float offsetY = 90.f;

    // Ligne 1
    if (m_buttonContinue)
        m_buttonContinue->SetPosition(centerX - offsetX, centerY - offsetY);

    if (m_buttonRestart)
        m_buttonRestart->SetPosition(centerX + offsetX, centerY - offsetY);

    // Ligne 2
    if (m_buttonSettings)
        m_buttonSettings->SetPosition(centerX - offsetX, centerY + offsetY);

    if (m_buttonExit)
        m_buttonExit->SetPosition(centerX + offsetX, centerY + offsetY);
}
