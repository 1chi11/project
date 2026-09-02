#include "object_create_sound.h"

CObjectCreateSound::CObjectCreateSound(aqua::IGameObject* parent)
	: ISound(parent, "EnemyHit")
{
}

void CObjectCreateSound::Initialize(bool loop)
{
	m_SoundPlayer.Create("data\\create_object.mp3", loop);
	m_SoundPlayer.Play();
}
