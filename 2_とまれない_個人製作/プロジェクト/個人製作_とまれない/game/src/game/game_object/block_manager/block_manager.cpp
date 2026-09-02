#include "block_manager.h"
#include "block\block.h"
#include"..\character_manager\character\character.h"
#include"..\stage_gimmick_manager\stage_gimmick\stage_gimmick.h"
#include"..\item_object_manager\item_object\item_object.h"
#include"..\..\mouse\mouse.h"
#include"..\..\collision\collision.h"
const int CBlockManager::max = 100;

CBlockManager::CBlockManager(aqua::IGameObject* parent)
	:IGameObject(parent, "BlockManager")
	,m_SaveNumber(0)
{
}

void CBlockManager::Initialize(void)
{
	m_BlockData = std::make_unique<SaveBlockData[]>(max);
	IGameObject::Initialize();
}

void CBlockManager::Update(void)
{
	SetBlocks();
	StageGimmickBlockHitCheck();
	IGameObject::Update();
}

void CBlockManager::Draw(void)
{
	//プレイヤーの移動距離を考慮してブロックの位置を調整
	CCharacterManager* character_manager = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
	if (!character_manager)
		return;
	aqua::CVector2 player_travel_distance = character_manager->GetPlayerTravelDistance();

	for (auto it : m_ChildObjectList)
	{
		CBlock* block = (CBlock*)it;
		if (block->GetGameObjectState() != aqua::GAME_OBJECT_STATE::DEAD)
		block->Draw(player_travel_distance);
	}
}


void CBlockManager::Create(const aqua::CVector2& position,const bool set_flg)
{
	CBlock* block = aqua::CreateGameObject<CBlock>(this);
	block->Initialize(position, set_flg);
}

void CBlockManager::Delete()
{
	m_BlockData.reset();
	for (auto it : m_ChildObjectList)
	{
		CBlock* block = (CBlock*)it;
		block->Finalize();
	}
}

void CBlockManager::CharacterBlockHitCheck(ICharacter*& character)
{
	for (auto it : m_ChildObjectList)
	{
		CBlock* block = (CBlock*)it;
		//キャラクターの移動距離を考慮してブロックの位置を調整
		aqua::CVector2 block_pos = block->GetPosition();
		aqua::CVector2 block_size = block->GetSize();

		//ブロックとキャラクターの当たり判定
		//キャラクター側の位置に移動距離を加算して当たり判定を行う
		aqua::CVector2 character_pos	= character->GetPosition() + character->GetTravelDistance();
		aqua::CVector2 character_size	= aqua::CVector2(character->GetWidth(), character->GetHeight());
		BLOCK_DIRECTION direction	=BLOCK_DIRECTION::DUMMY;

		if (Collision::AABB(block_pos,block_size,character_pos,character_size)
			&& block->GetSetFlg())
		{
			direction = block->GetDirection(character_pos, character_size, character->GetOverComeSize());
			switch (direction)
			{
			case BLOCK_DIRECTION::UP:
				block_pos= aqua::CVector2(block_pos.x, block_pos.y);
				break;
			case BLOCK_DIRECTION::DOWN:
				block_pos = aqua::CVector2(block_pos.x, block_pos.y + block_size.y);
				break;
			case BLOCK_DIRECTION::LEFT:
				block_pos = aqua::CVector2(block_pos.x, block_pos.y);
				break;
			case BLOCK_DIRECTION::RIGHT:
				block_pos = aqua::CVector2(block_pos.x + block_size.x, block_pos.y);
				break;
			default:
				break;
			}

			character->BlockHit(block_pos, direction);
			//キャラクターがブロックに当たったときの方向が横で、キャラクターがドリルを所持している場合はブロックを破壊する
			if ((direction == BLOCK_DIRECTION::RIGHT||direction == BLOCK_DIRECTION::LEFT||direction == BLOCK_DIRECTION::DOWN)&& character->GetCharacterHaveItemObject()==CHARACTER_HAVE_ITEM_OBJECT::DRILL)
			{
				block->Clash();
			}
		}
	}
}

