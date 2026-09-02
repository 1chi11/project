#pragma once
#include"aqua.h"

class IEffect
	: public aqua::IGameObject
{
public:
	IEffect(aqua::IGameObject* parent, const std::string& object_name);
	virtual void    Initialize(const aqua::CVector2& position);
	void Finalize()override;
private:
protected:
	aqua::CSprite m_Sprite;	//エフェクトのスプライト
};