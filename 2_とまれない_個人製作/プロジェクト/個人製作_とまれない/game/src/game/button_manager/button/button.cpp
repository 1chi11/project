#include "button.h"
#include"..\..\mouse\mouse.h"

const int CButton::m_sprite_count = 9;
const int CButton::m_corner_size = 12;
const unsigned int  CButton::m_default_color = 0xffffffff;
const unsigned int  CButton::m_selected_color = 0xffeeeeee;
const unsigned int  CButton::m_clicked_color = 0xffeeffff;
const unsigned int  CButton::m_text_color = 0xff000000;
const int
CButton::m_default_font_size = 16;
const int
CButton::m_default_texture_size = 64;

//コンストラクタ
CButton::CButton(aqua::IGameObject* parent)
	: IGameObject(parent, "Button")
	, m_Position(aqua::CVector2(0.0f, 0.0f))
	, m_Width(m_default_texture_size)
	, m_Height(m_default_texture_size)
	, m_Button_Id(BUTTON_ID::TRIGGER)
	, m_ButtonSetGameObjectId(GAME_OBJECT_ID::DUMMY)
{
}

//初期化
void CButton::Initialize(ClickEvent click_event, const aqua::CVector2& position, const std::string& name, GAME_OBJECT_ID id)
{
	m_TextureSprite.Create(name);
	m_Sprite = AQUA_NEW aqua::CSprite[m_sprite_count];
	for (int i = 0; i < m_sprite_count; ++i)
	{
		m_Sprite[i].Create("data\\button.png");
	}

	OnClick = click_event;


	SetupRect();
	SetSize(200, 100);
	SetPosition(position);
	m_Label.Create(m_default_font_size);
	m_Label.position = position;
	m_Label.position.y = m_Height / 2.0f - m_default_font_size / 2.0f;
	m_Label.position.x += m_Width / 5.0f ;
	m_Label.text = "";
	m_Label.color = m_text_color;
	m_ButtonSetGameObjectId = id;
}

void CButton::Update(void)
{
	namespace mouse = aqua::mouse;
	CMouseControl* control = (CMouseControl*)aqua::FindGameObject("MouseControl");
	aqua::CVector2 mpos = control->GetCursorPos();
	if (mpos.x > m_Position.x && mpos.x < m_Position.x + m_Width
		&& mpos.y > m_Position.y && mpos.y < m_Position.y + m_Height)
	{
		SetColor(m_selected_color);
		if (control->Button(mouse::BUTTON_ID::LEFT))
		{
			SetColor(m_clicked_color);
			Click();
		}
	}
	else
		SetColor(m_default_color);

}

void CButton::Draw(void)
{
	for (int i = 0; i < m_sprite_count; ++i)
		m_Sprite[i].Draw();
	
	m_TextureSprite.Draw();
	m_Label.Draw();
}

void CButton::Finalize(void)
{
	AQUA_SAFE_DELETE_ARRAY(m_Sprite);
	m_TextureSprite.Delete();
	m_Label.Delete();
	DeleteObject();
}


