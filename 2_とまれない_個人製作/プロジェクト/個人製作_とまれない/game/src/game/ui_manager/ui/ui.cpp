#include "ui.h"

IUi::IUi(aqua::IGameObject* parent, const std::string& name)
	:aqua::IGameObject(parent, name)
{
}

void IUi::Initialize(aqua::CVector2 position)
{
}

void IUi::Update(void)
{
}

void IUi::Draw(void)
{
	m_Sprite.Draw();
}

void IUi::Finalize(void)
{
	IGameObject::Finalize();
}

