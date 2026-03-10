#include "Player.h"
#include "Grapple.h"
#include "Hook.h"
#include "SampleScene.h"

void Player::OnInitialize()
{
    m_grapple = CreateEntity<Grapple>(20.f, sf::Color::Magenta);
    m_grappleRopeLenght = 200.f;
}

Hook* Player::SearchForHook()
{
    std::vector<Hook*> hooks = GetScene<SampleScene>()->GetHooks();

    for (int i = 0; i < hooks.size(); i++) {

    }
}

void Player::LaunchGrapple(Hook* target)
{
}
