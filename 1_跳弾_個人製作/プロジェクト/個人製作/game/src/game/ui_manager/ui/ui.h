#pragma once
#include"aqua.h"

class IUi 
	:public aqua::IGameObject
{
public:
	IUi(aqua::IGameObject* parent, const std::string& name);
	~IUi() = default;
	virtual void Initialize(aqua::CVector2 position) ;
	void Update()override;
	 void Draw()override;
	 void Finalize()override ;
protected:
	aqua::CSprite m_Sprite;
};