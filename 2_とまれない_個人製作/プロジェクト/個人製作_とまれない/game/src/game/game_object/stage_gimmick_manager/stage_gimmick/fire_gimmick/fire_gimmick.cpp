#include "fire_gimmick.h"

const aqua::CVector2 CFireGimmick::m_collsion_size = { 93.0f,164.0f };
const aqua::CVector2 CFireGimmick::m_texture_size = { 93.0f,164.0f };
const aqua::CVector2 CFireGimmick::m_adjustment_position = { 0.0f,2.0f };
const int CFireGimmick::m_damage = 1;
const float CFireGimmick::m_injection_range = 60.0f;

CFireGimmick::CFireGimmick(aqua::IGameObject* parent)
	:IStageGimmick(parent, "FireGimmick", m_damage, m_collsion_size, m_texture_size)
{
}

void CFireGimmick::Initialize(const aqua::CVector2& position, const bool set_flag)
{
	m_Position = position + m_adjustment_position;
	m_Sprite.Create("data\\fire.png");
	m_InjectionPosition = position ;
	m_InjectionPosition.x = m_collsion_size.x / 2.0f;
	m_Set = set_flag;
	m_Id = STAGE_GIMMICK_ID::FIRE;
}

void CFireGimmick::Update(void)
{
	IGameObject::Update();
}

void CFireGimmick::Draw(const aqua::CVector2& player_travel_distance)
{
		//プレイヤーの移動距離を考慮してアイテムオブジェクトの位置を調整
		//火の上側のスプライトを描画
		m_Sprite.position = m_Position - player_travel_distance + m_adjustment_position;
		m_Sprite.rect = aqua::CRect(0, 0, m_Collsion_Size.x, m_Collsion_Size .y- m_FireBottomSprite.GetTextureHeight());
		m_Sprite.Draw();
		//火の下側のスプライトを描画
		m_FireBottomSprite.position = aqua::CVector2(m_Position.x, m_Position.y + m_Collsion_Size .y-m_FireBottomSprite.GetTextureHeight()) - player_travel_distance;
		m_FireBottomSprite.Draw();

}

void CFireGimmick::PlayerHit(void)
{
}

void CFireGimmick::ObjectHit(const aqua::CVector2& object_position, const aqua::CVector2& object_size)
{
	m_Collsion_Size.y = m_collsion_size.y;
	//火の噴射の位置を中央に設定
	m_InjectionPosition = m_Position;
	m_InjectionPosition.x += m_collsion_size.x / 2.0f;

	aqua::CVector2 object_center=object_position+(object_size/2.0f);
	//縦の判定
	if (m_InjectionPosition.x - m_injection_range < object_center.x && object_center.x < m_InjectionPosition.x + m_injection_range)
	{
		//火の噴射の位置とオブジェクトの位置を比較して火の高さを設定
		if (m_InjectionPosition.y > object_position.y)
		{
			m_Collsion_Size.y = 0.0f;
			Finalize();
		}
		else
		{
			m_Collsion_Size.y = m_collsion_size.y - ((m_InjectionPosition.y + m_collsion_size.y) - object_position.y);
		}
		//火の下側のスプライトを作成
		m_FireBottomSprite.Create("data\\fire_bottom.png");
	}
	//m_Size = aqua::CVector2(m_Width, m_Height);
}

