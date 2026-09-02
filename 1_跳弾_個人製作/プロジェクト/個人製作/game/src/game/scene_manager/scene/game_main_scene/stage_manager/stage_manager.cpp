#include "stage_manager.h"
#include"..\..\..\..\bullet_manager\bullet_manager.h"
#include"..\..\..\..\chara_manager\chara_manager.h"
#include"..\..\..\..\block_manager\block_manager.h"


CStageManager::CStageManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "StageManager")
	,m_BulletManager(nullptr)
	,m_CharaManager(nullptr)
	,m_BlockManager(nullptr)
{
}


void CStageManager::Initialize(void)
{
	m_BackGround.Create("data\\field.png");
	m_BackGround.position = aqua::CVector2::ZERO;
	IGameObject::Initialize();
}

void CStageManager::Draw(void)
{
	m_BackGround.Draw();
	IGameObject::Draw();
}

void CStageManager::Create(STAGE_ID id)
{
	//CSVファイルからステージのレイアウトを読み込む
	aqua::CCSVLoader csv_loader;
	switch (id)
	{
	case STAGE_ID::ONE:
		csv_loader.Load("data\\stage1.csv");
		m_BackGround.Create("data\\field.png");
		break;
	case STAGE_ID::TWO:
		csv_loader.Load("data\\stage2.csv");
		m_BackGround.Create("data\\floor.png");
		break;
	case STAGE_ID::THREE:
		csv_loader.Load("data\\stage3.csv");
		m_BackGround.Create("data\\field.png");

		break;

	case STAGE_ID::FOUR:
		csv_loader.Load("data\\stage4.csv");
		m_BackGround.Create("data\\floor.png");

		break;

	case STAGE_ID::FIVE:
		csv_loader.Load("data\\stage5.csv");
		m_BackGround.Create("data\\field.png");
		break;
	case STAGE_ID::SIX:
		csv_loader.Load("data\\stage6.csv");
		m_BackGround.Create("data\\floor.png");
		break;
	case STAGE_ID::FINAL:
		csv_loader.Load("data\\stage7.csv");
		m_BackGround.Create("data\\field.png");

		break;

	default:
		break;
	}
	//CSVファイルからキャラ、オブジェクト、弾の配置を読み込む,配置に応じてキャラ、オブジェクト、弾を生成する
	for (int i = 0; i < csv_loader.GetRows(); ++i)
	{
			if (csv_loader.GetInteger(i, (int)OBJECT_ID_DATA::GAMEOBJECT_ID)==1)
			{
				CHRACTER_TABLE_DATA chara;
				chara.x = (float)csv_loader.GetInteger(i, (int)STAGE_LAYOUT_CHARACTER_DATA_PARAM::X);
				chara.y = (float)csv_loader.GetInteger(i, (int)STAGE_LAYOUT_CHARACTER_DATA_PARAM::Y);
				m_CharaManager->Create(aqua::CVector2(chara.x, chara.y));
			}
			
			if (csv_loader.GetInteger(i, (int)OBJECT_ID_DATA::GAMEOBJECT_ID) == 2)
			{
				OBJECT_TABLE_DATA object;
				object.x1 = (float)csv_loader.GetInteger(i, (int)STAGE_LAYOUT_OBJECT_DATA_PARAM::X);
				object.y1 = (float)csv_loader.GetInteger(i, (int)STAGE_LAYOUT_OBJECT_DATA_PARAM::Y);
				m_BlockManager->Create(BLOCK_ID::NOMAL_FELIX_BLOCK,aqua::CVector2(object.x1, object.y1), aqua::CVector2(object.x1, object.y1),0.0f);
			}
			
			if (csv_loader.GetInteger(i, (int)OBJECT_ID_DATA::GAMEOBJECT_ID) == 3)
			{
				OBJECT_TABLE_DATA object;
				object.x1 = (float)csv_loader.GetInteger(i, (int)STAGE_LAYOUT_MOVE_OBJECT_DATA_PARAM::X1);
				object.y1 = (float)csv_loader.GetInteger(i, (int)STAGE_LAYOUT_MOVE_OBJECT_DATA_PARAM::Y1);
				object.x2 = (float)csv_loader.GetInteger(i, (int)STAGE_LAYOUT_MOVE_OBJECT_DATA_PARAM::X2);
				object.y2 = (float)csv_loader.GetInteger(i, (int)STAGE_LAYOUT_MOVE_OBJECT_DATA_PARAM::Y2);
				object.speed = (float)csv_loader.GetInteger(i, (int)STAGE_LAYOUT_MOVE_OBJECT_DATA_PARAM::SPEED);
				m_BlockManager->Create(BLOCK_ID::MOVE_FELIX_BLOCK,aqua::CVector2(object.x1, object.y1), aqua::CVector2(object.x2, object.y2),object.speed);
			}
			
			if (csv_loader.GetInteger(i, (int)OBJECT_ID_DATA::GAMEOBJECT_ID) == 4)
			{
				BALL_TABLE_DATA ball;
				ball.x = (float)csv_loader.GetInteger(i, (int)STAGE_LAYOUT_BALL_DATA_PARAM::X);
				ball.y = (float)csv_loader.GetInteger(i, (int)STAGE_LAYOUT_BALL_DATA_PARAM::Y);
				ball.bounce = csv_loader.GetInteger(i, (int)STAGE_LAYOUT_BALL_DATA_PARAM::BOUNCE);
				m_BulletManager->Create(aqua::CVector2(ball.x, ball.y),ball.bounce);
			}
	}
	//CSVローダーのアンロード
	csv_loader.Unload();
}

void CStageManager::SetManager(CBulletManager* bullet, CCharaManager* chara, CBlockManager* block)
{
	if (!bullet || !chara || !block)
		return;
	m_BulletManager = bullet;
	m_CharaManager = chara;
	m_BlockManager = block;
}

void CStageManager::StageReset(bool clear)
{
	if ( !m_CharaManager||!m_BulletManager ||!m_BlockManager)
		return;
	m_CharaManager->Delete();
	m_BulletManager->Delete();
	m_BlockManager->Reset();

	//クリア時は設置したオブジェクトを消す
	if(clear&& m_BlockManager)
		m_BlockManager->Finalize();
}

