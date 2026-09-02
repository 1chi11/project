#include "shot_sound.h"

CShotSound::CShotSound(aqua::IGameObject* parent)
	: ISound(parent, "ShotSound")
{
}

void CShotSound::Initialize(bool loop)
{
	m_SoundPlayer.Create("data\\ball_shot.wav", loop);
	m_SoundPlayer.Play();
}
