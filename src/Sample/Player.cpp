#include "Player.h"
#include "InputManager.h"
#include "SoundWave.h"
#include "SoundBlast.h"
#include "SampleScene.h"
#include "Grapple.h"
#include "Hook.h"
#include "Utils.h"
#include "Platform.h"

#include <iostream>

void Player::OnInitialize()
{
	SetRigidBody(true);
	mBaseSpeed = 300;
	mAcceleration = 0.f;
	mDecceleration = 0.f;
	mMaxSpeed = 0.f;

	SetSpeed(300);
	m_grappleRopeLenght = 200.f;
	SetTag(1);

	//STATE MACHINE

	//IdleState
	{
		m_stateMachine.AddState(new IdleState());

		//->Avance si une commande de mouvement est appuyer
		Transition<Player>* t_moving = m_stateMachine.AddTransition((int)State::Idle, (int)State::Moving);
		t_moving->AddCondition(new MovingCommandCondition());

		//->Saute si une commande de saut est appuyer
		Transition<Player>* t_jumping = m_stateMachine.AddTransition((int)State::Idle, (int)State::Jumping);
		t_jumping->AddCondition(new JumpingCommandCondition());
		t_jumping->AddCondition(new IsGravityOffCondition());

		//->Attaque si une commande de d'attaque est appuyer
		Transition<Player>* t_attacking = m_stateMachine.AddTransition((int)State::Idle, (int)State::Attacking);
		t_attacking->AddCondition(new AttackCommandCondition());

		//->Lance le grappin si une commande de de lancement de grappin est appuyer
		Transition<Player>* t_launchingGrapple = m_stateMachine.AddTransition((int)State::Idle, (int)State::LaunchingGrapple);
		t_launchingGrapple->AddCondition(new GrappleCommandCondition);
		t_launchingGrapple->AddCondition(new IsGrappleCooldownBelowZeroCondition);

		//->Va la ou le grappin lui a dit d'aller si il est au bon endroit
		Transition<Player>* t_travelling = m_stateMachine.AddTransition((int)State::Idle, (int)State::Travelling);
		t_travelling->AddCondition(new GrappleHasReachedTargetCondition());

		//->Tombe si la gravité est activé
		Transition<Player>* t_falling = m_stateMachine.AddTransition((int)State::Idle, (int)State::Falling);
		t_falling->AddCondition(new IsGravityPositiveCondition());
	}

	//MovingState
	{
		m_stateMachine.AddState(new MovingState());

		//->S'arrète si on avance plus
		Transition<Player>* t_idle = m_stateMachine.AddTransition((int)State::Moving, (int)State::Idle);
		t_idle->AddCondition(new NoMoveCommandCondition());

		//->Saute si une commande de saut est appuyer
		Transition<Player>* t_jumping = m_stateMachine.AddTransition((int)State::Moving, (int)State::Jumping);
		t_jumping->AddCondition(new JumpingCommandCondition());
		t_jumping->AddCondition(new IsGravityOffCondition());

		//->Attaque si une commande de d'attaque est appuyer
		Transition<Player>* t_attacking = m_stateMachine.AddTransition((int)State::Moving, (int)State::Attacking);
		t_attacking->AddCondition(new AttackCommandCondition());

		//->Lance le grappin si une commande de de lancement de grappin est appuyer
		Transition<Player>* t_launchingGrapple = m_stateMachine.AddTransition((int)State::Moving, (int)State::LaunchingGrapple);
		t_launchingGrapple->AddCondition(new GrappleCommandCondition);
		t_launchingGrapple->AddCondition(new IsGrappleCooldownBelowZeroCondition);

		//->Va la ou le grappin lui a dit d'aller si il est au bon endroit
		Transition<Player>* t_travelling = m_stateMachine.AddTransition((int)State::Moving, (int)State::Travelling);
		t_travelling->AddCondition(new GrappleHasReachedTargetCondition());

		//->Tombe si la gravité est positive
		Transition<Player>* t_falling = m_stateMachine.AddTransition((int)State::Moving, (int)State::Falling);
		t_falling->AddCondition(new IsGravityPositiveCondition());
	}

	//JumpingState
	{
		m_stateMachine.AddState(new JumpingState());

		//->Attaque si une commande de d'attaque est appuyer
		Transition<Player>* t_attacking = m_stateMachine.AddTransition((int)State::Jumping, (int)State::Attacking);
		t_attacking->AddCondition(new AttackCommandCondition());

		//->Lance le grappin si une commande de de lancement de grappin est appuyer
		Transition<Player>* t_launchingGrapple = m_stateMachine.AddTransition((int)State::Jumping, (int)State::LaunchingGrapple);
		t_launchingGrapple->AddCondition(new GrappleCommandCondition);
		t_launchingGrapple->AddCondition(new IsGrappleCooldownBelowZeroCondition);

		//->Va la ou le grappin lui a dit d'aller si il est au bon endroit
		Transition<Player>* t_travelling = m_stateMachine.AddTransition((int)State::Jumping, (int)State::Travelling);
		t_travelling->AddCondition(new GrappleHasReachedTargetCondition());

		//->Tombe si la gravité est positive
		Transition<Player>* t_falling = m_stateMachine.AddTransition((int)State::Jumping, (int)State::Falling);
		t_falling->AddCondition(new IsGravityPositiveCondition());
	}

	//AttackingState

	{
		m_stateMachine.AddState(new AttackingState());

		//->S'arrète si on avance plus
		Transition<Player>* t_idle = m_stateMachine.AddTransition((int)State::Attacking, (int)State::Idle);
		t_idle->AddCondition(new NoMoveCommandCondition());
		t_idle->AddCondition(new IsAnimationCooldownBelowZero());

		//->Saute si une commande de saut est appuyer
		Transition<Player>* t_jumping = m_stateMachine.AddTransition((int)State::Attacking, (int)State::Jumping);
		t_jumping->AddCondition(new IsGravityNegativeCondition());

		//->Va la ou le grappin lui a dit d'aller si il est au bon endroit
		Transition<Player>* t_travelling = m_stateMachine.AddTransition((int)State::Attacking, (int)State::Travelling);
		t_travelling->AddCondition(new GrappleHasReachedTargetCondition());

		//->Tombe si la gravité est positive
		Transition<Player>* t_falling = m_stateMachine.AddTransition((int)State::Attacking, (int)State::Falling);
		t_falling->AddCondition(new IsGravityPositiveCondition());
	}

	//LaunchingGrappleState

	{
		m_stateMachine.AddState(new LaunchingGrappleState());

		
		//->S'arrète si on avance plus
		Transition<Player>* t_idle = m_stateMachine.AddTransition((int)State::LaunchingGrapple, (int)State::Idle);
		t_idle->AddCondition(new NoMoveCommandCondition());
		t_idle->AddCondition(new IsAnimationCooldownBelowZero());

		//->Saute si une commande de saut est appuyer
		Transition<Player>* t_jumping = m_stateMachine.AddTransition((int)State::LaunchingGrapple, (int)State::Jumping);
		t_jumping->AddCondition(new JumpingCommandCondition());
		t_jumping->AddCondition(new IsGravityOffCondition());

		//->Tombe si la gravité est positive
		Transition<Player>* t_falling = m_stateMachine.AddTransition((int)State::LaunchingGrapple, (int)State::Falling);
		t_falling->AddCondition(new IsGravityPositiveCondition());
	}

	//TravellingState
	{
		m_stateMachine.AddState(new TravellingState());

		//->S'arrète si on avance plus
		Transition<Player>* t_idle = m_stateMachine.AddTransition((int)State::Moving, (int)State::Idle);
		t_idle->AddCondition(new IsPlayerAtGrappleDestination());
	}

	//FallingState
	{
		m_stateMachine.AddState(new FallingState());

		//->S'arrète si on avance plus
		Transition<Player>* t_idle = m_stateMachine.AddTransition((int)State::Falling, (int)State::Idle);
		t_idle->AddCondition(new IsGravityOffCondition);

		//->Attaque si une commande de d'attaque est appuyer
		Transition<Player>* t_attacking = m_stateMachine.AddTransition((int)State::Falling, (int)State::Attacking);
		t_attacking->AddCondition(new AttackCommandCondition());

		//->Lance le grappin si une commande de de lancement de grappin est appuyer
		Transition<Player>* t_launchingGrapple = m_stateMachine.AddTransition((int)State::Falling, (int)State::LaunchingGrapple);
		t_launchingGrapple->AddCondition(new GrappleCommandCondition);
		t_launchingGrapple->AddCondition(new IsGrappleCooldownBelowZeroCondition);

		//->Va la ou le grappin lui a dit d'aller si il est au bon endroit
		Transition<Player>* t_travelling = m_stateMachine.AddTransition((int)State::Falling, (int)State::Travelling);
		t_travelling->AddCondition(new GrappleHasReachedTargetCondition());

	}
}


