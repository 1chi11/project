#include "battle_bgm.h"

CBgm::CBgm(aqua::IGameObject* parent)
	:ISound(parent, "BattleBgm")
{
}

void CBgm::Initialize(bool loop)
{
	m_SoundPlayer.Create("data\\bgm.wav", loop);
	m_SoundPlayer.Play();
}
