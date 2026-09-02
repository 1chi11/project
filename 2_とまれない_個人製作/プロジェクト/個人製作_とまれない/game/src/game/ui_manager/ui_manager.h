#pragma once
#include"aqua.h"
#include"ui_id.h"

class CUiManager :public aqua::IGameObject
{
public:
	CUiManager(aqua::IGameObject* parent);
	~CUiManager() = default;
	void Initialize(void);
private:
	enum UI_ID
	{
		LIFE_POINT,
		MOUSE_CLICK
	};
	static const aqua::CVector2 m_ui_position[];	
};