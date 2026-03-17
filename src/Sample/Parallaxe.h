#pragma once
#include <vector>
#include "Background.h"

class Parallaxe : public Entity
{
	std::vector<Background*> m_backgrounds;

public :
	void OnInitialize() override;

	void Start();

	void Stop();
};

