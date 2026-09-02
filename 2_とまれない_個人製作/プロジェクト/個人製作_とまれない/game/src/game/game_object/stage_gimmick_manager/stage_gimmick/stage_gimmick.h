#pragma once
#include "aqua.h"
#include"stage_gimmick_direction.h"
#include"..\stage_gimmick_id.h"
#include"..\..\game_object_id.h"
#include"..\..\..\sound_play_manager\sound_play_manager.h"
#include"..\..\..\score_manager\score_manager.h"

class IStageGimmick : public aqua::IGameObject
{
	public:
	IStageGimmick(aqua::IGameObject* parent, const std::string& name,const int damage, const aqua::CVector2& collsion_size, const aqua::CVector2& texture_size);
	~IStageGimmick(void) = default;
	 virtual void Initialize(const aqua::CVector2& position, const  bool set_flag);
	 void Update(void) override;
	 virtual void Draw(const aqua::CVector2& player_travel_distance) ;
	 void Finalize(void) override;
	 aqua::CVector2 GetOverComeSize()const;
	 bool GetSetFlg(void)const;
	 aqua::CVector2 GetPosition(void)const;
	 aqua::CVector2 GetSize(void)const;
	 STAGE_GIMMICK_DIRECTION_ID GetDirection(const aqua::CVector2& object_position, const aqua::CVector2& object_size)const;
	 STAGE_GIMMICK_ID GetStageGimmickId(void)const;
	 //プレイヤーとギミックに当たったときの処理
	virtual void PlayerHit(void);
	//ブロックとギミックに当たったときの処理
	virtual void ObjectHit(const aqua::CVector2& object_position, const aqua::CVector2& object_size);
	//ギミックの移動＆セット
    void Set(const aqua::CVector2& player_travel_distance, const aqua::CVector2& cursor_pos, const bool push_key);
protected:
	static const aqua::CVector2 m_overcome_size;
	aqua::CVector2 m_BlockSize;	//ブロックの大きさ
	aqua::CSprite m_Sprite;		//ギミックのスプライト
	aqua::CVector2 m_Position;	//ギミックの位置
	aqua::CVector2 m_Collsion_Size;		//ギミックの当たり判定サイズ
	aqua::CVector2 m_Texture_Size;		//ギミックの描画サイズ
	int m_Damage;	//ギミックのダメージ量
	bool m_Set;		//ギミックがセットされているかどうかセットしていたらtrueを返す
	STAGE_GIMMICK_ID m_Id;	//ギミックのID
};