//#pragma once
//#include "Entity.h"
//#include"Platform.h"
//
//class Platform;
//
//class Enemy : public Entity
//{
//protected:
//    int m_Hpmax = 50;
//    int m_damage = 10;
//    int m_direction = 1;
//
//    float m_speed = 100.f;
//    float m_maxDistance = 200.f;
//    float m_attackCooldown = 3.0f;   
//    float m_attackTimer = 0.0f;
//    int m_directionFacing = 1;
//    bool m_isAlive = true;
//
//    std::string m_name = "Enemy";
//
//    sf::Vector2f m_startPos;
//
//    Platform* m_platform = nullptr;
//
//protected:
//    void UpdateMovementAndTimers();
//
//public:
//    void SetPlatform(Platform* p) { m_platform = p; }
//    void SetName(const std::string& name) { m_name = name; }
//
//    void Initialize();
//    void OnUpdate() override;
//
//    float TakeDamage(int amount);
//
//
//    virtual void Attack();
//};
#pragma once
#include "Entity.h"

class Enemy : public Entity
{
protected :

	int m_hp = 3;
	int m_damage = 1;

	bool m_isAlive = true;
	int m_directionFacing = 1;
	float m_attackCooldown = 2.0f;
	float m_attackTimer = 0.0f;
	bool isChargingAttack = false;
	float m_movingTimer = 0.0f;
	float m_movingCooldown = 2.0f;
	bool isGrounded = false;

	bool activate = false;

public :

	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
	void TakeDamage(int amount);
	bool DetectPlayer();
	void Move();
	void Active() { activate = true; };

	virtual void Attack();
};