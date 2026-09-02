#include "bounce_count.h"
#include"..\..\..\bullet_manager\bullet_manager.h"
const float CBounceCount::m_size = 40.0f;

CBounceCount::CBounceCount(aqua::IGameObject* parent)
	:IUi(parent, "BounceCount")
{
}

void CBounceCount::Initialize(aqua::CVector2 position)
{
	m_One_Digit.Create("data\\bounce.png");
	m_Two_Digit.Create("data\\bounce.png");
	m_One_Digit.position = position;
	m_One_Digit.position.x += m_size;
	m_Two_Digit.position = position;
}

void CBounceCount::Update()
{
	CBulletManager* bullet = (CBulletManager*)aqua::FindGameObject("BulletManager");
	if (bullet)
	{
		m_One_Digit.rect.left =0+ (bullet->GetBounceCount()%10)*(int)m_size;
		m_One_Digit.rect.right = m_One_Digit.rect.left+(int) m_size;
		//10‚ÌˆÊ‚ª‘¶Ý‚µ‚È‚¢ê‡‚Í“§–¾‚É‚·‚é
		if (bullet->GetBounceCount() >= 10)
		{
			m_Two_Digit.color.alpha = 255;
			m_Two_Digit.rect.left = 0 + (bullet->GetBounceCount() / 10) * (int)m_size;
			m_Two_Digit.rect.right = m_Two_Digit.rect.left + (int)m_size;
		}else
			m_Two_Digit.color.alpha = 0;
	}
}

void CBounceCount::Draw()
{
	m_One_Digit.Draw();
	m_Two_Digit.Draw();

}
