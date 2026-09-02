#include "stage_gimmick.h"
const aqua::CVector2 IStageGimmick::m_overcome_size = { 0.0f,30.0f };

IStageGimmick::IStageGimmick(aqua::IGameObject* parent, const std::string& name, const int damage, const aqua::CVector2& collsion_size, const aqua::CVector2& texture_size)
	: aqua::IGameObject(parent, name)
	, m_Position(0.0f, 0.0f)
	, m_BlockSize(150.0f,150.0f)
	, m_Texture_Size(texture_size)
	, m_Collsion_Size(collsion_size)
	, m_Damage(damage)
	, m_Set(false)
{
}


void IStageGimmick::Initialize(const aqua::CVector2& position, const bool set_flag)
{
	m_Position.x = position.x + m_BlockSize.x/2.0f - m_Texture_Size.x/2.0f;
	m_Position.y = position.y + m_BlockSize.y - m_Texture_Size.y;
	m_Sprite.Create("data\\fire.png");
	m_Id = STAGE_GIMMICK_ID::DUMMY;
	m_Set = set_flag;
}

void IStageGimmick::Update(void)
{
	IGameObject::Update();
}

void IStageGimmick::Draw(const aqua::CVector2& player_travel_distance)
{
	//プレイヤーの移動距離を考慮してアイテムオブジェクトの位置を調整
	m_Sprite.position = m_Position - player_travel_distance;
	m_Sprite.Draw();
}

void IStageGimmick::Finalize(void)
{
	m_Sprite.Delete();
	DeleteObject();
}

aqua::CVector2 IStageGimmick::GetOverComeSize() const
{
	return m_overcome_size;
}

aqua::CVector2 IStageGimmick::GetPosition(void)const
{
	return m_Position;
}

aqua::CVector2 IStageGimmick::GetSize(void)const
{
	return m_Collsion_Size;
}

STAGE_GIMMICK_DIRECTION_ID IStageGimmick::GetDirection(const aqua::CVector2& object_position, const aqua::CVector2& object_size)const
{
	//オブジェクトの位置とサイズを考慮してギミックのどの面に当たっているかを判定
	if (object_position.y + object_size.y <= m_Position.y&& object_position.x <= m_Position.x + m_Collsion_Size.x && object_position.x + object_size.x >= m_Position.x)
	{
		return STAGE_GIMMICK_DIRECTION_ID::UP;
	}
	else if ( object_position.y >= m_Position.y + m_Collsion_Size.y && object_position.x <= m_Position.x + m_Collsion_Size.x && object_position.x + object_size.x >= m_Position.x)
	{
		return STAGE_GIMMICK_DIRECTION_ID::DOWN;
	}
	else if (object_position.x + object_size.x <= m_Position.x && object_position.y <= m_Position.y + m_Collsion_Size.y && object_position.y + object_size.y >= m_Position.y)
	{
		return STAGE_GIMMICK_DIRECTION_ID::LEFT;
	}
	else if (object_position.x >= m_Position.x + m_Collsion_Size.x && object_position.y <= m_Position.y + m_Collsion_Size.y && object_position.y + object_size.y >= m_Position.y)
	{
		return STAGE_GIMMICK_DIRECTION_ID::RIGHT;
	}
	else
	{
		return STAGE_GIMMICK_DIRECTION_ID::DUMMY;
	}
}

STAGE_GIMMICK_ID IStageGimmick::GetStageGimmickId(void)const
{
	return m_Id;
}


void IStageGimmick::PlayerHit(void)
{
	//プレイヤーとギミックが当たったときの処理
}

void IStageGimmick::ObjectHit(const aqua::CVector2& object_position, const aqua::CVector2& object_size)
{
	//オブジェクトとギミックが当たったときの処理
}



void IStageGimmick::Set(const aqua::CVector2& player_travel_distance, const aqua::CVector2& cursor_pos, const bool push_key)
{
	//ギミックの位置をマウスカーソルの位置にする
	if (push_key && !m_Set)
	{
		aqua::CVector2 local_position = cursor_pos;
		m_Position = local_position + player_travel_distance;
	}
	else
	{
		//ギミックがセットされたときの処理
		m_Set = true;
	}
}


bool IStageGimmick::GetSetFlg(void)const
{
	return m_Set;
}
