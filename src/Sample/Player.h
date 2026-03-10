#pragma once
#include "Entity.h"

class Grapple;
class Hook;

class Player : public Entity
{
	Grapple* m_grapple;
	float m_grappleRopeLenght;

public :

	void OnInitialize() override;

	Hook* SearchForHook();

	void LaunchGrapple(Hook* target);
};