void CBlockManager::ItemObjectBlockHitCheck(IItemObject*& item_object)
{
	for (auto it : m_ChildObjectList)
	{
		CBlock* block = (CBlock*)it;
		//アイテムオブジェクトの移動距離を考慮してブロックの位置を調整
		aqua::CVector2 block_pos = block->GetPosition();
		aqua::CVector2 block_size = block->GetSize();

		//ブロックとアイテムオブジェクトの当たり判定
		//アイテムオブジェクト側の位置に移動距離を加算して当たり判定を行う
		aqua::CVector2 item_pos = item_object->GetPosition();
		aqua::CVector2 item_size = aqua::CVector2(item_object->GetWidth(), item_object->GetHeight());
		BLOCK_DIRECTION direction = BLOCK_DIRECTION::DUMMY;

		if (Collision::AABB(block_pos, block_size, item_pos, item_size)
			&& block->GetSetFlg())
		{
			direction = block->GetDirection(item_pos, item_size, item_object->GetOverComeSize());
			switch (direction)
			{
			case BLOCK_DIRECTION::UP:
				block_pos = aqua::CVector2(block_pos.x, block_pos.y);
				break;
			case BLOCK_DIRECTION::DOWN:
				block_pos = aqua::CVector2(block_pos.x, block_pos.y + block_size.y);
				break;
			case BLOCK_DIRECTION::LEFT:
				block_pos = aqua::CVector2(block_pos.x, block_pos.y);
				break;
			case BLOCK_DIRECTION::RIGHT:
				block_pos = aqua::CVector2(block_pos.x + block_size.x, block_pos.y);
				break;
			default:
				break;
			}

			item_object->BlockHit(block_pos, direction);
		}
	}

}

void CBlockManager::GimmickBlockHitCheck(IStageGimmick*& stage_gimmick)
{
	for (auto it : m_ChildObjectList)
	{
		CBlock* block = (CBlock*)it;
		//アイテムオブジェクトの移動距離を考慮してブロックの位置を調整
		aqua::CVector2 block_pos = block->GetPosition();
		aqua::CVector2 block_size = block->GetSize();

		//ブロックとアイテムオブジェクトの当たり判定
		//アイテムオブジェクト側の位置に移動距離を加算して当たり判定を行う
		aqua::CVector2 gimmick_pos = stage_gimmick->GetPosition();
		aqua::CVector2 gimmick_size = stage_gimmick->GetSize();
		BLOCK_DIRECTION direction = BLOCK_DIRECTION::DUMMY;

		if (Collision::AABB(block_pos, block_size, gimmick_pos, gimmick_size)
			&& stage_gimmick->GetSetFlg())
		{
			direction = block->GetDirection(gimmick_pos, gimmick_size, stage_gimmick->GetOverComeSize());
			switch (direction)
			{
			case BLOCK_DIRECTION::UP:
				block_pos = aqua::CVector2(block_pos.x, block_pos.y);
				break;
			case BLOCK_DIRECTION::DOWN:
				block_pos = aqua::CVector2(block_pos.x, block_pos.y + block_size.y + 1);
				break;
			case BLOCK_DIRECTION::SIDE:
				if (gimmick_pos.x + gimmick_size.x / 2.0f < block_pos.x + block_size.x / 2.0f)
				{
					block_pos = aqua::CVector2(block_pos.x - gimmick_size.x, block_pos.y);
				}
				else
				{
					block_pos = aqua::CVector2(block_pos.x + block_size.x, block_pos.y);
				}
				break;
			default:
				break;
			}

			stage_gimmick->ObjectHit(block_pos, block_size);
		}
	}


}

void CBlockManager::StageGimmickBlockHitCheck()
{
	CStageGimmickManager* stage_gimmick_manager = (CStageGimmickManager*)aqua::FindGameObject("StageGimmickManager");
	if(!stage_gimmick_manager)
		return;
	//ブロックとギミックの当たり判定
	for (auto it : m_ChildObjectList)
	{
		CBlock* block = (CBlock*)it;
		if (block->GetSetFlg())
		{
			stage_gimmick_manager->ObjectHitCheck(block->GetPosition(), block->GetSize(), block->GetGameObjectId());
		}
	}

}



