#include "Enemy.h"
#include "Utils.h"
#include "SampleScene.h"
#include <iostream>


void Enemy::OnInitialize()
{
    SetTag(2);
    SetMoveAble(true);
    SetSpeed(100);
}

void Enemy::OnUpdate()
{
    if (m_directionFacing == true)
        PlayAnimation("walkRight");
    else
        PlayAnimation("walkLeft");

    if (DetectPlayer())
        isChargingAttack = true;

    if (isChargingAttack == true)
    {
        m_attackTimer += GetDeltaTime();
        SetDirection(0, 0);
    }

    else     
        Move();

    if (m_attackTimer >= m_attackCooldown)
    {
        Attack();
        isChargingAttack = false;
        m_attackTimer = 0;
    }
    
    
    
    m_movingTimer += GetDeltaTime();
    isGrounded = false;
}

void Enemy::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(0) || collidedWith->IsTag(10))
	{

		Side side = GetCollidingSide(collidedWith);


		if (side == Side::DOWN)
		{
			isGrounded = true;
		}
	}


}


void Enemy::TakeDamage(int amount)
{

    m_hp -= amount;

    if (m_hp <= 0)
    {
        m_isAlive = false;
        Destroy();
    }

}

bool Enemy::DetectPlayer()
{
    Player* player = ((SampleScene*)GetScene())->GetPlayer();
    float playerPositionY = player->GetPosition().y;
    float playerPositionX = player->GetPosition().x;

   

    if (GetPosition().y - 50 < playerPositionY && playerPositionY  < GetPosition().y + 50)
    {
        if (m_directionFacing == 1 && playerPositionX < GetPosition().x + 500 && playerPositionX > GetPosition().x)
            return true;

        if (m_directionFacing == -1 && playerPositionX >GetPosition().x - 500 && playerPositionX < GetPosition().x)
            return true;
    }

    return false;
           
}

void Enemy::Move()
{
    if (m_movingTimer >= m_movingCooldown || !isGrounded)
    {
        m_directionFacing *= -1;
        m_movingTimer = 0;
        isGrounded = true;
    }
        

    SetDirection(m_directionFacing, 0);
}

void Enemy::Attack()
{
    std::cout << "fuhgiufhuiofghuifjmifghuifdsghjjksdfghiosdfghjksdfgjiousgdfhdxfgshuj" << std::endl;
}