void CButton::SetPosition(const aqua::CVector2& position)
{
	m_Position = position;

	// 各スプライトの位置設定 
	float cw = (float)(m_Width - m_corner_size);
	float ch = (float)(m_Height - m_corner_size);

	m_Sprite[(int)LAYOUT_ID::UPPER_LEFT].position = m_Position;
	m_Sprite[(int)LAYOUT_ID::UPPER_RIGHT].position = m_Position + aqua::CVector2(
		cw,
		0.0f);
	m_Sprite[(int)LAYOUT_ID::LOWER_LEFT].position = m_Position + aqua::CVector2(
		0.0f, ch);
	m_Sprite[(int)LAYOUT_ID::LOWER_RIGHT].position = m_Position + aqua::CVector2(
		cw, ch);
	m_Sprite[(int)LAYOUT_ID::LEFT].position = m_Position + aqua::CVector2(0.0f,
		(float)m_corner_size);
	m_Sprite[(int)LAYOUT_ID::UPPER].position = m_Position + aqua::CVector2(
		(float)m_corner_size, 0.0f);
	m_Sprite[(int)LAYOUT_ID::RIGHT].position = m_Position + aqua::CVector2(cw,
		(float)m_corner_size);
	m_Sprite[(int)LAYOUT_ID::LOWER].position = m_Position + aqua::CVector2(
		(float)m_corner_size, ch);
	m_Sprite[(int)LAYOUT_ID::CENTER].position = m_Position + aqua::CVector2(
		(float)m_corner_size, (float)m_corner_size);

	// ラベルの座標修正 
	m_TextureSprite.position = m_Position;
	m_TextureSprite.position.x += (float)m_Width / 2.0f - (float)m_TextureSprite.GetTextureWidth() / 2.0f;
	m_TextureSprite.position.y += (float)m_Height / 2.0f - (float)m_TextureSprite.GetTextureHeight() / 2.0f;
}
void CButton::SetSize(int width, int height)
{
	m_Width = width;
	m_Height = height;

	float cs = m_corner_size * 2.0f;

	float sw = (float)(m_Width - cs) / (float)(m_default_texture_size - cs);
	float sh = (float)(m_Height - cs) / (float)(m_default_texture_size - cs);

	m_Sprite[(int)LAYOUT_ID::LEFT].scale = aqua::CVector2(1.0f, sh);
	m_Sprite[(int)LAYOUT_ID::UPPER].scale = aqua::CVector2(sw, 1.0f);
	m_Sprite[(int)LAYOUT_ID::RIGHT].scale = aqua::CVector2(1.0f, sh);
	m_Sprite[(int)LAYOUT_ID::LOWER].scale = aqua::CVector2(sw, 1.0f);
	m_Sprite[(int)LAYOUT_ID::CENTER].scale = aqua::CVector2(sw, sh);

	SetPosition(m_Position);
}
void CButton::SetButton(BUTTON_ID id)
{
	m_Button_Id = id;
}
void CButton::Click()
{
	namespace mouse = aqua::mouse;
	switch (m_Button_Id)
	{
	case BUTTON_ID::BUTTON:
		if (mouse::Button(mouse::BUTTON_ID::LEFT))
			OnClick();
		break;
	case BUTTON_ID::TRIGGER:
		if (mouse::Trigger(mouse::BUTTON_ID::LEFT))
			OnClick();
		break;
	case BUTTON_ID::RELEASED:
		if (mouse::Released(mouse::BUTTON_ID::LEFT))
			OnClick();
		break;
	default:
		break;
	}
}
void CButton::SetText(int count)
{
	m_Label.text = std::to_string(count);
}
GAME_OBJECT_ID CButton::GetButtonSetGameObjectId(void)
{
	return m_ButtonSetGameObjectId;
}
void CButton::SetupRect(void)
{
	int cs = m_default_texture_size - m_corner_size;

	m_Sprite[(int)LAYOUT_ID::UPPER_LEFT].rect = aqua::CRect(0, 0,
		m_corner_size, m_corner_size);
	m_Sprite[(int)LAYOUT_ID::UPPER_RIGHT].rect = aqua::CRect(cs, 0,
		m_default_texture_size, m_corner_size);
	m_Sprite[(int)LAYOUT_ID::LOWER_LEFT].rect = aqua::CRect(0, cs,
		m_corner_size, m_default_texture_size);
	m_Sprite[(int)LAYOUT_ID::LOWER_RIGHT].rect = aqua::CRect(cs, cs,
		m_default_texture_size, m_default_texture_size);
	m_Sprite[(int)LAYOUT_ID::LEFT].rect = aqua::CRect(0, m_corner_size,
		m_corner_size, cs);
	m_Sprite[(int)LAYOUT_ID::UPPER].rect = aqua::CRect(m_corner_size, 0,
		cs, m_corner_size);
	m_Sprite[(int)LAYOUT_ID::RIGHT].rect = aqua::CRect(cs, m_corner_size,
		m_default_texture_size, cs);
	m_Sprite[(int)LAYOUT_ID::LOWER].rect = aqua::CRect(m_corner_size, cs,
		cs, m_default_texture_size);
	m_Sprite[(int)LAYOUT_ID::CENTER].rect = aqua::CRect(m_corner_size,
		m_corner_size, cs, cs);
}

void CButton::SetColor(const aqua::CColor& color)
{
	for (int i = 0; i < m_sprite_count; ++i)
		m_Sprite[i].color = color;
}
