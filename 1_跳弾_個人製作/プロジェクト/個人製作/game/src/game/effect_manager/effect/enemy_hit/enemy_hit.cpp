#include "enemy_hit.h"
#include "enemy_hit.h"
#include "enemy_hit.h"
#include "enemy_hit.h"
const float CEnemyEffect::m_scaling_speed = 0.5f;
const float CEnemyEffect::m_size = 128.0f;
const float CEnemyEffect::m_correction = 0.5f;

CEnemyEffect::CEnemyEffect(IGameObject* parent)
	:IEffect(parent,"EnemyEffect")
{
}

void CEnemyEffect::Initialize(const aqua::CVector2& position)
{
	m_Sprite.Create("data\\hit_effect.png");
	m_Sprite.position.x = position.x - m_size /2.0f;
	m_Sprite.position.y = position.y - m_size / 2.0f;
	m_Sprite.scale = { 1.5f,1.5f };
	m_Sprite.anchor = { 64.0f,64.0f };
	m_Timer.Setup(1.0f);
}

void CEnemyEffect::Update(void)
{
	//時間経過でエフェクトを消去
	m_Timer.Update();
	float time_limit = m_Timer.GetLimit()/2.0f;
	if (m_Timer.GetTime()<time_limit)
	{
	}
	else
	{
		m_Sprite.scale.x *= m_scaling_speed;
		m_Sprite.scale.y *= m_scaling_speed;
	}

	if (m_Timer.Finished())
	{
		Finalize();
	}
}

void CEnemyEffect::Draw(void)
{
	m_Sprite.Draw();
}


