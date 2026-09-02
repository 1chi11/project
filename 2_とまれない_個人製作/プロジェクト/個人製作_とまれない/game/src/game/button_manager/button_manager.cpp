#include "button_manager.h"

CButtonManager::CButtonManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "ButtonManager")
{
}


void CButtonManager::Create(ClickEvent click_event, const aqua::CVector2& position, const std::string& name, GAME_OBJECT_ID id)
{
	CButton* button = aqua::CreateGameObject<CButton>(this);
	if (!button)
		return;
		button->Initialize(click_event, position, name,id);
}

void CButtonManager::SetButtonText(GAME_OBJECT_ID id, int count)
{
	for (auto it : m_ChildObjectList)
	{
		CButton* button = (CButton*)it;
		if (button->GetButtonSetGameObjectId() == id&& button->GetButtonSetGameObjectId() != GAME_OBJECT_ID::DUMMY)
		{
			button->SetText(count);
			return;
		}
	}
}


void CButtonManager::Delete()
{
	for (auto it : m_ChildObjectList)
	{
		CButton* button = (CButton*)it;
		button->DeleteObject();
	}

}
