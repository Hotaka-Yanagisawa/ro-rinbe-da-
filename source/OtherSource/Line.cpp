#include "Line.h"

Line::Line() : m_drawNum(0)
{
	//--- 描画する直線の頂点情報
	for (int i = 0; i < MAX_LINE_VTX; i++)
	{
		m_vtx[i].color[0] =
			m_vtx[i].color[1] =
			m_vtx[i].color[2] =
			m_vtx[i].color[3] = 1.0f;
	};
	m_buffer.CreateVertexBuffer(m_vtx, sizeof(LineVertex), MAX_LINE_VTX, true);
}
Line::~Line()
{
}

void Line::SetLine(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end)
{
	// 頂点配列の先頭から直線のデータを格納
	if (m_drawNum < MAX_LINE_VTX)
	{
		m_vtx[m_drawNum].pos[0] = start.x;
		m_vtx[m_drawNum].pos[1] = start.y;
		m_vtx[m_drawNum].pos[2] = start.z;
		++m_drawNum;
		m_vtx[m_drawNum].pos[0] = end.x;
		m_vtx[m_drawNum].pos[1] = end.y;
		m_vtx[m_drawNum].pos[2] = end.z;
		++m_drawNum;
	}
}

void Line::Draw()
{
#if 0	// 書き込みテスト
	static float f = 0.0f;
	LineVertex vtx[] = {
		{ { 0, 0, 0}, {1,1,1,1} },
		{ { sinf(f), 5, 0}, {1,1,1,1} },
	};
	f += 0.1f;
	m_buffer.Write(vtx);
#endif

	// 使用していない頂点データは初期化
	for (int i = m_drawNum; i < MAX_LINE_VTX; i++)
	{
		m_vtx[i].pos[0] =
			m_vtx[i].pos[1] =
			m_vtx[i].pos[2] = 0.0f;
	}

	// 描画までに溜めた直線の情報を頂点バッファへ書き込み
	m_buffer.Write(m_vtx);

	// 直線を描画するときのプリミティブ
	// 頂点バッファ内のデータを二つずつ読み取って直線を描画
	m_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// 描画データクリア
	m_drawNum = 0;
}
