#include "character_manager.h"
#include"character/ground_enemy/ground_enemy.h"
#include"..\..\button_manager\button_manager.h"
#include"..\..\sound_play_manager\sound_play_manager.h"
#include"..\..\collision\collision.h"
const int CCharacterManager::m_player_have_item_num = 5;

CCharacterManager::CCharacterManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "CharacterManager")
	, m_Player(nullptr)
	, m_PlayerTravelDistance(0.0f, 0.0f)
	, m_PlayerData({ {0.0f, 0.0f}, {0.0f, 0.0f}, {}, 0.0f, 0.0f })
	, m_PlayerSaveData({ {0.0f, 0.0f}, {0.0f, 0.0f}, {}, 0.0f, 0.0f })
{
}


void CCharacterManager::Initialize(void)
{
	//アイテムオブジェクトの所持数初期化
	for (int i = 0; i < static_cast<int>(GAME_OBJECT_ID::MAX); ++i)
		m_PlayerData.have_item[i] = m_player_have_item_num;
	for (int i = 0; i < static_cast<int>(GAME_OBJECT_ID::MAX); ++i)
		m_PlayerSaveData.have_item[i] = m_player_have_item_num;

	//アイテムの所持数描画
	CButtonManager* button_manager = (CButtonManager*)aqua::FindGameObject("ButtonManager");
	if (button_manager)
	{
		for (int i = static_cast<int>(GAME_OBJECT_ID::DUMMY); i < static_cast<int>(GAME_OBJECT_ID::MAX); ++i)
			button_manager->SetButtonText(static_cast<GAME_OBJECT_ID>(i), m_PlayerData.have_item[i]);
	}

	IGameObject::Initialize();

}

void CCharacterManager::Update(void)
{
	//キャラクターとブロックの当たり判定
	CharacterBlockHitCheck();
	//キャラクターとギミックの当たり判定
	CharacterGimmickHitCheck();
	//キャラクターとアイテムオブジェクトの当たり判定
	CharacterItemObjectCheckHit();
	//キャラクター同士の当たり判定
	CharacterHitCheck();


	if(m_Player)
	if (m_Player->GetLifePoint() <= 0)
	{
		//壊れたブロックの再生
		CBlockManager* block_manager = (CBlockManager*)aqua::FindGameObject("BlockManager");
		if (block_manager)
			block_manager->CreateSaveBlock();

		Create(CHARACTER_ID::PLAYER, m_PlayerSaveData.position, m_PlayerSaveData.travel_distance);
	}

	//アイテムの所持数描画
	CButtonManager* button_manager = (CButtonManager*)aqua::FindGameObject("ButtonManager");
	if (button_manager)
	{
		for (int i = static_cast<int>(GAME_OBJECT_ID::DUMMY); i < static_cast<int>(GAME_OBJECT_ID::MAX); ++i)
			button_manager->SetButtonText(static_cast<GAME_OBJECT_ID>(i), m_PlayerData.have_item[i]);
	}

	IGameObject::Update();

}

void CCharacterManager::Draw(void)
{
	CCharacterManager* character_manager = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
	if (!character_manager)
		return;
	aqua::CVector2 player_travel_distance = character_manager->GetPlayerTravelDistance();

	for (auto it : m_ChildObjectList)
	{
		ICharacter* character = (ICharacter*)it;
		if (character->GetGameObjectState() != aqua::GAME_OBJECT_STATE::DEAD)
		character->Draw(player_travel_distance);
	}
	IGameObject::Draw();
}

void CCharacterManager::Finalize(void)
{
	m_Player=nullptr;
	IGameObject::Finalize();
}

void CCharacterManager::Create(const CHARACTER_ID id, const aqua::CVector2& position, const aqua::CVector2& travel_distance)
{
	aqua::CVector2 travel = travel_distance;
	//キャラクターの生成
	ICharacter* character = nullptr;
	switch (id)
	{
	case CHARACTER_ID::PLAYER:
	{
		character = aqua::CreateGameObject<CPlayer>(this);
		m_Player= (CPlayer*)character;
		travel = m_PlayerSaveData.travel_distance;
		for (int i = 0; i < static_cast<int>(GAME_OBJECT_ID::MAX); ++i)
			m_PlayerData.have_item[i]=m_PlayerSaveData.have_item[i];

		break;
	}
	case CHARACTER_ID::ENEMY:
	{
		character = aqua::CreateGameObject<CGroundEnemy>(this);
		break;
	}
	}
	if (character)
		character->Initialize(position, travel);
}

void CCharacterManager::Delete()
{
	m_PlayerSaveData = { {0.0f, 0.0f}, {0.0f, 0.0f}, {}, 0.0f, 0.0f };

	for (auto it : m_ChildObjectList)
	{
		ICharacter* character = (ICharacter*)it;
		character->Finalize();
	}
	m_Player = nullptr;
}

