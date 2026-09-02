#pragma once

#include "aqua.h"
#include "scene\scene_id.h"

class CSceneManager
    : public aqua::IGameObject
{
public:
    CSceneManager(aqua::IGameObject* parent);
    ~CSceneManager(void) = default;
    void        Initialize(void) override;
    void        Update(void) override;
    void        Draw(void) override;
    void        Finalize(void) override;

    //シーンの切り替え
    void        Change(SCENE_ID id);
    //シーンをスタックする
    void        Push(SCENE_ID id);
    //      スタックしたシーンを取り出す
    void        Pop(void);
    //現在のシーンをリセットする
    void        Reset(void);
private:
    //シーンの状態
    enum class STATE
    {
        SCENE_IN,         //! 開始
        SCENE_UPDATA,     //! 更新
        SCENE_OUT,        //! 終了
        SCENE_CHANGE,     //! 変更
    };
    //シーンの生成
    void        Create(SCENE_ID id);
    //現在のシーンの消去
    void        Delete(void);
    //シーンの開始演出
    void        SceneIn(void);
    //シーンの更新
    void        SceneUpdate(void);
    //シーンの終了演出
    void        SceneOut(void);
    //シーン変更
    void        SceneChange(void);

    static const float  m_fade_speed;       //! フェード速度
    SCENE_ID            m_CurrentSceneID;   //! 現在のシーンID
    SCENE_ID            m_NextSceneID;      //! 次のシーンID
    SCENE_ID            m_PushSceneID;      //! プッシュするシーンID
    STATE               m_State;            //! 状態ID
    bool                m_PushFlag;         //! シーンのプッシュが行われた
    aqua::CSprite       m_FadeSprite;       //! フェード用スプライト
};
