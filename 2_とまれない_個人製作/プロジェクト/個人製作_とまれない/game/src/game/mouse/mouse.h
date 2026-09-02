#pragma once
#include "aqua.h"

class CMouseControl : public aqua::IGameObject
{
public:
	CMouseControl(aqua::IGameObject* parent);
	~CMouseControl(void) = default;
	void Update(void)override;
	aqua::CVector2 GetCursorPos(void);
	bool Button(aqua::mouse::BUTTON_ID button_id);
	bool Trigger(aqua::mouse::BUTTON_ID button_id);
};