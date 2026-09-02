#pragma once
#include"..\..\item_object\item_object.h"

class CUmbrella : public IItemObject
{
public:
	CUmbrella(aqua::IGameObject* parent);
	~CUmbrella(void) = default;
	void Initialize(const aqua::CVector2& position, const bool set_flag) override;
	void Update(void) override;
	void Hit(ICharacter*& character) override;
private:
	static const float m_width;
	static const float m_height;
};

