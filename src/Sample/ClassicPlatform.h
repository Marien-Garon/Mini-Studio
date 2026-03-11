#pragma once

#include "Platform.h"


class ClassicPlatform : public Platform
{
public:
	ClassicPlatform(float width, float height, const sf::Color& color) {};


	void OnUpdate(float dt) override;
	void OnPlayerContact()override;
};