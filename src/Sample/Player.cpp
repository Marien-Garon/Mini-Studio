#include "Player.h"
#include "InputManager.h"
#include "SoundWave.h"
#include "SoundBlast.h"
#include "SampleScene.h"
#include "Grapple.h"
#include "Hook.h"
#include "Utils.h"
#include "Platform.h"
#include "Debug.h"
#include "SceneManager.h"

#include <iostream>

const char* Player::StateToStr() const
{
	switch ((State)m_stateMachine.GetState())
	{

	case State::Idle:
		return "Idle";

	case State::Moving:
		return "Moving";

	case State::Jumping:
		return "Jumping";

	case State::Attacking:
		return "Attacking";

	case State::LaunchingGrapple:
		return "LaunchingGrapple";

	case State::Travelling:
		return "Travelling";

	case State::Falling:
		return "Falling ";

	}
}

void Player::OnInitialize()
{
	SetRigidBody(true);
	SetMoveAble(true);
	mBaseSpeed = 300;
	mAcceleration = 0.f;
	mDecceleration = 0.f;
	mMaxSpeed = 0.f;

	SetSpeed(300);
	m_grappleRopeLenght = 2000.f;
	SetTag(1);

	StateMachineInitialize();
	
}

void Player::StateMachineInitialize()
{
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
		t_attacking->AddCondition(new HasNotAttackedThisBeatCondition());


		//->Lance le grappin si une commande de de lancement de grappin est appuyer
		Transition<Player>* t_launchingGrapple = m_stateMachine.AddTransition((int)State::Idle, (int)State::LaunchingGrapple);
		t_launchingGrapple->AddCondition(new GrappleCommandCondition);
		t_launchingGrapple->AddCondition(new IsGrappleCooldownBelowZeroCondition);
		t_launchingGrapple->AddCondition(new IsSomthingGrabbable);

		//->Va la ou le grappin lui a dit d'aller si il est au bon endroit
		Transition<Player>* t_travelling = m_stateMachine.AddTransition((int)State::Idle, (int)State::Travelling);
		t_travelling->AddCondition(new GrappleHasReachedTargetCondition());

		//->Tombe si la gravit� est activ�
		Transition<Player>* t_falling = m_stateMachine.AddTransition((int)State::Idle, (int)State::Falling);
		t_falling->AddCondition(new IsGravityPositiveCondition());
	}

	//MovingState
	{
		m_stateMachine.AddState(new MovingState());

		//->S'arr�te si on avance plus
		Transition<Player>* t_idle = m_stateMachine.AddTransition((int)State::Moving, (int)State::Idle);
		t_idle->AddCondition(new NoMoveCommandCondition());

		//->Saute si une commande de saut est appuyer
		Transition<Player>* t_jumping = m_stateMachine.AddTransition((int)State::Moving, (int)State::Jumping);
		t_jumping->AddCondition(new JumpingCommandCondition());
		t_jumping->AddCondition(new IsGravityOffCondition());

		//->Attaque si une commande de d'attaque est appuyer
		Transition<Player>* t_attacking = m_stateMachine.AddTransition((int)State::Moving, (int)State::Attacking);
		t_attacking->AddCondition(new AttackCommandCondition());
		t_attacking->AddCondition(new HasNotAttackedThisBeatCondition());

		//->Lance le grappin si une commande de de lancement de grappin est appuyer
		Transition<Player>* t_launchingGrapple = m_stateMachine.AddTransition((int)State::Moving, (int)State::LaunchingGrapple);
		t_launchingGrapple->AddCondition(new GrappleCommandCondition);
		t_launchingGrapple->AddCondition(new IsGrappleCooldownBelowZeroCondition);
		t_launchingGrapple->AddCondition(new IsSomthingGrabbable);

		//->Va la ou le grappin lui a dit d'aller si il est au bon endroit
		Transition<Player>* t_travelling = m_stateMachine.AddTransition((int)State::Moving, (int)State::Travelling);
		t_travelling->AddCondition(new GrappleHasReachedTargetCondition());

		//->Tombe si la gravit� est positive
		Transition<Player>* t_falling = m_stateMachine.AddTransition((int)State::Moving, (int)State::Falling);
		t_falling->AddCondition(new IsGravityPositiveCondition());
	}

	//JumpingState
	{
		m_stateMachine.AddState(new JumpingState());

		//->Attaque si une commande de d'attaque est appuyer
		Transition<Player>* t_attacking = m_stateMachine.AddTransition((int)State::Jumping, (int)State::Attacking);
		t_attacking->AddCondition(new AttackCommandCondition());
		t_attacking->AddCondition(new HasNotAttackedThisBeatCondition());

		//->Lance le grappin si une commande de de lancement de grappin est appuyer
		Transition<Player>* t_launchingGrapple = m_stateMachine.AddTransition((int)State::Jumping, (int)State::LaunchingGrapple);
		t_launchingGrapple->AddCondition(new GrappleCommandCondition);
		t_launchingGrapple->AddCondition(new IsGrappleCooldownBelowZeroCondition);
		t_launchingGrapple->AddCondition(new IsSomthingGrabbable);

		//->Va la ou le grappin lui a dit d'aller si il est au bon endroit
		Transition<Player>* t_travelling = m_stateMachine.AddTransition((int)State::Jumping, (int)State::Travelling);
		t_travelling->AddCondition(new GrappleHasReachedTargetCondition());

		//->Tombe si la gravit� est positive
		Transition<Player>* t_falling = m_stateMachine.AddTransition((int)State::Jumping, (int)State::Falling);
		t_falling->AddCondition(new IsGravityPositiveCondition());
	}

	//AttackingState

	{
		m_stateMachine.AddState(new AttackingState());

		//->S'arr�te si on avance plus
		Transition<Player>* t_idle = m_stateMachine.AddTransition((int)State::Attacking, (int)State::Idle);
		t_idle->AddCondition(new NoMoveCommandCondition());
		t_idle->AddCondition(new IsAnimationCooldownBelowZero());
		t_idle->AddCondition(new IsGravityOffCondition);

		//->Saute si une commande de saut est appuyer
		Transition<Player>* t_jumping = m_stateMachine.AddTransition((int)State::Attacking, (int)State::Jumping);
		t_jumping->AddCondition(new IsGravityNegativeCondition());

		//->Va la ou le grappin lui a dit d'aller si il est au bon endroit
		Transition<Player>* t_travelling = m_stateMachine.AddTransition((int)State::Attacking, (int)State::Travelling);
		t_travelling->AddCondition(new GrappleHasReachedTargetCondition());

		//->Tombe si la gravit� est positive
		Transition<Player>* t_falling = m_stateMachine.AddTransition((int)State::Attacking, (int)State::Falling);
		t_falling->AddCondition(new IsGravityPositiveCondition());
	}

	//LaunchingGrappleState

	{
		m_stateMachine.AddState(new LaunchingGrappleState());


		//->S'arr�te si on avance plus
		Transition<Player>* t_idle = m_stateMachine.AddTransition((int)State::LaunchingGrapple, (int)State::Idle);
		t_idle->AddCondition(new NoMoveCommandCondition());
		t_idle->AddCondition(new IsAnimationCooldownBelowZero());

		//->Saute si une commande de saut est appuyer
		Transition<Player>* t_jumping = m_stateMachine.AddTransition((int)State::LaunchingGrapple, (int)State::Jumping);
		t_jumping->AddCondition(new JumpingCommandCondition());
		t_jumping->AddCondition(new IsGravityOffCondition());

		//->Tombe si la gravit� est positive
		Transition<Player>* t_falling = m_stateMachine.AddTransition((int)State::LaunchingGrapple, (int)State::Falling);
		t_falling->AddCondition(new IsGravityPositiveCondition());
	}

	//TravellingState
	{
		m_stateMachine.AddState(new TravellingState());

		//->S'arr�te si on avance plus
		Transition<Player>* t_idle = m_stateMachine.AddTransition((int)State::Travelling, (int)State::Idle);
		t_idle->AddCondition(new IsPlayerAtGrappleDestination());
	}

	//FallingState
	{
		m_stateMachine.AddState(new FallingState());

		//->S'arr�te si on avance plus
		Transition<Player>* t_idle = m_stateMachine.AddTransition((int)State::Falling, (int)State::Idle);
		t_idle->AddCondition(new IsGravityOffCondition);

		//->Attaque si une commande de d'attaque est appuyer
		Transition<Player>* t_attacking = m_stateMachine.AddTransition((int)State::Falling, (int)State::Attacking);
		t_attacking->AddCondition(new AttackCommandCondition());
		t_attacking->AddCondition(new HasNotAttackedThisBeatCondition());

		//->Lance le grappin si une commande de de lancement de grappin est appuyer
		Transition<Player>* t_launchingGrapple = m_stateMachine.AddTransition((int)State::Falling, (int)State::LaunchingGrapple);
		t_launchingGrapple->AddCondition(new GrappleCommandCondition);
		t_launchingGrapple->AddCondition(new IsGrappleCooldownBelowZeroCondition);
		t_launchingGrapple->AddCondition(new IsSomthingGrabbable);

		//->Va la ou le grappin lui a dit d'aller si il est au bon endroit
		Transition<Player>* t_travelling = m_stateMachine.AddTransition((int)State::Falling, (int)State::Travelling);
		t_travelling->AddCondition(new GrappleHasReachedTargetCondition());

	}
}