void Player::OnUpdate()
{
	if (!m_isJumping && !mIsGravity)
		StartGravity(0.f);

	if (m_grapple != nullptr) {
		if (GetPosition().x == m_grapple->GetPosition().x && GetPosition().y == m_grapple->GetPosition().y) {
			m_grapple->Destroy();
			m_grapple = nullptr;
			GoToPosition(GetPosition().x + 10.f, GetPosition().y);
		}
	}
	
	m_grappleCooldown -= GetDeltaTime();
}

void Player::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(0))
	{
		Platform* pf = (Platform*)collidedWith;

		if (pf->IsActive() == false)
			return;

		Side side = GetCollidingSide(collidedWith);
		
		std::cout << "Platform : " << collidedWith->GetCollider().x << "/" << collidedWith->GetCollider().y << std::endl;
		std::cout << "Player   : " << GetCollider().x << "/" << GetCollider().y + GetCollider().height << std::endl;


		switch (side) 
		{
		case Side::INSIDE:
			std::cout << "INSIDE" << std::endl;
			break;
		case Side::DOWN:
			std::cout << "DOWN" << std::endl;
			break;

		case Side::UP:
			std::cout << "UP" << std::endl;
			break;

		case Side::RIGHT:
			std::cout << "RIGHT" << std::endl;
			break;

		case Side::LEFT:
			std::cout << "LEFT" << std::endl;
			break;
		case Side::NONE:
			std::cout << "NONE" << std::endl;
			break;
		}

		if (side == Side::DOWN)
		{
 			StopGravity();
			m_isJumping = false;
		}
			
	}
		
}

