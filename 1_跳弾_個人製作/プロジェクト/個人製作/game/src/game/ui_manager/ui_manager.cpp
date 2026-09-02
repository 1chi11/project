#include"ui_manager.h"
#include"ui/ui.h"
#include"ui/bounce_count/bounce_count.h"

CUiManager::CUiManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "UiManager")
{
}

void CUiManager::Create(aqua::CVector2 position, UI_ID id)
{
	//UIÇÃê∂ê¨
	IUi* ui = nullptr;
	switch (id)
	{
	case UI_ID::BOUNCE_COUNT:
		ui= aqua::CreateGameObject<CBounceCount>(this);
		break;
	default:
		break;
	}

	if (ui)
	ui->Initialize(position);
}
