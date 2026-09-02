#include "ground_enemy.h"

const aqua::CVector2 CGroundEnemy::m_texture_scale = aqua::CVector2(1.0f, 0.7f);
const aqua::CVector2 CGroundEnemy::m_position_adjustment = aqua::CVector2(70.0f, 0.0f);
const float CGroundEnemy::m_width = 90.0f;
const float CGroundEnemy::m_height = 145.0f;
const float CGroundEnemy::m_run_speed = 0.0f;
const float CGroundEnemy::m_i_frame_timer = 0.0f;
const int CGroundEnemy::m_first_life_point = 1;



CGroundEnemy::CGroundEnemy(aqua::IGameObject* parent)
	:ICharacter(parent, "GroundEnemy", m_run_speed, m_width, m_height, m_first_life_point, m_i_frame_timer)
{
}

void CGroundEnemy::Initialize(const aqua::CVector2& position, const aqua::CVector2& travel_distance)
{
	//アニメーションスプライトの作成
	m_TravelDistance = travel_distance;
	m_AnimationSprite.Create("data\\enemy.ass");
	m_Position = position - m_position_adjustment;
	m_AnimationSprite.position = m_Position;
	m_AnimationSprite.scale = m_texture_scale;
	m_AnimationSprite.Change("stop_animation");
	//キャラクターの状態を走る状態にする
	m_State = CHARACTER_STATE::RUN;
	//キャラクターの体力を初期体力にする
	m_IFrameTimer.Setup(m_I_Frame_Time);

	m_Ncolor = 0xff00ffff;
	m_Icolor = 0x5500ffff;

	m_AnimationSprite.scale = m_texture_scale;
	m_TextureScale = m_texture_scale;
	m_TextureSize = aqua::CVector2(m_AnimationSprite.GetFrameWidth(), m_AnimationSprite.GetFrameHeight());
}



