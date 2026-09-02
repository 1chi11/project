#include"mouse.h"
#include"..\time_speed\time_speed.h"

CMouseControl::CMouseControl(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "MouseControl")
{
}

void CMouseControl::Update(void)
{
	//右クリックで時間が遅くなる
	if(Trigger(aqua::mouse::BUTTON_ID::RIGHT))
	{
		CTimeSpeed* time = (CTimeSpeed*)aqua::FindGameObject("TimeSpeed");
		if (!time)
			return;
		time->SwitchTimeSpeed();
	}
}

aqua::CVector2 CMouseControl::GetCursorPos(void)
{
	return aqua::CVector2((float)aqua::mouse::GetCursorPos().x, (float)aqua::mouse::GetCursorPos().y);
}

bool CMouseControl::Button(aqua::mouse::BUTTON_ID button_id)
{
	return aqua::mouse::Button(button_id);
}

bool CMouseControl::Trigger(aqua::mouse::BUTTON_ID button_id)
{
	return aqua::mouse::Trigger(button_id);
}
