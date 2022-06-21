//=======================================================================
// Transform.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/12	operator�����������̂�Float3�쐬 �ł�����
//			15	Transform�쐬 Float3�Ɠ���
//			24	Move��Accel�ǉ� �ڂ�����
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Component.h"
#include <DirectXMath.h>

struct Float3	// 3�������W
{
	float x, y, z;

	Float3(float v) :x(v), y(v), z(v) {}
	Float3(float x, float y, float z) :x(x), y(y), z(z) {}

	// DX�ϊ��p
	DirectX::XMFLOAT3 DXFloat3() { return DirectX::XMFLOAT3(x, y, z); }

	// ��Βl
	Float3 abs()
	{
		return Float3(
			(x < 0) ? -x : x,
			(y < 0) ? -y : y,
			(z < 0) ? -z : z);
	}

	//--- ���Z�q�I�[�o�[���[�h
	// ���
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
	// �Z�p
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
	// �������
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
	// ��r(������)

	Float3() = default;
	virtual ~Float3() {}

private:
};
struct Transform : public Component
{
	Float3 Position;	// ���W
	Float3 Size;		// �傫��
	Float3 Rotate;		// ��]

	Float3 Move;	// �ړ���
	Float3 Accel;	// �����x

	Transform() :Position(0), Size(1), Rotate(0), Move(0), Accel(0) {}
	~Transform() {}

private:
};
