#include "umbrella.h"
#pragma once
const float CUmbrella::m_width = 94.0f;
const float CUmbrella::m_height = 103.0f;

CUmbrella::CUmbrella(aqua::IGameObject* parent)
	:IItemObject(parent, "Umbrella",m_width,m_height)
{
}

void CUmbrella::Initialize(const aqua::CVector2& position, const bool set_flag)
{
	m_Set = set_flag;
	m_Position = position;
	m_Sprite.Create("data\\umbrella.png");
	m_Sprite.position = m_Position;
	m_GameObjectId = GAME_OBJECT_ID::UMBRELLA;
	m_TextureSize = aqua::CVector2(m_Sprite.GetTextureWidth(), m_Sprite.GetTextureHeight());

}

void CUmbrella::Update(void)
{
	IGameObject::Update();
}

void CUmbrella::Hit(ICharacter*& character)
{
	//Finalize();
}
