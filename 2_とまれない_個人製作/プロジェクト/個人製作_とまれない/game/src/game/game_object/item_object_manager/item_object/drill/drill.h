#pragma once
#include"..\..\item_object\item_object.h"

class CDrill : public IItemObject
{
public:
	CDrill(aqua::IGameObject* parent);
	~CDrill(void) = default;
	void Initialize(const aqua::CVector2& position,const bool set_flag) override;
	void Hit(ICharacter*& character) override;
private:
	static const float m_width;
	static const float m_height;

	static const float m_drill_time;	//ドリルの効果時間
};