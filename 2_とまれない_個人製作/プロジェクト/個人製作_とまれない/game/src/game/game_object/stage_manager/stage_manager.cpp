#include "stage_manager.h"
#include"..\character_manager\character_manager.h"
const int CStage::m_scroll = 2;

CStage::CStage(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "Stage")
{
}

void CStage::Initialize(void)
{
	m_Position = AQUA_NEW aqua::CVector2[m_scroll];
	m_Sprite.Create("data\\bg.png");
	
	for (int i = 0; i < m_scroll;i++)
	{
		m_Position[i] = aqua::CVector2{ (float)aqua::GetWindowWidth()*i,0.0f };
	}
}

void CStage::Update(void)
{
	//プレイヤーの位置に合わせて背景をスクロールさせる
	CCharacterManager* character_manager = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
	if (!character_manager)
		return;
	if (character_manager->GetPlayerTravelDistance().x < 0.0f)
	{
		return;
	}
	float pos = fmod(-character_manager->GetPlayerTravelDistance().x, (float)aqua::GetWindowWidth()) ;

	for (int i = 0; i < m_scroll;i++)
	{
		m_Position[i].x = pos + (float)aqua::GetWindowWidth()*i;
	}
}

void CStage::Draw(void)
{
	for (int i = 0; i < m_scroll; ++i)
	{
		m_Sprite.position = m_Position[i];
		m_Sprite.Draw();
	}
	
}

void CStage::Finalize(void)
{
	m_Sprite.Delete();
	AQUA_SAFE_DELETE_ARRAY(m_Position);
}
