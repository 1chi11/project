#include "time_speed.h"
#include"..\game_object\character_manager\character_manager.h"
#include"..\game_object\item_object_manager\item_object_manager.h"
#include"..\sound_play_manager\sound_play_manager.h"
#include"..\effect_manager\effect_manager.h"

const float CTimeSpeed::m_default_time_speed = 1.0f;
const float CTimeSpeed::m_slow_time_speed = 0.5f;

CTimeSpeed::CTimeSpeed(aqua::IGameObject* parent)
	:IGameObject(parent, "TimeSpeed")
	,m_TimeSpeed(m_default_time_speed)
{
}

void CTimeSpeed::Update(void)
{
	CCharacterManager* chara_manager = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
	if (chara_manager)
		chara_manager->SetTimeSpeed(m_TimeSpeed);
	CItemObjectManager* item_manager = (CItemObjectManager*)aqua::FindGameObject("ItemObjectManager");
	if (item_manager)
		item_manager->SetTimeSpeed(m_TimeSpeed);
	CEffectManager* effect_manager = (CEffectManager*)aqua::FindGameObject("EffectManager");
	if (effect_manager)
		effect_manager->SetTimeSpeed(m_TimeSpeed);
}

void CTimeSpeed::SwitchTimeSpeed()
{
	//時間の速さを切り替える
	if (m_TimeSpeed == m_default_time_speed)
	{
		m_TimeSpeed = m_slow_time_speed;
	}
	else
	{
		m_TimeSpeed = m_default_time_speed;
	}
	CSoundPlayManager* sound_manager = (CSoundPlayManager*)aqua::FindGameObject("SoundPlayManager");
	if (sound_manager)
		sound_manager->Play(SOUND_ID::SWITCH_TIME);
}

void CTimeSpeed::DefaultTimeSpeed()
{
	m_TimeSpeed = m_default_time_speed;
}

void CTimeSpeed::SlowTimeSpeed()
{
	m_TimeSpeed = m_slow_time_speed;
}

float CTimeSpeed::GetTimeSpeed()const
{
	return m_TimeSpeed;
}
