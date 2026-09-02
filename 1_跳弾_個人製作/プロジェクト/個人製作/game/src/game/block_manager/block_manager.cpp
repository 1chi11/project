#include"..\effect_manager\effect_manager.h"
#include "block_manager.h"
#include"..\bullet_manager\bullet_manager.h"
#include "..\sound_manager/sound_manager.h"
#include"block/move_felix_block/move_felix_block.h"
#include"block/nomal_felix_block/nomal_felix_block.h"
#include"block/nomal_block/nomal_block.h"

CBlockManager::CBlockManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "BlockManager", "Manager")
	,m_Block(nullptr)
	,m_EffectManager(nullptr)
	,m_Having(true)
{
}

void CBlockManager::Create(BLOCK_ID id, aqua::CVector2 position1, aqua::CVector2 position2, float speed)
{
	CSoundManager* sm = (CSoundManager*)aqua::FindGameObject("SoundManager");
	sm->Create(SOUND_ID::BLOCK_CREATE, false);

	IBlock* block =nullptr;
	switch (id)
	{
	case BLOCK_ID::NOMAL_BLOCK:
		if (m_Having)
		{
			m_Block = aqua::CreateGameObject<CNomalBlock>(this);
			m_Having = false;
		}
		break;
	case BLOCK_ID::NOMAL_FELIX_BLOCK:
		block = aqua::CreateGameObject<CNomalFelixBlock>(this);
		break;
	case BLOCK_ID::MOVE_FELIX_BLOCK:
		block = aqua::CreateGameObject<CMoveFelixBlock>(this);
		break;
	default:
		break;
	}
	if (m_Block)
	{
		m_Block->Initialize(position1, position2, speed);
		return;
	}
	if (!block)return;
	block->Initialize(position1, position2, speed);
		return;
}

void CBlockManager::AllDelete()
{
	for (auto it : m_ChildObjectList)
	{
		IBlock* block = (IBlock*)it;
		if (block->GetFelixBlock()==FELIX_BLOCK_ID::NOMAL_BLOCK)
			block->Finalize();
		m_Having = true;
	}
	m_Block = nullptr;
}

void CBlockManager::OneDelete()
{
	if (!m_Block)
	{
		return;
	}
	m_Block->Finalize();
	m_Block = nullptr;
	m_Having = true;
}

void CBlockManager::Reset()
{
	for (auto it : m_ChildObjectList)
	{
		IBlock* block = (IBlock*)it;
		if (block->GetFelixBlock()==FELIX_BLOCK_ID::FELIX_BLOCK)
			block->Finalize();
	}
	m_Having = true;
}



IBlock* CBlockManager::BlockHitRotated(aqua::CVector2 position, float ball_radius)
{
	IBlock* block = nullptr;
	//ãŒÀ‚ðÝ’è
	float len = 9999999.0f;
	
	for (auto it : m_ChildObjectList)
	{
		IBlock* blk = (IBlock*)it;
		
		aqua::CVector2 v = blk->GetCenterPosition() - position;
		//’e‚Æ“G‚ÌÚG
		if (len > v.Length())
		{
			block = blk;
			len = v.Length();
		}
	}
	if (!block)return nullptr;

	if (block->HitCircleRotatedRect(position, ball_radius))
	{
		//hit
		return block;
	}

	return nullptr;
}

void CBlockManager::SetBlock(bool sw)
{
	if (!m_Having)
	{
		m_Block->SetBlock(sw);
		m_Having = true;
		m_Block = nullptr;
	}
}

void CBlockManager::MoveBlock(aqua::CPoint point)
{
	if (!m_Block)return;
		m_Block->MoveBlock(point);
}

void CBlockManager::CatchMoveBlock(aqua::CPoint mouse_point)
{
	if (!m_Having)
	{
		return;
	}
	for (auto it : m_ChildObjectList)
	{
		IBlock* block = (IBlock*)it;
		if (!block)
			return;
		aqua::CVector2 v;
		v.x = (float)mouse_point.x - block->GetCenterPosition().x;
		v.y = (float)mouse_point.y - block->GetCenterPosition().y;
		if (v.Length() < 50.0f&&block->GetFelixBlock()==FELIX_BLOCK_ID::NOMAL_BLOCK)
		{
			m_Block = block;
			m_Block->SetBlock(true);
			m_Having = false;
		}
	}
}

bool CBlockManager::GetHaving()
{
	return m_Having;
}

void CBlockManager::SpinBlock(int spin)
{
	if (!m_Block)
		return;
	m_Block->SpinBlock(spin);
}



