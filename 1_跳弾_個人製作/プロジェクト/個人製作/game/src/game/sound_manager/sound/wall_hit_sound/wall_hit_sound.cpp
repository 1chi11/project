#include "wall_hit_sound.h"

CWallHitSound::CWallHitSound(aqua::IGameObject* parent)
	: ISound(parent, "WallHitSound")
{
}

void CWallHitSound::Initialize(bool loop)
{
	m_SoundPlayer.Create("data\\wall_hit.mp3", loop);
	m_SoundPlayer.Play();
}
