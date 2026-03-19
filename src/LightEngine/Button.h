#pragma once

#include "Entity.h"
#include <functional>

class Button : public Entity
{
private:

	std::function<void()> m_onClick;
	bool hasBeenClick = false;
	bool isHover = false;

public:

	void SetFunction(std::function<void()> _func) { m_onClick = _func; };
	void Click() { hasBeenClick = true; };

	virtual void UpdateEvent(const sf::Event& _event);

	virtual void OnUpdate() override;
	virtual void OnInitialize() override;
	//void OnDestroy() override;
};