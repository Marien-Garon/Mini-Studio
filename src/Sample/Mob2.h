#pragma once
#include"Enemy.h"
#include"Entity.h"

class Mob2 : public Enemy
{
public:
    void Attack() override;
    void OnInitialize() override;
};


