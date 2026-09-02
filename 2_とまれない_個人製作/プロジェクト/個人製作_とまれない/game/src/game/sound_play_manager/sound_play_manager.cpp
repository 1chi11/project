#include "sound_play_manager.h"
const int CSoundPlayManager::m_bolume = 25;
const std::string CSoundPlayManager::m_sound_file_names[] =
{
    "data\\bgm.mp3",
    "data\\click_sound.mp3",
    "data\\decision.wav",
    "data\\hit.wav",
    "data\\check_point.wav",
    "data\\create_object.mp3",
    "data\\select.wav",
    "data\\switch_time.mp3",

};

/*
 *  コンストラクタ
 */
CSoundPlayManager::
CSoundPlayManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "SoundPlayManager")
    , m_SoundPlayer(nullptr)
{
}

void CSoundPlayManager::Initialize(void)
{
    if (!m_SoundPlayer) m_SoundPlayer = AQUA_NEW aqua::CSoundPlayer[(int)SOUND_ID::MAX];

    // BGMはループ再生設定
    m_SoundPlayer[(int)SOUND_ID::BGM].Create(m_sound_file_names[(int)SOUND_ID::BGM], true);
    m_SoundPlayer[(int)SOUND_ID::BGM].SetVolume(m_bolume);
    // SEは単発
    for (int i = (int)SOUND_ID::DECISION; i < (int)SOUND_ID::MAX; ++i)
    {
        m_SoundPlayer[i].Create(m_sound_file_names[i], false, 100);
        m_SoundPlayer[i].SetVolume(m_bolume);
    }

}

void CSoundPlayManager::Finalize(void)
{
    for (int i = (int)SOUND_ID::BGM; i < (int)SOUND_ID::MAX; ++i)
    {
        m_SoundPlayer[i].Delete();
    }
    AQUA_SAFE_DELETE_ARRAY(m_SoundPlayer);
}

void CSoundPlayManager::Play(const SOUND_ID id)
{
    if(!m_SoundPlayer)
        return;
    m_SoundPlayer[static_cast<int>(id)].Play();
}

void CSoundPlayManager::Stop(const SOUND_ID id)
{
    if (!m_SoundPlayer)
        return;
    m_SoundPlayer[static_cast<int>(id)].Stop();
}

void CSoundPlayManager::SetTimeSpeed(const float rate)
{
    for (int i = (int)SOUND_ID::BGM; i < (int)SOUND_ID::MAX; ++i)
        m_SoundPlayer[i].SetTimeSpeed(rate);
}

