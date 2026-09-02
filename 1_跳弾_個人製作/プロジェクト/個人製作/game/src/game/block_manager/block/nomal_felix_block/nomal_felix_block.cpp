#include "nomal_felix_block.h"

CNomalFelixBlock::CNomalFelixBlock(aqua::IGameObject* parent)
	:IBlock(parent, "NomalFelixBlock")
{
}

void CNomalFelixBlock::Initialize(aqua::CVector2 position1, aqua::CVector2 position2, float speed)
{
	m_CenterPosition = aqua::CVector2(m_size / 2.0f, m_size / 2.0f);
	m_Sprite.Create("data\\object.png");
	m_Sprite.anchor = aqua::CVector2(m_size / 2.0f, m_size / 2.0f);
	//固定オブジェクトにする(色変更)
	m_Sprite.color = 0xffffff00;
	m_Sprite.rotation = 0.0f;
	m_Vertices[0] = aqua::CVector2(0.0f, 0.0f);
	m_Vertices[1] = aqua::CVector2(m_size, 0.0f);
	m_Vertices[2] = aqua::CVector2(m_size, m_size);
	m_Vertices[3] = aqua::CVector2(0.0f, m_size);
	m_Position = position1;
	m_FELIX_BLOCK = FELIX_BLOCK_ID::FELIX_BLOCK;

}