void Player::OnUpdate()
{	
	bool isAttackingTimingGood = static_cast<SampleScene*>(GetScene())->IsAttackTimingOkay();

	if (!isAttackingTimingGood)
		m_hasAttackedThisBeat = false;

	if (!m_hasAttackedThisBeat && isAttackingTimingGood)
		m_resetBombo = true;


	if (!m_isGrounded && !GetIsGravity())
		StartGravity(0);

	SetDirection(0, 0);
	

	Debug::DrawText(GetPosition().x, GetPosition().y - 50, StateToStr(), 0.5f, 0.5f, sf::Color::White);

	m_stateMachine.Update(this, GetDeltaTime());

	m_grappleCooldown -= GetDeltaTime();
	m_isGrounded = false;

	if (m_resetBombo && !isAttackingTimingGood)
		m_numberOfGoodPress = 0;
	
	std::cout << mDirection.x << "/" << mDirection.y << std::endl;
	std::cout << m_collider.x << "/" << m_collider.y << std::endl;
}

void Player::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(0) || collidedWith->IsTag(10))
	{
		Platform* pf = (Platform*)collidedWith;

		if (pf->IsActive() == false)
			return;

		Side side = GetCollidingSide(collidedWith);

		if (side == Side::DOWN)
		{
			StopGravity();
			m_isGrounded = true;
		}
 			
			
	}
		
}

