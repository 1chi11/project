#pragma once
#include "aqua.h"
#include"..\item_object_id.h"
#include"..\..\game_object_id.h"
#include"..\..\stage_gimmick_manager\stage_gimmick_manager.h"
#include"..\..\character_manager\character_manager.h"
#include"..\..\..\score_manager\score_manager.h"

class ICharacter;

class IItemObject : public aqua::IGameObject
{
public:
	IItemObject(aqua::IGameObject* parent, const std::string& name, const float width, const float height);
	virtual ~IItemObject(void) = default;
	virtual void Initialize(const aqua::CVector2& position, const bool set_flag);
	virtual void Update(void) override;
	virtual void Draw(const aqua::CVector2& player_travel_distance);
	virtual void Finalize(void)override;
	aqua::CVector2 GetPosition(void)const;
	aqua::CVector2 GetSize(void)const;
	aqua::CVector2 GetOverComeSize(void)const;
	float GetWidth(void)const;
	float GetHeight(void)const;
	bool GetSetFlg(void)const;
	GAME_OBJECT_ID GetGameObjectId(void)const;

	//時間の入力
	void SetTimeSpeed(const float rate);
	//プレイヤーとアイテムオブジェクトが当たったときの処理
	virtual void Hit(ICharacter*& character);
	//アイテムオブジェクトがブロックに当たったときの処理
	void BlockHit(const aqua::CVector2& hit_position, const BLOCK_DIRECTION direction);
	//アイテムオブジェクトの重力の処理
	void Gravity(void);
	//アイテムオブジェクトの位置指定の処理
	void Set(const aqua::CVector2& player_travel_distance, const aqua::CVector2& mouse_pos, const bool push_key);


protected:
	static const aqua::CVector2 m_overcome_size;//アイテムの超えられる段差の高さ
	static const float	m_gravity;		//アイテムオブジェクトの重力
	static const int m_score;			//アイテムオブジェクトのスコア

	aqua::CSprite	m_Sprite;		//アイテムのスプライト
	aqua::CVector2	m_Position;		//アイテムの位置
	aqua::CVector2 m_Velocity;		//アイテムの速度
	aqua::CVector2 m_TextureSize;	//テクスチャの大きさ
	aqua::CVector2 m_Size;			//アイテムの大きさ
	float			m_Width;		//アイテムの幅
	float			m_Height;		//アイテムの高さ
	float			m_YVelocity;	//アイテムのY軸の速度
	float			m_TimeSpeed;

	bool			m_LandingFlg;	//アイテムが地面にいるかどうか
	bool			m_Set;			//アイテムがセットされているかどうかセットしていたらtrueを返す

	GAME_OBJECT_ID	m_GameObjectId;			//アイテムオブジェクトのID
};