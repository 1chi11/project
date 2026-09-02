#include "enemy_hit_sound.h"

CEnemyHitSound::CEnemyHitSound(aqua::IGameObject* parent)
	: ISound(parent, "EnemyHit")
{
}

void CEnemyHitSound::Initialize(bool loop)
{
	m_SoundPlayer.Create("data\\enemy_hit.wav", loop);
	m_SoundPlayer.Play();
}
