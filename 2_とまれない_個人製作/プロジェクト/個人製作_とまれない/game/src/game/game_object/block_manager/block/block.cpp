#include "block.h"
#include"..\..\stage_gimmick_manager\stage_gimmick_manager.h"
#include"..\..\character_manager\character_manager.h"
#include"..\..\block_manager\block_manager.h"
#include"..\..\..\sound_play_manager\sound_play_manager.h"
#include"..\..\..\effect_manager\effect_manager.h"

const float CBlock::m_size = 150.0f;
const float CBlock::m_clash_score = 100.0f;

CBlock::CBlock(aqua::IGameObject* parent)
	:IGameObject(parent, "Block")
	, m_Position(0.0f, 0.0f)
	, m_Set(false)
	, m_Direction(BLOCK_DIRECTION::DUMMY)
	, m_GameObjectId(GAME_OBJECT_ID::BLOCK)
{
}

bool CBlock::GetSetFlg(void)const
{
	return m_Set;
}

void CBlock::Initialize(const aqua::CVector2& position, const bool set_flag)
{
	m_Position = position;
	m_Set = set_flag;
	m_Sprite.Create("data\\block.png");
	m_Sprite.position = m_Position;
}

void CBlock::Update(void)
{
}

void CBlock::Draw(const aqua::CVector2& player_travel_distance)
{
	m_Sprite.position = m_Position - player_travel_distance;
	m_Sprite.Draw();
}

void CBlock::Finalize(void)
{
	m_Sprite.Delete();
	DeleteObject();
	IGameObject::Finalize();
}

aqua::CVector2 CBlock::GetPosition(void)const
{
	return m_Position;
}

aqua::CVector2 CBlock::GetCenterPosition(void)const
{
	return aqua::CVector2(m_Position.x + m_size / 2.0f, m_Position.y + m_size / 2.0f);
}

aqua::CVector2 CBlock::GetSize(void)const
{
	return aqua::CVector2(m_size, m_size);
}

GAME_OBJECT_ID CBlock::GetGameObjectId(void)
{
	return m_GameObjectId;
}

BLOCK_DIRECTION CBlock::GetDirection(const aqua::CVector2& object_position, const aqua::CVector2& object_size, const aqua::CVector2& object_overcome)
{

	//プレイヤーの位置とサイズを考慮してブロックのどの面に当たっているかを判定
	if (object_position.y + object_size.y < m_Position.y + object_overcome.y && object_position.x < m_Position.x + m_size && object_position.x + object_size.x > m_Position.x)
	{
		return BLOCK_DIRECTION::UP;
	}
	else if(object_position.y > m_Position.y + m_size - object_overcome.y  &&object_position.x < m_Position.x + m_size && object_position.x + object_size.x > m_Position.x)
	{
		return BLOCK_DIRECTION::DOWN;
	}
	else if (object_position.x + object_size.x <= m_Position.x + object_overcome.x && object_position.y < m_Position.y + m_size && object_position.y + object_size.y > m_Position.y)
	{
		return BLOCK_DIRECTION::LEFT;
	}
	else if(object_position.x >= m_Position.x + m_size - object_overcome.x && object_position.y < m_Position.y + m_size && object_position.y + object_size.y > m_Position.y)
	{
		return BLOCK_DIRECTION::RIGHT;
	}
	else
	{
		return BLOCK_DIRECTION::SIDE;
	}
	
}

void CBlock::Clash(void)
{
	CBlockManager* block_manager = (CBlockManager*)aqua::FindGameObject("BlockManager");
	if (block_manager)
		block_manager->SaveData(m_Position);
	CSoundPlayManager* sm = (CSoundPlayManager*)aqua::FindGameObject("SoundPlayManager");
	if (sm)
		sm->Play(SOUND_ID::HIT);
	CEffectManager* effect = (CEffectManager*)aqua::FindGameObject("EffectManager");
	if (effect)
		effect->Create(EFFECT_ID::BLOCK_CLASH_EFFECT, m_Position );
	CScoreManager* score_manager = (CScoreManager*)aqua::FindGameObject("ScoreManager");
	if (score_manager)
		score_manager->AddScore(m_clash_score);
	DeleteObject();
	Finalize();
}

void CBlock::Set(const aqua::CVector2& player_travel_distance, const aqua::CVector2& mouse_pos, const bool push_key)
{
	//アイテムオブジェクトの位置をマウスカーソルの位置にする
	if (push_key && !m_Set)
	{
		aqua::CVector2 cursor_pos = mouse_pos;
		m_Position = cursor_pos + player_travel_distance;
	}
	else
	{
		m_Set = true;
	}
}
