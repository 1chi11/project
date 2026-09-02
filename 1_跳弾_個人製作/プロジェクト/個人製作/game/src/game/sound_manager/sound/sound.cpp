#include "sound.h"

ISound::ISound(aqua::IGameObject* parent, const std::string& name)
	: aqua::IGameObject(parent, "Sound")
{
}

void ISound::Initialize(bool loop)
{
	m_SoundPlayer.Create("data\\bgm.wav", loop);
	m_SoundPlayer.Play();
}

void ISound::Update(void)
{
	//サウンドの再生が終了したらオブジェクトを消去
	if (!m_SoundPlayer.IsPlaying())
	{
 		Finalize();
	};
	IGameObject::Update();
}

void ISound::Finalize(void)
{
	m_SoundPlayer.Delete();
	DeleteObject();
}
