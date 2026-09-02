#pragma once
#include "aqua.h"

class CTimeSpeed :public aqua::IGameObject
{
public:
	CTimeSpeed(aqua::IGameObject* parent);
	~CTimeSpeed() = default;
	void Update(void)override;
	void SwitchTimeSpeed(void);		//ŠÔ‚Ì‘¬‚³‚ğØ‚è‘Ö‚¦‚é
	void DefaultTimeSpeed(void);	//ŠÔ‚Ì‘¬‚³‚ğ‰Šú‰»
	void SlowTimeSpeed(void);		//ŠÔ‚Ì‘¬‚³‚ğ’x‚­‚·‚é
	float GetTimeSpeed(void)const;
private:
	static const float m_default_time_speed;	//ŠÔ‚Ì‘¬‚³‚Ì‰Šú’l
	static const float m_slow_time_speed;		//ŠÔ‚Ì‘¬‚³‚Ì’x‚­‚·‚é’l
	float m_TimeSpeed;							//ŠÔ‚Ì‘¬‚³
};