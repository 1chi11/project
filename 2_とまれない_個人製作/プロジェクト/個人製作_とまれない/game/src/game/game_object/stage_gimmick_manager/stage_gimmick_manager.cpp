#include "stage_gimmick_manager.h"
#include "stage_gimmick\stage_gimmick.h"
#include"stage_gimmick/fire_gimmick/fire_gimmick.h"
#include"stage_gimmick/spike_gimmick/spike_gimmick.h"
#include"stage_gimmick/goal_gimmick/goal_gimmick.h"
#include"stage_gimmick/check_point/check_point.h"
#include"..\character_manager\character_manager.h"
#include"..\..\mouse\mouse.h"
#include"..\..\collision\collision.h"

CStageGimmickManager::CStageGimmickManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "StageGimmickManager")
{
}

void CStageGimmickManager::Update(void)
{
	SetGimmicks();
	IGameObject::Update();
}

void CStageGimmickManager::Draw(void)
{
	CCharacterManager* character_manager = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
	if (!character_manager)
		return;
	aqua::CVector2 player_travel_distance = character_manager->GetPlayerTravelDistance();
	for (auto it : m_ChildObjectList)
	{
		IStageGimmick* stage_gimmick = (IStageGimmick*)it;
		if (stage_gimmick->GetGameObjectState() != aqua::GAME_OBJECT_STATE::DEAD)
		stage_gimmick->Draw(player_travel_distance);
	}
}

void CStageGimmickManager::Create(const STAGE_GIMMICK_ID id, const aqua::CVector2& position,const bool set_flag)
{
	IStageGimmick* stage_gimmick = nullptr;
	switch (id)
	{
		case STAGE_GIMMICK_ID::FIRE: 
			stage_gimmick = aqua::CreateGameObject<CFireGimmick>(this);
			break;
		case STAGE_GIMMICK_ID::SPIKE:
			stage_gimmick = aqua::CreateGameObject<CSpikeGimmick>(this);
			break;
		case STAGE_GIMMICK_ID::GOAL:
			stage_gimmick = aqua::CreateGameObject<CGoalGimmick>(this);
			break;
		case STAGE_GIMMICK_ID::CHECK_POINT:
			stage_gimmick = aqua::CreateGameObject<CCheckPoint>(this);
			break;
	}
	
	if (stage_gimmick)
		stage_gimmick->Initialize(position, set_flag);
}

void CStageGimmickManager::Delete(void)
{
	for (auto it : m_ChildObjectList)
	{
		IStageGimmick* stage_gimmick = (IStageGimmick*)it;
		stage_gimmick->Finalize();
	}
}

void CStageGimmickManager::SetGimmicks(void)
{
	//アイテムオブジェクトの位置指定の処理
	CCharacterManager* character_manager = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
	if (!character_manager)
		return;
	//プレイヤーの移動距離を取得
	aqua::CVector2 player_travel_distance = character_manager->GetPlayerTravelDistance();

	//マウスの位置とクリックの状態を取得
	CMouseControl* mouse = (CMouseControl*)aqua::FindGameObject("MouseControlouse");
	if (!mouse)
		return;
	//マウスの位置を取得
	aqua::CVector2 cursor_pos = mouse->GetCursorPos();
	//左クリックが押されているかどうか
	bool push_key = mouse->Button(aqua::mouse::BUTTON_ID::LEFT);

	for (auto it : m_ChildObjectList)
	{
		IStageGimmick* stage_gimmick = (IStageGimmick*)it;
		//ギミックがセットされていないときにマウスの位置とクリックの状態をもとにギミックの位置指定の処理を行う
        if (!stage_gimmick->GetSetFlg())
		{
			stage_gimmick->Set(player_travel_distance, cursor_pos, push_key);
		}
	}
}

STAGE_GIMMICK_ID CStageGimmickManager::ObjectHitCheck(const aqua::CVector2& position, const aqua::CVector2& size, const GAME_OBJECT_ID id)const
{
	for (auto it : m_ChildObjectList)
	{
		IStageGimmick* stage_gimmick = (IStageGimmick*)it;
		//ギミックの位置と大きさをとる
		aqua::CVector2 stage_gimmick_pos = stage_gimmick->GetPosition();
		aqua::CVector2 stage_gimmick_size = stage_gimmick->GetSize();

		//ギミックとオブジェクトの当たり判定
		if (Collision::AABB(stage_gimmick_pos, stage_gimmick_size,position,size)
			&& stage_gimmick->GetSetFlg())
		{
			//当たったオブジェクトによって処理をかえる
			switch (id)
			{
			case GAME_OBJECT_ID::PLAYER:
				stage_gimmick->PlayerHit();
				break;
			case GAME_OBJECT_ID::BLOCK:
				stage_gimmick->ObjectHit(position, size);
				break;
			case GAME_OBJECT_ID::UMBRELLA :
				stage_gimmick->ObjectHit(position, size);
				break;
			case GAME_OBJECT_ID::STAGE_GIMMICK:
				break;
			default:
				break;
			}
			return stage_gimmick->GetStageGimmickId();
		}
	}
			return STAGE_GIMMICK_ID::DUMMY;

}

