#pragma once
#include "aqua.h"
#include"button\button.h"
#include"..\game_object\game_object_id.h"

class CButtonManager : public aqua::IGameObject
{
public:
	CButtonManager(aqua::IGameObject* parent);
	~CButtonManager(void) = default;
	void Create(ClickEvent click_event, const aqua::CVector2& position, const std::string& name, GAME_OBJECT_ID id);
	void SetButtonText(GAME_OBJECT_ID id, int count);
	void Delete();
private:
};