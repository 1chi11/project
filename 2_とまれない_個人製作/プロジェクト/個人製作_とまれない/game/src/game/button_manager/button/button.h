#pragma once
#include"aqua.h"
#include<functional>
#include"button_id.h"
#include"..\..\game_object\game_object_id.h"

using ClickEvent = std::function<void(void)>;


// ボタンクラス
class CButton
    :public aqua::IGameObject
{
public:
    CButton(aqua::IGameObject* parent);
    ~CButton(void) = default;

    //初期化（関数ポインタを受け取る）
    void Initialize(ClickEvent click_event, const aqua::CVector2& position, const std::string& name,GAME_OBJECT_ID id);

    void Update(void) override;
    void Draw(void) override;
    void Finalize(void) override;
    void SetPosition(const aqua::CVector2& position);
    void SetSize(int width, int height);
    void SetButton(BUTTON_ID id);       //OnClickの呼び出し方を変えられる(BUTTON,RELEASED,TRIGGER)
    void Click();                                       //OnClickの呼び出し
	void SetText(int count);

    GAME_OBJECT_ID GetButtonSetGameObjectId(void);
private:

    enum class LAYOUT_ID
    {
        UPPER_LEFT,         // 左上 
        UPPER_RIGHT,        // 右上
        LOWER_LEFT,         // 左上
        LOWER_RIGHT,        // 右下
        LEFT,               // 左
        UPPER,              // 上
        RIGHT,              // 右
        LOWER,              // 下
        CENTER,             // 中央　
    };

    void    SetupRect(void);
    void    SetColor(const aqua::CColor& color);
    static const int m_sprite_count;
    static const int m_corner_size;

    static const unsigned int   m_default_color;    // デフォルトの色 
    static const unsigned int   m_selected_color;   // カーソルが乗っているときの色 
    static const unsigned int   m_clicked_color;    // クリックされたときの色 
    static const unsigned int   m_text_color;       // テキストの色
    static const int    m_default_font_size;        // テキストの大きさ
    static const int    m_default_texture_size;     // テクスチャの大きさ
    aqua::CSprite* m_Sprite;        // ボタンスプライト
	aqua::CSprite m_TextureSprite;  // テクスチャスプライト
    aqua::CVector2 m_Position;      // ボタンの位置
	aqua::CLabel m_Label;           // ボタンのラベル
    int m_Width;    // ボタンの横幅
    int m_Height;   // ボタンの立幅
   
    ClickEvent   OnClick;    //functionオブジェクト

    BUTTON_ID m_Button_Id;  //OnClickの呼び出し方
	GAME_OBJECT_ID m_ButtonSetGameObjectId;  //ゲームオブジェクトID
};

