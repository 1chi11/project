#pragma once
#include"aqua.h"
#include"scene_id.h"
#include"..\..\sound_play_manager\sound_play_manager.h"
#include"..\..\mouse\mouse.h"

class IScene
	:public aqua::IGameObject
{
public:
	IScene(aqua::IGameObject* parent, const std::string& object_name);
	virtual ~IScene(void) = default;
	//シーンの変更
	void    Change(SCENE_ID id);
	//シーンをスタックする
	void    Push(SCENE_ID id);
	//スタックしたシーンを取り出す
	void    Pop(void);
	//シーンのリセット
	void    Reset(void);

private:
	static const std::string    m_scene_category;  //! シーンカテゴリー

};