void Player::TakeDamage(int _damage)
{
	SceneManager& SM = SceneManager::getInstance();

	if (m_health <= 0)
	{
		m_health = 0;
		std::cout << "Player died." << std::endl;
		m_playerAlive = false;
		SM.ChangeScene("DEATH");
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

	if (in.IsControllerPressed(0, Controller::Button::A) || in.IsKeyHeld(sf::Keyboard::Space))
		Jump();

	SetDirection(0, 0);

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D))
	{
		m_directionFacing = 1;
		MoveRight();
	}

	if (in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))
	{
		m_directionFacing = -1;
		MoveLeft();
	}

	if (in.IsControllerPressed(0, Controller::Button::LB) || in.IsKeyPressed(sf::Keyboard::Enter))
	{
		Attack();
	}
	/*if (in.IsKeyPressed(sf::Keyboard::E))
	{
		Heal(1);
	}

	if (in.IsKeyPressed(sf::Keyboard::A))
	{
		TakeDamage(1);
	}*/

	else if (static_cast<SampleScene*>(GetScene())->IsAttackTimingOkay())
		m_numberOfGoodPress = 0;

}

void Player::Jump()
{
	if(!GetIsGravity())
		StartGravity(-200);
}

void Player::Attack()
{
	bool isAttackingTimingGood = static_cast<SampleScene*>(GetScene())->IsAttackTimingOkay();

	if (isAttackingTimingGood && !m_hasAttackedThisBeat)
	{
		m_numberOfGoodPress++;
		m_resetBombo = false;
		m_hasAttackedThisBeat = true;
	}
		
	else
		m_numberOfGoodPress = 0;


	if (m_numberOfGoodPress == 1)
	{
		AttackZone* attack = CreateEntity<AttackZone>(50, 50, sf::Color::Cyan);
		attack->SetPosition(GetPosition().x + m_directionFacing * GetCollider().width, GetPosition().y);

	}

	if (m_numberOfGoodPress == 3)
	{
		Shoot();
	}

}

void Player::Shoot()
{
	SoundBlast* attack = CreateEntity<SoundBlast>(50, 100, sf::Color::Cyan);
	attack->SetPosition(GetPosition().x, GetPosition().y);
	attack->SetDirection(m_directionFacing, 0);
	m_numberOfGoodPress = 0;
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

	m_grapple->GoToPosition(target->GetPosition(0.0f,0.0f).x, target->GetPosition(0.0f, 0.0f).y);

	mIsGravity = true;
	m_grappleCooldown = m_baseGrappleCooldown;
}

void Player::SetDirectionFacing(int direction)
{
	m_directionFacing = direction;
}

void Player::ControlSetDirectionFacing()
{
	InputManager& in = InputManager::Get();

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D))
		m_directionFacing = 1;

	if (in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))
		m_directionFacing = -1;
}

void Player::SetGrapple(Grapple* newGrapple)
{
	m_grapple = newGrapple;
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

bool Player::GetHasAttackedThisBeat()
{
	return m_hasAttackedThisBeat;
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

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D) || in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))
		return true;

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
	if (player->GetGrapple() == nullptr)
		return false;

	return player->GetGrapple()->AsReachedTarget();
}

