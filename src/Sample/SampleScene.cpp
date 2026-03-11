#include "SampleScene.h"

#include "Debug.h"

#include"Player.h"
#include "Hook.h"

std::vector<Hook*> SampleScene::GetHooks()
{
	return m_hooks;
}

void SampleScene::OnInitialize()
{
	m_player = CreateEntity<Player>(50.f, sf::Color::Cyan);
	m_player->SetPosition(100, 500);

	for (int i = 0; i < 3; i++) {
		m_hooks.push_back(CreateEntity<Hook>(20.f, sf::Color::Yellow));
		m_hooks[i]->SetPosition(400.f - i * 100, 200.f + i * 100);
	}
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_player->LaunchGrapple(m_player->SearchForHook());
	}
}

void SampleScene::OnUpdate()
{
	
}