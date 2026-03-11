#include "Player.h"
#include "Grapple.h"
#include "Hook.h"
#include "SampleScene.h"
#include "Utils.h"
#include "Debug.h"

void Player::OnInitialize()
{
    SetSpeed(100.f);
    m_grappleRopeLenght = 200.f;
}

void Player::OnUpdate()
{
    if (m_grapple != nullptr) {
        if (GetPosition().x == m_grapple->GetPosition().x && GetPosition().y == m_grapple->GetPosition().y) {
            m_grapple->Destroy();
            m_grapple = nullptr;
            GoToPosition(GetPosition().x + 10.f, GetPosition().y);
        }
    }
}

Hook* Player::SearchForHook()
{
    std::vector<Hook*> hooks = GetScene<SampleScene>()->GetHooks();

	Hook* closestHook = nullptr;
	float closestDistance = m_grappleRopeLenght;
    for (int i = 0; i < hooks.size(); i++) {
        if (hooks[i]->GetPosition().y > GetPosition(0.5f, 1.f).y) {
            continue;
        }

        if (hooks[i]->GetPosition().x < GetPosition(0.5f, 1.f).x) {
			continue;
        }

        float currentDistance = Utils::GetDistance(GetPosition().x, GetPosition().y, hooks[i]->GetPosition().x, hooks[i]->GetPosition().y);
        if (currentDistance <= m_grappleRopeLenght) {
            if (currentDistance < closestDistance) {
                closestDistance = currentDistance;
				closestHook = hooks[i];
            }
        }
    }
	return closestHook;
}

void Player::LaunchGrapple(Hook* target)
{
    if (target == nullptr || m_grapple != nullptr) {
        return;
    }
    m_grapple = CreateEntity<Grapple>(20.f, sf::Color::Magenta);
    m_grapple->SetPosition(GetPosition().x + 1, GetPosition().y + 1);
    m_grapple->m_Owner = this;
    
    m_grapple->GoToPosition(target->GetPosition().x, target->GetPosition().y);
}