bool IsGravityPositiveCondition::Test(Player* player)
{
	if (player->GetGravitySpeed() > 0)
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
	
	if (grapple == nullptr)
		return false;

	if (player->GetPosition().x == grapple->GetPosition().x && player->GetPosition().y == grapple->GetPosition().y)
		return true;
	return false;
}

bool IsSomthingGrabbable::Test(Player* player)
{
	if (player->SearchForHook() != nullptr)
		return true;

	return false;
}

bool HasNotAttackedThisBeatCondition::Test(Player* player)
{
	if (player->GetHasAttackedThisBeat())
		return false;
	
	return true;
}



void IdleState::Start(Player* type)
{
	if (type->GetDirectionFacing() == 1)
		type->PlayAnimation("idle_test_right");

	else
		type->PlayAnimation("idle_test_left");
	
}

void IdleState::Update(Player* type, float dt)
{
}

void IdleState::End(Player* type)
{

}



void MovingState::Start(Player* type)
{
}

void MovingState::Update(Player* type, float dt)
{

	type->ControlSetDirectionFacing();

	if (type->GetDirectionFacing() == 1)
	{
		type->MoveRight();
		type->PlayAnimation("running_to_right");
	}
	
	else if (type->GetDirectionFacing() == -1)
	{
		type->MoveLeft();
		type->PlayAnimation("running_to_left");
	}
}

void MovingState::End(Player* type)
{
}



void JumpingState::Start(Player* type)
{
	type->SetPosition(type->GetPosition().x, type->GetPosition().y - 1);
	if (type->GetDirectionFacing())
		type->PlayAnimation("jumping_to_right");

	else
		type->PlayAnimation("jumping_to_left");
	
	
	type->Jump();
}

void JumpingState::Update(Player* type, float dt)
{
	type->ControlSetDirectionFacing();

	InputManager& in = InputManager::Get();

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D))
	{
		type->MoveRight();
		type->PlayAnimation("jumping_to_right");
	}

	if (in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))
	{
		type->MoveLeft();
		type->PlayAnimation("jumping_to_left");
	}
}

void JumpingState::End(Player* type)
{
}



void AttackingState::Start(Player* type)
{

	if (type->GetNumberOfGoodPress() == 0)
	{
		if (type->GetDirectionFacing())
			type->PlayAnimation("first_combo_to_right");

		else
			type->PlayAnimation("first_combo_to_left");
	}
	
	if (type->GetNumberOfGoodPress() == 1)
	{
		if (type->GetDirectionFacing())
			type->PlayAnimation("second_combo_to_right");

		else
			type->PlayAnimation("second_combo_to_left");
	}

	if (type->GetNumberOfGoodPress() == 2)
	{
		if (type->GetDirectionFacing())
			type->PlayAnimation("third_combo_to_right");

		else
			type->PlayAnimation("third_combo_to_left");
	}

	type->Attack();
}

void AttackingState::Update(Player* type, float dt)
{
}

void AttackingState::End(Player* type)
{
}



void LaunchingGrappleState::Start(Player* type)
{
	if (type->GetDirectionFacing())
		type->PlayAnimation("grapple_to_right");

	else
		type->PlayAnimation("grapple_to_left");

	
	type->ThrowGrapple(type->SearchForHook());
}

void LaunchingGrappleState::Update(Player* type, float dt)
{
}

void LaunchingGrappleState::End(Player* type)
{
}



void TravellingState::Start(Player* type)
{
	//Animation ici
}

void TravellingState::Update(Player* type, float dt)
{

}

void TravellingState::End(Player* type)
{
	type->GetGrapple()->Destroy();
	type->SetGrapple(nullptr);
	type->GoToPosition(type->GetPosition().x + 20.f * type->GetDirectionFacing(), type->GetPosition().y);
	type->StartGravity(0);
}



void FallingState::Start(Player* type)
{
	if (type->GetDirectionFacing())
		type->PlayAnimation("falling_to_right");

	else
		type->PlayAnimation("falling_to_left");
}

void FallingState::Update(Player* type, float dt)
{
	type->ControlSetDirectionFacing();

	InputManager& in = InputManager::Get();

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D))
	{
		type->PlayAnimation("falling_to_right");
		type->MoveRight();

	}
		
	if (in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))
	{
		type->PlayAnimation("falling_to_left");
		type->MoveLeft();
	}
		
}

void FallingState::End(Player* type)
{
	if (type->GetDirectionFacing())
		type->PlayAnimation("landing_to_right");

	else
		type->PlayAnimation("landing_to_left");
}