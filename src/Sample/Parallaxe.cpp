#include "Parallaxe.h"
#include "SampleScene.h"
#include "AssetManager.h"

void Parallaxe::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();

	// Background
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("fond"), sf::Color::Green));

	int cameraSpeed = GetScene<SampleScene>()->GetCameraSpeed();

	// Layer 1
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer1"), sf::Color::Green));
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer1"), sf::Color::Green));
	m_backgrounds[1]->SetSpeed(cameraSpeed * 0.25f);
	m_backgrounds[2]->SetSpeed(cameraSpeed * 0.25f);

	// Layer 2
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer2"), sf::Color::Green));
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer2"), sf::Color::Green));
	m_backgrounds[3]->SetSpeed(cameraSpeed * 0.5f);
	m_backgrounds[4]->SetSpeed(cameraSpeed * 0.5f);

	// Layer 3
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer3"), sf::Color::Green));
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer3"), sf::Color::Green));
	m_backgrounds[5]->SetSpeed(cameraSpeed * 0.75f);
	m_backgrounds[6]->SetSpeed(cameraSpeed * 0.75f);

	for (int i = 0; i < m_backgrounds.size(); i++) {
		if (i == 0) {
			m_backgrounds[i]->SetPosition(0, 0, 0, 0);
		}
		
		if (i % 2  != 0) {
			m_backgrounds[i]->SetPosition(0, 0, 0, 0);
		}
		else {
			m_backgrounds[i]->SetPosition(m_backgrounds[0]->GetPosition(0, 1).x, 0, 0, 0);
		}
	}
}

void Parallaxe::Start()
{
	for (int i = 0; i < m_backgrounds.size(); i++) {
		m_backgrounds[i]->SetDirection(-1, 0);
	}
}

void Parallaxe::Stop()
{
	for (int i = 0; i < m_backgrounds.size(); i++) {
		m_backgrounds[i]->SetDirection(0, 0);
	}
}
