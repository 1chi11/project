#include "effect.h"

IEffect::IEffect(aqua::IGameObject* parent, const std::string& object_name)
	:IGameObject(parent,"effect")
{
}

void IEffect::Initialize(const aqua::CVector2& position)
{
}

void IEffect::Finalize()
{
	m_Sprite.Delete();
	DeleteObject();
}
