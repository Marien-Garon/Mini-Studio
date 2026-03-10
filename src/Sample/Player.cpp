#include "Player.h"
#include "Grapple.h"
#include "Hook.h"
#include "SampleScene.h"
#include "Utils.h"

void Player::OnInitialize()
{
    m_grapple = CreateEntity<Grapple>(20.f, sf::Color::Magenta);
    m_grappleRopeLenght = 200.f;
}

Hook* Player::SearchForHook()
{
    std::vector<Hook*> hooks = GetScene<SampleScene>()->GetHooks();

	Hook* closestHook = nullptr;
	float closestDistance = m_grappleRopeLenght;
    for (int i = 0; i < hooks.size(); i++) {
        if (hooks[i]->GetPosition().y < GetPosition(0.5f, 1.f).y) {
            continue;
        }

        if (hooks[i]->GetPosition().x < GetPosition(0.f, 0.5f).x) {
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
    if (target == nullptr) {
        return;
    }
    m_grapple->GoToPosition(GetPosition());
	m_grapple->SetDirection(target->GetPosition().x - GetPosition().x, target->GetPosition().y - GetPosition().y);
}
