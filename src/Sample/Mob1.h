#pragma once
#include"Enemy.h"
#include"Entity.h"

class Enemy;

class Mob1 : public Enemy
{
public:
	void OnInitialize() override;
	void Attack() override;
};
