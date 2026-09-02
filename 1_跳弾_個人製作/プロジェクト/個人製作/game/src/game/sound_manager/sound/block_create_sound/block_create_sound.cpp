#include "block_create_sound.h"

CBlockCreateSound::CBlockCreateSound(aqua::IGameObject* parent)
	: ISound(parent, "EnemyHit")
{
}

void CBlockCreateSound::Initialize(bool loop)
{
	m_SoundPlayer.Create("data\\create_object.mp3", loop);
	m_SoundPlayer.Play();
}
