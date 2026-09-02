#pragma once
#include "trampoline.h"
const int CTrampoline::m_max_guide = 10;
const float CTrampoline::m_width = 53.0f;
const float CTrampoline::m_height = 50.0f;
const float CTrampoline::m_bounce_power = -18.0f;
const float CTrampoline::m_gravity = 0.5f;

CTrampoline::CTrampoline(aqua::IGameObject* parent)
	:IItemObject(parent, "Trampoline",m_width,m_height)
	, m_GuidePointInterval(0)
{
}

void CTrampoline::Initialize(const aqua::CVector2& position,const bool set_flag)
{
	m_Set = set_flag;
	m_Sprite.Create("data\\trampoline.png");
	m_Sprite.position = position;
	m_GuideSprite.Create("data\\life.png");
	m_GuidePoint = AQUA_NEW aqua::CVector2[m_max_guide];
	m_GuideSprite.color = aqua::CColor(100, 255, 255, 255);
	m_GuidePointInterval = 10;
	m_GameObjectId = GAME_OBJECT_ID::TRAMPOLINE;
	m_TextureSize = aqua::CVector2(m_Sprite.GetTextureWidth(), m_Sprite.GetTextureHeight());

}

void CTrampoline::Draw(const aqua::CVector2& player_travel_distance)
{
	
		//プレイヤーの移動距離を考慮してガイドポイントの位置を調整
		CCharacterManager* character_manager = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
		if (!character_manager->GetPlayer())
			return;
	
		if (!m_GuidePoint)
			return;
		float player_run_speed = character_manager->GetPlayer()->GetRunSpeed();

		aqua::CVector2 local_position = m_Position;
		aqua::CVector2 local_velocity = aqua::CVector2(player_run_speed, m_bounce_power);
		//トランポリンのガイドポイントの位置を設定
		for (int i = 0;i < m_GuidePointInterval* m_max_guide;i++)
		{
			local_position += local_velocity;
			local_velocity.y += m_gravity;	//重力の影響
			if (i % m_GuidePointInterval == 0)
			{
				m_GuidePoint[i / m_GuidePointInterval] = local_position;
				m_GuidePoint[i / m_GuidePointInterval].x +=m_Width / 2.0f;
			}
		}

	
	//プレイヤーの移動距離を考慮してアイテムオブジェクトの位置を調整
	m_Sprite.position = m_Position - player_travel_distance;
	m_Sprite.Draw();
	//ガイドスプライトの描画
	for (int i = 0;i < m_max_guide;i++)
	{
		m_GuideSprite.position= m_GuidePoint[i] - player_travel_distance;
		m_GuideSprite.Draw();
	}

}

void CTrampoline::Finalize(void)
{
	AQUA_SAFE_DELETE(m_GuidePoint);

	m_GuideSprite.Delete();
	m_Sprite.Delete();
	DeleteObject();
}

void CTrampoline::Hit(ICharacter*& character)
{
	//プレイヤーのY軸の速度をトランポリンの跳ねる力にする
	character->Jump(m_bounce_power);
}


