#pragma once
#include"aqua.h"
#include"..\..\time_speed\time_speed.h"

class IEffect
	: public aqua::IGameObject
{
public:
	IEffect(aqua::IGameObject* parent, const std::string& object_name);
	virtual void    Initialize(const aqua::CVector2& position);
	virtual void    Update()override;
	virtual void	Draw(const aqua::CVector2& travel_postion);
	virtual void	Finalize()override;
	void SetTimeSpeed(float time_speed);
protected:
	aqua::CSprite m_Sprite;	//エフェクトのスプライト
	aqua::CVector2 m_Position;
	float m_TimeSpeed;	//時間の進む速度
};