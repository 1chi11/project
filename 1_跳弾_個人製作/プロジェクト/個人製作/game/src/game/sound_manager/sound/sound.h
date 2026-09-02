#pragma once
#include"aqua.h"

class ISound
	: public aqua::IGameObject
{
public:
	ISound(aqua::IGameObject* parent, const std::string& name);
	~ISound(void) = default;
	virtual void Initialize(bool loop);
	void Update(void) override;
	void Finalize(void) override;
protected:
	aqua::CSoundPlayer m_SoundPlayer;          //! サウンドプレイヤー
};