#pragma once

#include "DrawBuffer.h"
#include <DirectXMath.h>

// �萔��`
#define MAX_LINES		(1000)
#define MAX_LINE_VTX	(MAX_LINES * 2)

// ���̒��_�o�b�t�@
struct LineVertex
{
	float pos[3];
	float color[4];
};

class Line
{
public:
	Line();
	~Line();

	void SetLine(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end);
	void Draw();

private:
	DrawBuffer m_buffer;
	LineVertex m_vtx[MAX_LINE_VTX];
	int m_drawNum;

};