#pragma once
#include "item_object.h"
#include"..\..\block_manager\block\block.h"
const aqua::CVector2 IItemObject::m_overcome_size = aqua::CVector2{ 75.0f,50.0f };
const float IItemObject::m_gravity = 0.5f;
const int IItemObject::m_score = 100;


IItemObject::IItemObject(aqua::IGameObject* parent, const std::string& name, const float width, const float height)
	: aqua::IGameObject(parent,"ItemObject")
	, m_Position(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_Width(width)
	, m_Height(height)
	, m_YVelocity(0.0f)
	, m_LandingFlg(false)
	, m_Set(false)
	, m_GameObjectId(GAME_OBJECT_ID::ITEM_OBJECT)
	,m_TimeSpeed(1.0f)
	,m_TextureSize(0.0f,0.0f)
	,m_Size(width,height)
{
}

void IItemObject::Initialize(const aqua::CVector2& position, const bool set_flg)
{
	m_Set=set_flg;
	m_Position = position;
	m_Sprite.Create("data\\block.png");
	m_Sprite.position = m_Position;
	m_TextureSize = aqua::CVector2(m_Sprite.GetTextureWidth(), m_Sprite.GetTextureHeight());
}

void IItemObject::Update(void)
{
	//アイテムオブジェクトの重力の処理
	if (m_Set)
	Gravity();

	IGameObject::Update();
}


void IItemObject::Draw(const aqua::CVector2& player_travel_distance)
{
	m_Sprite.position = m_Position - player_travel_distance;
	m_Sprite.Draw();
}

void IItemObject::Finalize(void)
{
	m_Sprite.Delete();
	DeleteObject();
}


void IItemObject::Hit(ICharacter*& character)
{
	CScoreManager* score_manager = (CScoreManager*)aqua::FindGameObject("ScoreManager");
	if(score_manager)
		score_manager->AddScore(m_score);
}

void IItemObject::BlockHit(const aqua::CVector2& hit_position, const BLOCK_DIRECTION direction)
{
	aqua::CVector2 local_position = hit_position;
	//キャラクターがブロックの上にいない場合落下状態にする
	if (direction == BLOCK_DIRECTION::UP )
	{
		//ブロックに当たったときのキャラクターの位置を調整
		m_Position.y = local_position.y - m_Size.y;
		m_LandingFlg = true;
	}
	//ドリルを所持している場合は止まらない
	if (direction == BLOCK_DIRECTION::DOWN)
	{
		//ブロックに当たったときのキャラクターの位置を調整
		m_Position.y = local_position.y;
		m_Velocity.y = 0.0f;
	}
	if (direction == BLOCK_DIRECTION::LEFT)
	{
		m_Position.x = local_position.x - m_TextureSize.x / 2.0f - m_Size.x / 2.0f;
		m_Velocity.x = 0.0f;
	}
	if (direction == BLOCK_DIRECTION::RIGHT)
	{
		m_Position.x = local_position.x;
	}
}

void IItemObject::Gravity(void)
{
	//時間の速さを取得

	//アイテムが地面にいるかどうかで重力の処理を分ける
	if (m_LandingFlg)
	{
		m_Velocity.y = 0.0f;
	}
	else
	{
		m_Velocity.y += m_gravity;
	}
	m_LandingFlg = false;
	m_Position += m_Velocity * m_TimeSpeed;
}

void IItemObject::Set(const aqua::CVector2& player_travel_distance, const aqua::CVector2& mouse_pos, const bool push_key)
{
	//アイテムオブジェクトの位置をマウスカーソルの位置にする
	if (push_key && !m_Set)
	{
		aqua::CVector2 cursor_pos = mouse_pos;
		m_Position = cursor_pos + player_travel_distance;
		m_YVelocity = 0.0f;
	}
	else
	{
		m_Set = true;
	}

}

aqua::CVector2 IItemObject::GetPosition(void)const
{
	return m_Position;
}

aqua::CVector2 IItemObject::GetSize(void) const
{
	return m_Size;
}

aqua::CVector2 IItemObject::GetOverComeSize(void)const
{
	return m_overcome_size;
}

float IItemObject::GetWidth(void)const
{
	return m_Width;
}

float IItemObject::GetHeight(void)const
{
	return m_Height;
}

bool IItemObject::GetSetFlg(void)const
{
	return m_Set;
}


GAME_OBJECT_ID IItemObject::GetGameObjectId(void)const
{
	return m_GameObjectId;
}

void IItemObject::SetTimeSpeed(const float rate)
{
	m_TimeSpeed = rate;
}