void CCharacterManager::CreateItemObject(const GAME_OBJECT_ID id, const aqua::CVector2& position)
{
	CItemObjectManager* item_object_manager = (CItemObjectManager*)aqua::FindGameObject("ItemObjectManager");
	if (!item_object_manager)
		return;
	CButtonManager* button_manager = (CButtonManager*)aqua::FindGameObject("ButtonManager");
	if (!button_manager)
		return;
	//プレイヤーがアイテムの在庫確認
	if (m_PlayerData.have_item[static_cast<int>(id)] > 0)
	{
		//アイテムオブジェクトの生成
		m_PlayerData.have_item[static_cast<int>(id)]--;
		button_manager->SetButtonText(id, m_PlayerData.have_item[static_cast<int>(id)]);
		item_object_manager->Create(id, position, false);
		CSoundPlayManager* sm = (CSoundPlayManager*)aqua::FindGameObject("SoundPlayManager");
		if (sm)
			sm->Play(SOUND_ID::CREATE);
	}
}

void CCharacterManager::CharacterBlockHitCheck(void)
{
	CBlockManager* block_manager = (CBlockManager*)aqua::FindGameObject("BlockManager");
	if (!block_manager)
		return;
	
		for (auto it : m_ChildObjectList)
		{
			ICharacter* character = (ICharacter*)it;
			block_manager->CharacterBlockHitCheck(character);
		}
}

void CCharacterManager::CharacterGimmickHitCheck(void)
{
	CStageGimmickManager* stage_gimmick_manager = (CStageGimmickManager*)aqua::FindGameObject("StageGimmickManager");
	if (!stage_gimmick_manager)
		return;
	for (auto it : m_ChildObjectList)
	{
		ICharacter* character = (ICharacter*)it;
		if (!character||character->GetGameObjectState()==aqua::GAME_OBJECT_STATE::DEAD
			||!m_Player|| m_Player->GetGameObjectState() == aqua::GAME_OBJECT_STATE::DEAD)
			return;
		aqua::CVector2 character_pos = character->GetPosition() + character->GetTravelDistance();
		switch (stage_gimmick_manager->ObjectHitCheck(character_pos, character->GetSize(), character->GetGameObjectId()))
		{
		case STAGE_GIMMICK_ID::FIRE:
			character->Damage(1);break;
		case STAGE_GIMMICK_ID::SPIKE:
			character->Damage(2);break;
		case STAGE_GIMMICK_ID::CHECK_POINT:
			Save();break;
		case STAGE_GIMMICK_ID::GOAL:
			m_Player->Goal();break;
			if (!m_Player)
				return;

		}
	}
}

void CCharacterManager::CharacterItemObjectCheckHit(void)
{
	CItemObjectManager* item_object_manager = (CItemObjectManager*)aqua::FindGameObject("ItemObjectManager");
	if (!item_object_manager)
		return;
	for (auto it : m_ChildObjectList)
	{
		ICharacter* character = (ICharacter*)it;
		item_object_manager->CharacterItemObjectCheckHit(character);
	}
}

void CCharacterManager::CharacterHitCheck(void)
{
	if (!m_Player)
		return;
	for (auto it : m_ChildObjectList)
	{
		ICharacter* character = (ICharacter*)it;
		aqua::CVector2 character_pos = character->GetPosition();
		aqua::CVector2 character_size = character->GetSize();

		//プレイヤー側の位置に移動距離を加算して当たり判定を行う
		aqua::CVector2 player_pos = m_Player->GetPosition() + m_Player->GetTravelDistance();
		aqua::CVector2 player_size = m_Player->GetSize();
		float width = player_size.x;
		float height = player_size.y;

		//プレイヤー同士の当たり判定は行わない
		if (character->GetGameObjectId() == GAME_OBJECT_ID::PLAYER&&m_Player)
		{
			m_PlayerTravelDistance = m_Player->GetTravelDistance();
			continue;

		}

		//プレイヤーとキャラクターの当たり判定
		if (Collision::AABB(character_pos, character_size, player_pos, player_size))
		{
			//プレイヤーの接触方向を取得
			switch (m_Player->GetHitDirection(character_pos, character_size))
			{
				case CHARACTER_HIT_DIRECTION::UP:
					character->Damage(m_Player->GetDamage());
					m_Player->Jump(character->GetBouncePower());
					break;
				case CHARACTER_HIT_DIRECTION::DOWN:
					m_Player->Damage(character->GetDamage());
					break;
				case CHARACTER_HIT_DIRECTION::SIDE:
					m_Player->Damage(character->GetDamage());
					break;
				default:
					break;
			};
		}
	}
}

CPlayer* CCharacterManager::GetPlayer(void)const
{
	if(!m_Player)
		return nullptr;
	return m_Player;
}

aqua::CVector2 CCharacterManager::GetPlayerTravelDistance(void)const
{
	return m_PlayerTravelDistance;
}

void CCharacterManager::Save(void)
{
	CBlockManager* block_manager = (CBlockManager*)aqua::FindGameObject("BlockManager");
	if (block_manager)
		block_manager->DeleteSaveData();
	m_PlayerSaveData = { m_Player->GetPosition(),m_Player->GetTravelDistance(), {}, m_Player->GetLifePoint(), m_Player->GetRunSpeed() };

	for (int i = 0; i < static_cast<int>(GAME_OBJECT_ID::MAX); ++i)
		m_PlayerSaveData.have_item[i] = m_PlayerData.have_item[i];
}


void CCharacterManager::SetTimeSpeed(const float rate)
{
	for (auto it : m_ChildObjectList)
	{
		ICharacter* character = (ICharacter*)it;
		character->SetTimeSpeed(rate);
	}
}


