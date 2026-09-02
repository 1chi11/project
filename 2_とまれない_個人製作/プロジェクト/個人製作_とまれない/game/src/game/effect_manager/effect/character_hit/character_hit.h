#pragma once
#include"..\effect.h"

class CCharacterHit
	:public IEffect
{
public:
	CCharacterHit(IGameObject* parent);
	~CCharacterHit(void) = default;
	void Initialize(const aqua::CVector2& position)override;
	void Update(void)override;
	void Draw(const aqua::CVector2& travel_postion)override;
	void Finalize(void)override;
private:
	static const aqua::CVector2 m_scale_velocity;
	aqua::CVector2 m_Scale;
};