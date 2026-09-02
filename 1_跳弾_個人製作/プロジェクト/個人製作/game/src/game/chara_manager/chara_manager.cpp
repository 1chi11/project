#include "chara_manager.h"
#include"..\bullet_manager\bullet_manager.h"
#include"..\effect_manager\effect_manager.h"
#include <game/sound_manager/sound_manager.h>

CCharaManager::CCharaManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "CharaManager", "Manager")
	,m_BulletManager(nullptr)
{
}


void CCharaManager::Create(const aqua::CVector2& position)
{
	CChara* chara = aqua::CreateGameObject<CChara>(this);

	if (!chara)return;
	chara->Initialize(position);
}

void CCharaManager::Initialize()
{
	m_BulletManager = (CBulletManager*)aqua::FindGameObject("BulletManager");
}

void CCharaManager::Update()
{
	Hit();
	IGameObject::Update();
}

void CCharaManager::Delete()
{
	for (auto it : m_ChildObjectList)
	{
		CChara* chara = (CChara*)it;
		chara->Finalize();
	}
}


void CCharaManager::Hit()
{
	if (!m_BulletManager)
	{
		return;
	}
	//弾に一番近いキャラを返す
	for (auto it : m_ChildObjectList)
	{
		CChara* chara = (CChara*)it;
		if (!chara || !m_BulletManager)return;
		aqua::CVector2 v = chara->GetCenterPosition() - m_BulletManager->GetCenterPosition();
		if (v.Length() < (m_BulletManager->GetRadius()+chara->GetRadius()))
		{
			CSoundManager* sound = (CSoundManager*)aqua::FindGameObject("SoundManager");
			sound->Create(SOUND_ID::ENEMY_HIT, false);
			CEffectManager* effect = (CEffectManager*)aqua::FindGameObject("EffectManager");
			effect->Create(EFFECT_ID::ENEMY_HIT_EFFECT, chara->GetCenterPosition());
			chara->Hit();
		}
	}
}

bool CCharaManager::CharaExist()
{
	//ステージに残ってるキャラの数
	int i = 0;
	for (auto it : m_ChildObjectList)
	{
		i++;
		CChara* chara = (CChara*)it;
	}
	if (i > 0)
		return false;
	else
		return true;
}

