//=======================================================================
// Camera.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生, 中村洸介
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/18	授業内のを書き換え
//			19	シングルトン
//			2X	自由に操作できるように変更
//			28	平行投影
//	2020/12/02	試しにゲームパッド右スティックによるカメラ操作を可能に。(中村
//			03  プレイヤーの背後に視点を移動する機能を実装。
//			04	lateのmoveとpositionをヘッダーに追加
//				リスタート時にカメラの視点をリセットするように実装。Reset関数実装
//			
//=======================================================================
#pragma once

//--- インクルード
#include <DirectXMath.h>
#include "Object.h"
#include "Transform.h"
#include "State/CameraState.h"

//--- マクロ
#define CAMERA	(Camera::GetInstance())

//--- クラス
class Camera
{
public:
	inline static Camera* GetInstance()
	{
		static Camera instance;
		return &instance;
	}

	void Init();
	void Uninit();
	void Update();

	void Bind(bool Parallel = false);

	void SetObject(Object*);

	DirectX::XMMATRIX m_ViewMatrix;

	// XZ軸上での角度(0°で-Zの位置)
	float m_xzAngle;

	Float3 m_Position;
	Float3 m_LatePosition;
	Float3 m_Look;
	Float3 m_LateLook;
	Float3 m_Up;

	float m_Angle;
	float m_Near;
	float m_Far;

	// Y軸上での角度
	float m_yAngle;
	// 中心からの距離
	float m_radius;

	Object* m_pTarget;

	CameraState *m_State;

	DirectX::XMMATRIX TransWVP(DirectX::XMMATRIX);

private:


	Camera() {}
	~Camera() {}
};
