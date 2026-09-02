#include "ui.h"

IUi::IUi(aqua::IGameObject* parent, const std::string& name)
	:aqua::IGameObject(parent, "Ui")
{
}

void IUi::Initialize(aqua::CVector2 position)
{
}

void IUi::Update()
{
}

void IUi::Draw()
{
	m_Sprite.Draw();
}

void IUi::Finalize()
{
	m_Sprite.Delete();
}
