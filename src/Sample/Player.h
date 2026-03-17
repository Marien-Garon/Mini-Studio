#pragma once
#include "Entity.h"
#include "StateMachine.h"
#include "Grapple.h"

class Hook;

class Player : public Entity
{
	enum class State
	{
		Idle, //Bouge pas
		Moving, //Bouge
		Jumping, //Saute 
		Attacking, //Attaque
		LaunchingGrapple, //Lance le grappin
		Travelling, //Avance avec le grappin
		Falling, //Tomber

		count //Total
	};

public:

	

	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override ;
	void OnDestroy() override {} ;

	void TakeDamage(int damage);
	void Heal(int heal);

	void Actions();
	void Jump();
	void Attack();

	void MoveRight();
	void MoveLeft();

	Hook* SearchForHook();
	void ThrowGrapple(Hook* target);

	void SetDirectionFacing(int direction);
	void ControlSetDirectionFacing();
	int GetDirectionFacing() { return m_directionFacing; };
	void SetGrapple(Grapple* newGrapple);
	Grapple* GetGrapple();
	float GetGrappleCooldown();
	bool GetIsGravity();
	float GetGravitySpeed();

private:

	const char* StateToStr() const; //debug

	int m_health = 3;
	int m_maxHealth = 3;
	bool m_playerAlive = true;
	int m_directionFacing = 1; //1 = regarde vers la droite, -1 = regarde vers la gauche
	int m_numberOfGoodPress = 0;

	float mAcceleration = 0.f;
	float mDecceleration = 0.f;
	float mBaseSpeed = 0.f;
	float mMaxSpeed = 0.f;

	float m_baseGrappleCooldown = 2;
	float m_grappleCooldown = m_baseGrappleCooldown;

	Grapple* m_grapple;
	float m_grappleRopeLenght;


	StateMachine<Player> m_stateMachine;


	friend class Grapple;

};

//ETAT POSSIBLE DU JOUEUR

class IdleState : public StateBase<Player>
{
public:
	void Start(Player* type) override;
	void Update(Player* type, float dt) override;
	void End(Player* type) override;
};

class MovingState : public StateBase<Player>
{
public:
	void Start(Player* type) override;
	void Update(Player* type, float dt) override;
	void End(Player* type) override;
};

class JumpingState : public StateBase<Player>
{
public:
	void Start(Player* type) override;
	void Update(Player* type, float dt) override;
	void End(Player* type) override;
};

class AttackingState : public StateBase<Player>
{
public:
	void Start(Player* type) override;
	void Update(Player* type, float dt) override;
	void End(Player* type) override;
};

class LaunchingGrappleState : public StateBase<Player>
{
public:
	void Start(Player* type) override;
	void Update(Player* type, float dt) override;
	void End(Player* type) override;
};

class TravellingState : public StateBase<Player>
{
public:
	void Start(Player* type) override;
	void Update(Player* type, float dt) override;
	void End(Player* type) override;
};

class FallingState : public StateBase<Player>
{
public:
	void Start(Player* type) override;
	void Update(Player* type, float dt) override;
	void End(Player* type) override;
};

//CONDITION DE TRANSITION D'ETATS

class NoMoveCommandCondition : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};

class MovingCommandCondition : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};

class JumpingCommandCondition : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};

class AttackCommandCondition : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};

class GrappleCommandCondition : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};

class GrappleHasReachedTargetCondition : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};

class IsGravityPositiveCondition : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};

class IsGravityNegativeCondition : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};

class IsGravityOffCondition : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};

class IsGrappleCooldownBelowZeroCondition : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};

class IsAnimationCooldownBelowZero : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};

class IsPlayerAtGrappleDestination : public Condition<Player>
{
public:
	bool Test(Player* player) override;
};