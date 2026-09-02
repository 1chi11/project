#pragma once
#include "aqua.h"
#include"effect_id.h"

class CEffectManager
    : public aqua::IGameObject
{
public:
    CEffectManager(aqua::IGameObject* parent);
    ~CEffectManager(void) = default;
    void Draw(void)override;
	//エフェクトの生成
    void Create(EFFECT_ID id, const aqua::CVector2& position); 
	//エフェクトの削除
    void Delete();
	//時間の速度を設定
	void SetTimeSpeed(float speed);
};
