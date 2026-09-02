#pragma once
#include"aqua.h"

class IUi 
	:public aqua::IGameObject
{
public:
	IUi(aqua::IGameObject* parent, const std::string& name);
	~IUi() = default;
	virtual void Initialize(aqua::CVector2 position) ;
	virtual void Update(void)override;
	virtual void Draw(void)override;
	virtual void Finalize(void)override;
protected:
	aqua::CSprite m_Sprite;
};