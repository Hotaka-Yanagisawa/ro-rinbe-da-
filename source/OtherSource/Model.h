//=======================================================================
// Model.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/16	クラス作成しただけ
//			20	仮で読み込む
//			27	オブジェクトごとのモデルを管理させる
//		 12/18	一部をModelManagerに移動
//			19	デバッグ用のキューブモデル読み込み処理追加
//	2021/01/20	複数描画用フラグと処理
//
//=======================================================================
#pragma once

//--- インクルード
#include "Object.h"
#include "FBX/FBXPlayer.h"
#include "DrawBuffer.h"

//--- 定数
// マルチ対象
enum MultiInstanceModel
{
	MI_BTREE,
	//MI_ENEMY1,

	MULTI_MODEL_NUM
};

//--- クラス
class Model : public Component
{
public:
	Model() {}
	~Model() {}

	void Init() override;
	void Draw() override;

	void LoadModel(bool Load = true);

	FBXPlayer* m_Model;

private:
	Transform* m_Transform;
	DrawBuffer* m_pBuffer;

	float m_fDif;

public:
	bool m_bMulti;
	int m_nMultiNum;
	static void LoadMultiModel();
	static void DrawMultiModel();
private:
	static int m_nInstCount[MULTI_MODEL_NUM];
	static FBXPlayer* m_MultiModel[MULTI_MODEL_NUM];
	static DrawBuffer* m_pMultiBuffer[MULTI_MODEL_NUM];
};
