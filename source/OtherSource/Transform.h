//=======================================================================
// Transform.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/12	operatorしたかったのでFloat3作成 でも微妙
//			15	Transform作成 Float3と統一
//			24	MoveとAccel追加 移すかも
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Component.h"
#include <DirectXMath.h>

struct Float3	// 3次元座標
{
	float x, y, z;

	Float3(float v) :x(v), y(v), z(v) {}
	Float3(float x, float y, float z) :x(x), y(y), z(z) {}

	// DX変換用
	DirectX::XMFLOAT3 DXFloat3() { return DirectX::XMFLOAT3(x, y, z); }

	// 絶対値
	Float3 abs()
	{
		return Float3(
			(x < 0) ? -x : x,
			(y < 0) ? -y : y,
			(z < 0) ? -z : z);
	}

	//--- 演算子オーバーロード
	// 代入
	Float3 &operator =(const Float3 &r)
	{
		x = r.x;
		y = r.y;
		z = r.z;
		return *this;
	}
	Float3 &operator =(const float  &v)
	{
		x = v;
		y = v;
		z = v;
		return *this;
	}
	// 算術
	Float3 operator +(const Float3 &r) const
	{
		Float3 t;
		t.x = x + r.x;
		t.y = y + r.y;
		t.z = z + r.z;
		return t;
	}
	Float3 operator -(const Float3 &r) const
	{
		Float3 t;
		t.x = x - r.x;
		t.y = y - r.y;
		t.z = z - r.z;
		return t;
	}
	Float3 operator *(const Float3 &r) const
	{
		Float3 t;
		t.x = x * r.x;
		t.y = y * r.y;
		t.z = z * r.z;
		return t;
	}
	Float3 operator /(const Float3 &r) const
	{
		Float3 t;
		t.x = x / r.x;
		t.y = y / r.y;
		t.z = z / r.z;
		return t;
	}
	// 複合代入
	Float3 operator +=(const Float3 &r)
	{
		x += r.x;
		y += r.y;
		z += r.z;
		return *this;
	}
	Float3 operator -=(const Float3 &r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}
	Float3 operator *=(const Float3 &r)
	{
		x *= r.x;
		y *= r.y;
		z *= r.z;
		return *this;
	}
	Float3 operator *=(const float  &v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}
	Float3 operator /=(const Float3 &r)
	{
		x /= r.x;
		y /= r.y;
		z /= r.z;
		return *this;
	}
	Float3 operator /=(const float  &v)
	{
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}
	// 比較(未実装)

	Float3() = default;
	virtual ~Float3() {}

private:
};
struct Transform : public Component
{
	Float3 Position;	// 座標
	Float3 Size;		// 大きさ
	Float3 Rotate;		// 回転

	Float3 Move;	// 移動量
	Float3 Accel;	// 加速度

	Transform() :Position(0), Size(1), Rotate(0), Move(0), Accel(0) {}
	~Transform() {}

private:
};
