#pragma once
#include "aqua.h"

class CScoreManager
	: public aqua::IGameObject
{
public:
	CScoreManager(aqua::IGameObject* parent);
	~CScoreManager(void);
	void Initialize(void)override;
	//なにもしない
	void Finalize(void)override;
	//解放
	void FinalizeScore(void);
	
	bool GetClearFlag(void)const;
	//リザルト画面のスコア表示
	void ResultDraw(void);
	//ゲーム中のスコア表示
	void GamePlayDraw(void);
	//スコアマネージャーの解放
	void ScoreManagerFinalize(void);
	//スコアの初期化
	void InitializeScore(int max);
	//スコアの減算
	void SubtractScore(int score);
	//スコアの加算
	void AddScore(int score);
	//タイムの設定
	void SetTime(int time);
	//ステージ番号の設定
	void SetStageNumber(int stage_number);
	//クリアフラグの設定
	void SetClearFlag(bool flag);
private:
	static const aqua::CVector2 m_score_label_position_result;	//リザルト画面のスコア表示用ラベルの位置
	static const aqua::CVector2 m_score_label_position_gameplay;	//ゲーム中のスコア表示用ラベルの位置
	static const int m_score_label_size_gameplay;	//スコア表示用ラベルのサイズ
	static const int m_score_label_size_result;	//スコア表示用ラベルのサイズ
	aqua::CLabel m_ScoreLabel;	//スコア表示用ラベル
	int* m_Score;				//スコア
	int* m_Time;				//タイム
	int m_StageNumber;			//ステージ番号
	int m_MaxStage;				//最大ステージ数
	bool m_ClearFlag;			//クリアフラグ
};