BLOCK_DIRECTION CBlockManager::ObjectHitCheck(const aqua::CVector2& position, const aqua::CVector2& size, const aqua::CVector2& overcome)const
{
	for (auto it : m_ChildObjectList)
	{
		CBlock* block = (CBlock*)it;
		//プレイヤーの移動距離を考慮してブロックの位置を調整
		aqua::CVector2 block_pos = block->GetPosition();
		aqua::CVector2 block_size = block->GetSize();

		//ブロックとプレイヤーの当たり判定
		//プレイヤー側の位置に移動距離を加算して当たり判定を行う
		BLOCK_DIRECTION direction = BLOCK_DIRECTION::DUMMY;

		if (Collision::AABB(block_pos, block_size, position, size)
			&& block->GetSetFlg())
		{
			direction = block->GetDirection(position, size,overcome);
			return direction;
		}
	}
	//当たり判定に接触していない場合はダミーを返す
	return BLOCK_DIRECTION::DUMMY;
}

aqua::CVector2 CBlockManager::GetBlockPosition(const aqua::CVector2& position, const aqua::CVector2& size, const aqua::CVector2& overcome)const
{
	for (auto it : m_ChildObjectList)
	{
		CBlock* block = (CBlock*)it;
		//プレイヤーの移動距離を考慮してブロックの位置を調整
		aqua::CVector2 block_pos = block->GetPosition();
		aqua::CVector2 block_size = block->GetSize();

		//ブロックとプレイヤーの当たり判定
		//プレイヤー側の位置に移動距離を加算して当たり判定を行う
		BLOCK_DIRECTION direction = BLOCK_DIRECTION::DUMMY;

		if (Collision::AABB(block_pos, block_size, position, size)
			&& block->GetSetFlg())
		{

			direction = block->GetDirection(position, size, overcome);
			switch (direction)
			{
			case BLOCK_DIRECTION::UP:
				block_pos = aqua::CVector2(block_pos.x, block_pos.y);
				break;
			case BLOCK_DIRECTION::DOWN:
				block_pos = aqua::CVector2(block_pos.x, block_pos.y + block_size.y);
				break;
			case BLOCK_DIRECTION::SIDE:
				if (position.x + size.x / 2.0f < block_pos.x + block_size.x / 2.0f)
				{
					block_pos = aqua::CVector2(block_pos.x - size.x, block_pos.y);
				}
				else
				{
					block_pos = aqua::CVector2(block_pos.x + block_size.x, block_pos.y);
				}
				break;
			default:
				break;
			}

			return block_pos;

		}
	}
	//当たり判定に接触していない場合はダミーを返す
	return { 0.0f, 0.0f };
}

void CBlockManager::SetBlocks()
{
	//アイテムオブジェクトの位置指定の処理
	CCharacterManager* character_manager = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
	if (!character_manager)
		return;
	//プレイヤーの移動距離を取得
	aqua::CVector2 player_travel_distance = character_manager->GetPlayerTravelDistance();

	//マウスの位置とクリックの状態を取得
	CMouseControl* mouse = (CMouseControl*)aqua::FindGameObject("MouseControl");
	if (!mouse)
		return;
	//マウスの位置を取得
	aqua::CVector2 cursor_pos = mouse->GetCursorPos();
	//左クリックが押されているかどうか
	bool push_key = mouse->Button(aqua::mouse::BUTTON_ID::LEFT);


	for (auto it : m_ChildObjectList)
	{
		CBlock* block = (CBlock*)it;
		//未配置のブロックをマウスで配置する
		if (!block->GetSetFlg())
		{
			block->Set(player_travel_distance, cursor_pos, push_key);
		}
	}

}

void CBlockManager::SaveData(const aqua::CVector2& position)
{
	m_BlockData[m_SaveNumber].position = position;
	m_SaveNumber++;
}

void CBlockManager::CreateSaveBlock()
{
	for (int i = 0;i < m_SaveNumber;i++)
	{
		Create(m_BlockData[i].position, true);
	}
	
}

void CBlockManager::DeleteSaveData()
{
	m_SaveNumber = 0;
}