void Player::TakeDamage(int _damage)
{
	if (m_health <= 0)
	{
		m_health = 0;
		std::cout << "Player died." << std::endl;
		m_playerAlive = false;
	}

	else {

		m_health -= _damage;
		std::cout << "Player take damage : " << _damage << std::endl;
		std::cout << "Current Health : " << m_health << std::endl;
	}
}

void Player::Heal(int _heal)
{
	if (m_health >= 100)
	{
		m_health = m_maxHealth;
		std::cout << "Player had max health" << std::endl;
	}

	else {

		m_health += _heal;
		std::cout << "Player got heal : " << _heal << std::endl;
		std::cout << "Current Health : " << m_health << std::endl;
	}
}

void Player::Actions()
{
	InputManager& in = InputManager::Get();
	float deltaTime = GetDeltaTime();

	if ((in.IsControllerPressed(0, Controller::Button::RB) || in.IsKeyPressed(sf::Keyboard::LShift)) && m_grappleCooldown <= 0) {
		ThrowGrapple(SearchForHook());
	}

	if ((in.IsControllerPressed(0, Controller::Button::A) || in.IsKeyHeld(sf::Keyboard::Space)) && m_isJumping == false && mIsGravity == false)
		Jump();

	SetDirection(0, 0);

	if ((in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D)) && m_isTravelling == false)
	{
		m_directionFacing = 1;
		MoveRight();
	}

	if ((in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q)) && m_isTravelling == false)
	{
		m_directionFacing = -1;
		MoveLeft();
	}

	if (in.IsControllerPressed(0, Controller::Button::LB) || in.IsKeyPressed(sf::Keyboard::Enter))
	{
		Attack();
	}

	else if (static_cast<SampleScene*>(GetScene())->IsAttackTimingOkay())
		m_numberOfGoodPress = 0;

}

void Player::Jump()
{
	StartGravity(-200);
	m_isJumping = true;
}

void Player::Attack()
{
	float windowWidth = GetScene()->GetWindowWidth();
	bool isAttackingTimingGood = static_cast<SampleScene*>(GetScene())->IsAttackTimingOkay();

	if (isAttackingTimingGood)
	{
		m_numberOfGoodPress++;
		
	}


	else
	{
		m_numberOfGoodPress = 0;
	}



	if (m_numberOfGoodPress == 1)
	{
		SoundWave* attack = CreateEntity<SoundWave>(50, 50, sf::Color::Cyan);
		attack->SetPosition(GetPosition().x, GetPosition().y);
		attack->GoToDirection(windowWidth * m_directionFacing, GetPosition().y);

	}

	else if (m_numberOfGoodPress == 3)
	{
		SoundBlast* attack = CreateEntity<SoundBlast>(50, 100, sf::Color::Cyan);
		attack->SetPosition(GetPosition().x, GetPosition().y);
		attack->GoToDirection(windowWidth * m_directionFacing, GetPosition().y);
		m_numberOfGoodPress = 0;
	}

}

