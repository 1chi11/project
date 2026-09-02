#pragma once
#include"aqua.h"
#include"character\character.h"
#include"character\player\player.h"
#include"character_id.h"
#include"..\game_object_id.h"

class CPlayer;

class CCharacterManager : public aqua::IGameObject
{
	public:
	CCharacterManager(aqua::IGameObject* parent);
	~CCharacterManager(void) = default;
	void Initialize(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void)override;

	//キャラクターの生成
	void Create(const CHARACTER_ID id,const aqua::CVector2& position, const aqua::CVector2& travel_distance);
	//キャラクターの消去
	void Delete(void);
	//アイテムの生成
	void CreateItemObject(const GAME_OBJECT_ID id, const aqua::CVector2& position);
	//キャラクターとブロックの当たり判定
	void CharacterBlockHitCheck(void);
	//キャラクターとギミックの当たり判定
	void CharacterGimmickHitCheck(void);
	//キャラクターとアイテムオブジェクトの当たり判定
	void CharacterItemObjectCheckHit(void);
	//キャラクター同士の当たり判定
	void CharacterHitCheck(void);
	//プレイヤーのオブジェクトを取得
	CPlayer* GetPlayer(void)const;
	//プレイヤーの移動距離を取得
	aqua::CVector2 GetPlayerTravelDistance(void)const;
	//データを保存
	void Save(void);
	//時間の速さを変える
	void SetTimeSpeed(const float rate);
private:
	static const int m_player_have_item_num ;	//プレイヤーが持てるアイテムの数
	CPlayer* m_Player;							//プレイヤーのオブジェクト
	aqua::CVector2 m_PlayerTravelDistance;		//プレイヤーの移動距離

	struct PlayerData
	{
		aqua::CVector2 position;		//プレイヤーの位置
		aqua::CVector2 travel_distance;	//プレイヤーの移動距離
		int have_item[static_cast<int>(GAME_OBJECT_ID::MAX)];	//プレイヤーが持っているアイテムの種類
		float life_point;				//プレイヤーの体力
		float run_speed;				//プレイヤーの走る速度

	};
	PlayerData m_PlayerData;	//プレイヤーのデータ

	struct PlayerSaveData
	{
		aqua::CVector2 position;		//プレイヤーの位置
		aqua::CVector2 travel_distance;	//プレイヤーの移動距離
		int have_item[static_cast<int>(GAME_OBJECT_ID::MAX)];				//プレイヤーが持っているアイテムの種類
		float life_point;				//プレイヤーの体力
		float run_speed;				//プレイヤーの走る速度

	};
	PlayerSaveData m_PlayerSaveData;	//プレイヤーのデータ

};
