#include "item_object_manager.h"
#include"item_object/item_object.h"
#include"item_object\trampoline\trampoline.h"
#include"item_object\drill\drill.h"
#include"item_object\umbrella\umbrella.h"
#include"..\character_manager\character_manager.h"
#include"..\stage_gimmick_manager\stage_gimmick_manager.h"
#include"..\..\mouse\mouse.h"
#include"..\..\collision\collision.h"
CItemObjectManager::CItemObjectManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent,"ItemObjectManager")
{
}


void CItemObjectManager::Update(void)
{
	ItemObjectSet();
	StageGimmickItemObjectCheckHit();
	BlockItemObjectCheckHit();
	IGameObject::Update();
}

void CItemObjectManager::Draw(void)
{
	CCharacterManager* character_manager = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
	if (!character_manager)
		return;
	aqua::CVector2 player_travel_distance = character_manager->GetPlayerTravelDistance();
	for (auto it : m_ChildObjectList)
	{
		IItemObject* item_object = (IItemObject*)it;
		if (item_object->GetGameObjectState() != aqua::GAME_OBJECT_STATE::DEAD)
		item_object->Draw(player_travel_distance);
	}
}

void CItemObjectManager::Create(const GAME_OBJECT_ID id, const aqua::CVector2& position, const bool set_flag)
{
    //アイテムオブジェクトの生成
    IItemObject* item_object = nullptr;
    switch (id)
    {
    case GAME_OBJECT_ID::TRAMPOLINE:    item_object = aqua::CreateGameObject<CTrampoline>(this);
        break;
    case GAME_OBJECT_ID::UMBRELLA:   item_object = aqua::CreateGameObject<CUmbrella>(this);
        break;
	case GAME_OBJECT_ID::DRILL:   item_object = aqua::CreateGameObject<CDrill>(this);
		break;
    }
    if (item_object)
        item_object->Initialize(position, set_flag);
}

void CItemObjectManager::Delete(void)
{
	for (auto it : m_ChildObjectList)
	{
		IItemObject* item_object = (IItemObject*)it;
		item_object->Finalize();
	}
}

GAME_OBJECT_ID CItemObjectManager::GetCharacterHitObjectCheck(const aqua::CVector2& position, const aqua::CVector2& size)const
{
	for (auto it : m_ChildObjectList)
	{
		//プレイヤーの移動距離を考慮してブロックの位置を調整
		IItemObject* item_object = (IItemObject*)it;
		aqua::CVector2 item_pos = item_object->GetPosition();
		aqua::CVector2 item_size = item_object->GetSize();

		//ブロックとプレイヤーの当たり判定
		ITEM_OBJECT_ID item_id = ITEM_OBJECT_ID::DUMMY;

		//プレイヤーとアイテムオブジェクトの当たり判定
		if (Collision::AABB(item_pos,item_size,position,size)
			&& item_object->GetSetFlg())
		{
			return item_object->GetGameObjectId();
		}
	}
	return GAME_OBJECT_ID::DUMMY;

}

void CItemObjectManager::CharacterItemObjectCheckHit(ICharacter*& character)
{
	for (auto it : m_ChildObjectList)
	{
		//プレイヤーの移動距離を考慮してブロックの位置を調整
		IItemObject* item_object = (IItemObject*)it;
		aqua::CVector2 item_pos = item_object->GetPosition();
		aqua::CVector2 item_size = item_object->GetSize();

		//ブロックとプレイヤーの当たり判定
		//プレイヤー側の位置に移動距離を加算して当たり判定を行う
		aqua::CVector2 player_pos = character->GetPosition() + character->GetTravelDistance();
		aqua::CVector2 player_size = aqua::CVector2(character->GetWidth(), character->GetHeight());
		float player_width = character->GetWidth();
		float player_height = character->GetHeight();
		ITEM_OBJECT_ID item_id = ITEM_OBJECT_ID::DUMMY;
		
		//プレイヤーとアイテムオブジェクトの当たり判定
		if (Collision::AABB(item_pos, item_size, player_pos, player_size)
			&&item_object->GetSetFlg())
		{
			item_object->Hit(character);
		}
	}
}

void CItemObjectManager::BlockItemObjectCheckHit(void)
{
	CBlockManager* block_manager = (CBlockManager*)aqua::FindGameObject("BlockManager");
	if (!block_manager)
		return;
	for (auto it : m_ChildObjectList)
	{
		IItemObject* item_object = (IItemObject*)it;
		if (item_object->GetSetFlg())
		{
			block_manager->ItemObjectBlockHitCheck(item_object);
		}
	}
}

void CItemObjectManager::StageGimmickItemObjectCheckHit(void)
{
	CStageGimmickManager* stage_gimmick_manager = (CStageGimmickManager*)aqua::FindGameObject("StageGimmickManager");
	if (!stage_gimmick_manager)
		return;
	for (auto it : m_ChildObjectList)
	{
		IItemObject* item_object = (IItemObject*)it;
		if (item_object->GetSetFlg())
		{
			stage_gimmick_manager->ObjectHitCheck(item_object->GetPosition(), aqua::CVector2(item_object->GetWidth(), item_object->GetHeight()), item_object->GetGameObjectId());
		}
	}
}

void CItemObjectManager::ItemObjectSet(void)
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
		IItemObject* item_object = (IItemObject*)it;
		//アイテムオブジェクトがセットされていないときにマウスの位置にアイテムオブジェクトをセットする
		if (!item_object->GetSetFlg())
		{
			item_object->Set(player_travel_distance, cursor_pos, push_key);
		}
	}
}

void CItemObjectManager::SetTimeSpeed(const float rate)
{
	for (auto it : m_ChildObjectList)
	{
		IItemObject* item_object = (IItemObject*)it;
		item_object->SetTimeSpeed(rate);
	}
}
