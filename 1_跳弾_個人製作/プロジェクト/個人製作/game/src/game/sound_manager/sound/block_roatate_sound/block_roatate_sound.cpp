#include "block_roatate_sound.h"

CBlockRoatateSound::CBlockRoatateSound(aqua::IGameObject* parent)
	: ISound(parent, "EnemyHit")
{
}

void CBlockRoatateSound::Initialize(bool loop)
{
	m_SoundPlayer.Create("data\\rotation_object.mp3", loop);
	m_SoundPlayer.Play();
}
