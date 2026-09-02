#pragma once
#include"aqua.h"

enum class SOUND_ID
{
    BGM,            //BGM
    DECISION,       //決定音
    JUMP,           //ジャンプ
    HIT,            //ヒット
    CHECK_POINT,    //チェックポイント
    CREATE,         //生成音
    CLICK,          //クリック
    SWITCH_TIME,    //時間の切り替え

    MAX             //サウンドIDの数
};
class CSoundPlayManager
    : public aqua::IGameObject
{
public:
    CSoundPlayManager(aqua::IGameObject* parent);
    ~CSoundPlayManager(void) = default;
    void Initialize(void) override;
    void Finalize(void) override;
    //音の再生
    void Play(const SOUND_ID id);
    //音の停止
    void Stop(const SOUND_ID id);
    //音の速さを入れる（仮）
    void SetTimeSpeed(const float rate);
private:
    static const std::string    m_sound_file_names[];   //サウンドファイルパス
    static const int    m_bolume;               //音量
    aqua::CSoundPlayer* m_SoundPlayer;          //サウンドプレイヤー
};
