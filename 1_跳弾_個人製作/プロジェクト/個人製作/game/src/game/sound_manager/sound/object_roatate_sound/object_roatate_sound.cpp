#include "object_roatate_sound.h"

CObjectRoatateSound::CObjectRoatateSound(aqua::IGameObject* parent)
	: ISound(parent, "EnemyHit")
{
}

void CObjectRoatateSound::Initialize(bool loop)
{
	m_SoundPlayer.Create("data\\rotation_object.mp3", loop);
	m_SoundPlayer.Play();
}
