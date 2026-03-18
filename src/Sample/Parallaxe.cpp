#include "Parallaxe.h"
#include "SampleScene.h"
#include "AssetManager.h"
#include "Camera.h"

void Parallaxe::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();

	// Background
	m_backgrounds.push_back(CreateEntity<Background>(AM.CreateSprite("fond")));
	m_backgrounds[0]->SetSpeed(0);
	
	// Layer 1
	m_backgrounds.push_back(CreateEntity<Background>(AM.CreateSprite("layer1")));
	m_backgrounds.push_back(CreateEntity<Background>(AM.CreateSprite("layer1")));
	m_backgrounds[1]->SetSpeed(250.f);
	m_backgrounds[2]->SetSpeed(250.f);

	// Layer 2
	m_backgrounds.push_back(CreateEntity<Background>(AM.CreateSprite("layer2")));
	m_backgrounds.push_back(CreateEntity<Background>(AM.CreateSprite("layer2")));
	m_backgrounds[3]->SetSpeed(500.f);
	m_backgrounds[4]->SetSpeed(500.f);

	// Layer 3
	m_backgrounds.push_back(CreateEntity<Background>(AM.CreateSprite("layer3")));
	m_backgrounds.push_back(CreateEntity<Background>(AM.CreateSprite("layer3")));
	m_backgrounds[5]->SetSpeed(750.f);
	m_backgrounds[6]->SetSpeed(750.f);

	//sf::Vector2f cameraPos = GetScene<SampleScene>()->GetCamera()->GetView()->getCenter();
	float windowWidth = GetScene<SampleScene>()->GetWindowWidth();
	for (int i = 0; i < m_backgrounds.size(); i++) {
		if (i == 0) {
			m_backgrounds[i]->SetPosition(0, 0);
		}else if (i % 2  != 0) {
			m_backgrounds[i]->SetPosition(0, 0);
		}
		else {
			m_backgrounds[i]->SetPosition(windowWidth / 2, 0, 0.f, 0.5f);
		}
	}
}

void Parallaxe::OnUpdate()
{
	for (int i = 0; i < m_backgrounds.size(); i++) {
		sf::Vector2f cameraPos = GetScene<SampleScene>()->GetCamera()->GetView()->getCenter();
		sf::Vector2f backgroundPos = m_backgrounds[i]->GetPosition();
		m_backgrounds[i]->SetPosition(backgroundPos.x + cameraPos.x, backgroundPos.y + cameraPos.y);
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
