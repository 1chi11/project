#include"ui_manager.h"
#include"ui/life_point/life_point.h"
#include"ui/mouse_click/mouse_click.h"
#include"ui/ui.h"
const aqua::CVector2 CUiManager::m_ui_position[] = 
{
	aqua::CVector2(0.0f,120.0f),	//LIFE_POINT
	aqua::CVector2(0.0f,0.0f)		//MOUSE_CLICK
};
CUiManager::CUiManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "UiManager")
{
}

void CUiManager::Initialize(void)
{
	CLifePoint* lp = aqua::CreateGameObject<CLifePoint>(this);
	if (lp)
		lp->Initialize(m_ui_position[LIFE_POINT]);

	CMouseClick* mc = aqua::CreateGameObject<CMouseClick>(this);
	if (mc)
		mc->Initialize(m_ui_position[MOUSE_CLICK]);

}
