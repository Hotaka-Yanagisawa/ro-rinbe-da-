//=======================================================================
// Effect.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/12/02	作成
//			16	プレイヤーの境界判定を可視化するためのプログラムを実装
//			22	土埃おためし
//			25	吸収エフェクト
//	2021/01/09	ヒット
//
//=======================================================================

//--- インクルード
#include "Pol2D.h"

//--- 定数
#define MAX_PARTICLE	(50 * 2)

//--- 列挙体
enum KIND
{
	PLAYER = 0,
	CIRCLE,
	SMOKE,
	POWER1,
	POWER2,
	POWER3,
	POWER4,
	POWER5,
	ABSORB,
	HIT,

	MAX
};

//--- クラス
class Effect
{
	struct PARTICLE
	{
		Pol2D Polygon;
		KIND Kind;
		int	nLife;
		bool bExist;
		float fMass;
	};

public:

	void Init();
	void Uninit();

	void Update();
	void Draw();

	void SetEffect(Float3 Pos, KIND Kind);

private:
	PARTICLE m_Particle[MAX_PARTICLE];

};
