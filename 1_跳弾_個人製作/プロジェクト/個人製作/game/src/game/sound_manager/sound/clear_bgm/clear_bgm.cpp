#include "Clear_bgm.h"

CClearBgm::CClearBgm(aqua::IGameObject* parent)
	:ISound(parent, "BattleBgm")
{
}

void CClearBgm::Initialize(bool loop)
{
	m_SoundPlayer.Create("data\\clear_bgm.mp3", loop);
	m_SoundPlayer.Play();
}