void Player::MoveRight()
{
	float deltaTime = GetDeltaTime();

	mSpeed += mAcceleration * deltaTime;
	SetDirection(1, 0, mBaseSpeed + (mAcceleration * deltaTime));

}

void Player::MoveLeft()
{
	float deltaTime = GetDeltaTime();

	mSpeed += mAcceleration * deltaTime;
	SetDirection(-1, 0, mBaseSpeed + (mAcceleration * deltaTime));

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

		if (m_directionFacing == 1)
		{
			if (hooks[i]->GetPosition().x < GetPosition(0.5f, 1.f).x) {
				continue;
			}
		}

		else
			if (hooks[i]->GetPosition().x > GetPosition(0.5f, 1.f).x) {
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

void Player::ThrowGrapple(Hook* target)
{
	if (target == nullptr || m_grapple != nullptr) {
		return;
	}
	m_grapple = CreateEntity<Grapple>(20.f, 20.f, sf::Color::Magenta);
	m_grapple->SetPosition(GetPosition().x + 1, GetPosition().y + 1);
	m_grapple->m_Owner = this;

	m_grapple->GoToPosition(target->GetPosition().x, target->GetPosition().y);

	m_isJumping = false;
	mIsGravity = true;
	m_isTravelling = true;
	m_grappleCooldown = m_baseGrappleCooldown;
}

void Player::SetDirectionFacing(int direction)
{
	m_directionFacing = direction;
}

Grapple* Player::GetGrapple()
{
	return m_grapple;
}

float Player::GetGrappleCooldown()
{
	return m_grappleCooldown;
}

bool Player::GetIsGravity()
{
	return mIsGravity;
}

float Player::GetGravitySpeed()
{
	return mGravitySpeed;
}

bool NoMoveCommandCondition::Test(Player* player)
{
	InputManager& in = InputManager::Get();

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D) || in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))
		return false;
	
	return true;
}

bool MovingCommandCondition::Test(Player* player)
{
	InputManager& in = InputManager::Get();

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D))
	{
		player->SetDirectionFacing(1);
		return true;
	}

	if (in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))
	{
		player->SetDirectionFacing(-1);
		return true;
	}

	return false;
}

bool JumpingCommandCondition::Test(Player* player)
{
	InputManager& in = InputManager::Get();

	if (in.IsControllerPressed(0, Controller::Button::A) || in.IsKeyHeld(sf::Keyboard::Space))
		return true;

	return false;
}

bool AttackCommandCondition::Test(Player* player)
{
	InputManager& in = InputManager::Get();

	if (in.IsControllerPressed(0, Controller::Button::LB) || in.IsKeyPressed(sf::Keyboard::Enter))
		return true;

	return false;
}

bool GrappleCommandCondition::Test(Player* player)
{
	InputManager& in = InputManager::Get();

	if (in.IsControllerPressed(0, Controller::Button::RB) || in.IsKeyPressed(sf::Keyboard::LShift))
		return true;

	return false;
}

bool GrappleHasReachedTargetCondition::Test(Player* player)
{
	return player->GetGrapple()->AsReachedTarget();
}

bool IsGravityPositiveCondition::Test(Player* player)
{
	if (player->GetGravitySpeed() >= 0)
		return true;

	return false;
}

bool IsGravityNegativeCondition::Test(Player* player)
{
	if (player->GetGravitySpeed() < 0)
		return true;

	return false;
}

bool IsGravityOffCondition::Test(Player* player)
{
	return !player->GetIsGravity();
}

bool IsGrappleCooldownBelowZeroCondition::Test(Player* player)
{
	if (player->GetGrappleCooldown() <= 0)
		return true;

	return false;
}

bool IsAnimationCooldownBelowZero::Test(Player* player)
{
	return true;
}

bool IsPlayerAtGrappleDestination::Test(Player* player)
{
	Grapple* grapple = player->GetGrapple();
	if (player->GetPosition().x == grapple->GetPosition().x && player->GetPosition().y == grapple->GetPosition().y)
		return true;
	return false;
}
