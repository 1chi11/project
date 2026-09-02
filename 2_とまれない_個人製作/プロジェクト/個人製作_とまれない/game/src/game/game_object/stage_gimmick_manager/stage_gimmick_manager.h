#pragma once
#include "aqua.h"
#include "stage_gimmick_id.h"
#include"..\item_object_manager\item_object_id.h"
#include"..\game_object_id.h"

class CStageGimmickManager : public aqua::IGameObject
{
public:
	CStageGimmickManager(aqua::IGameObject* parent);
	~CStageGimmickManager(void) = default;
	void Update(void) override;
	void Draw(void) override;
	//ギミックの生成
	void Create(const STAGE_GIMMICK_ID id, const aqua::CVector2& position,const bool set_flag);
	//ギミックの消去
	void Delete(void);
	//ステージギミックの位置指定の処理
	void SetGimmicks(void);
	//ステージギミックとアイテムオブジェクトの当たり判定
	STAGE_GIMMICK_ID ObjectHitCheck(const aqua::CVector2& position, const  aqua::CVector2& size,const GAME_OBJECT_ID id)const;
};