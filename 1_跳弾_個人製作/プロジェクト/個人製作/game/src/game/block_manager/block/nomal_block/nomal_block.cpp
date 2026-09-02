#include "nomal_block.h"
#include "..\..\..\bullet_manager\bullet_manager.h"
#include"..\..\..\sound_manager\sound_manager.h"

CNomalBlock::CNomalBlock(aqua::IGameObject* parent)
	:IBlock(parent, "NomalBlock")
{
}

void CNomalBlock::Initialize(aqua::CVector2 position1, aqua::CVector2 position2, float speed)
{
	m_CenterPosition = aqua::CVector2(m_size / 2.0f, m_size / 2.0f);
	m_Sprite.Create("data\\object.png");
	m_Sprite.anchor = aqua::CVector2(m_size / 2.0f, m_size / 2.0f);
	//固定オブジェクトにする(色変更)
	m_Sprite.color = 0xff00ff00;
	m_Sprite.rotation = 0.0f;
	m_Vertices[0] = aqua::CVector2(0.0f, 0.0f);
	m_Vertices[1] = aqua::CVector2(m_size, 0.0f);
	m_Vertices[2] = aqua::CVector2(m_size, m_size);
	m_Vertices[3] = aqua::CVector2(0.0f, m_size);
	m_Position = position1;
	m_FELIX_BLOCK = FELIX_BLOCK_ID::NOMAL_BLOCK;
	m_SetSw = true;
}


