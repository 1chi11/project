#pragma once
#include"aqua.h"
#include"ui_id.h"

class CUiManager :public aqua::IGameObject
{
public:
	CUiManager(aqua::IGameObject* parent);
	~CUiManager() = default;
	void Create(aqua::CVector2 position, UI_ID id);
};