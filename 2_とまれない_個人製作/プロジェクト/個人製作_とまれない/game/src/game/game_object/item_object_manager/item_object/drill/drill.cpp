#pragma once
#include "drill.h"
const float CDrill::m_drill_time = 5.0f;
const float CDrill::m_width = 68.0f;
const float CDrill::m_height = 28.0f;

CDrill::CDrill(aqua::IGameObject* parent)
	:IItemObject(parent, "Drill",m_width,m_height)
{
}

void CDrill::Initialize(const aqua::CVector2& position, const bool set_flag)
{
	m_Position = position;
	m_Set = set_flag;
	m_Sprite.Create("data\\drill.png");
	m_Sprite.position = m_Position;
	m_GameObjectId = GAME_OBJECT_ID::DRILL;
	m_TextureSize = aqua::CVector2(m_Sprite.GetTextureWidth(), m_Sprite.GetTextureHeight());

}

void CDrill::Hit(ICharacter*& character)
{
	character->PickUpItemObject(CHARACTER_HAVE_ITEM_OBJECT::DRILL, m_drill_time);
	DeleteObject();
}
