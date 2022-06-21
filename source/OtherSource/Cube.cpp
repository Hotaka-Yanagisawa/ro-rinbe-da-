//--- インクルード
#include "Cube.h"
#include "Shader.h"
#include "Texture.h"

//==================================================
// 初期化
//==================================================
void Cube::Init()
{
	if (m_Parent != nullptr)
		m_Transform = m_Parent->Get<Transform>();

	// 頂点バッファ
	struct Vertex
	{
		float pos[3];
		float color[4];
		float uv[2];
	};
	Vertex vtx[] = {
		{{-m_Transform->Size.x, m_Transform->Size.y,-m_Transform->Size.z}, {1,1,1,1}, {0,1}},
		{{ m_Transform->Size.x, m_Transform->Size.y,-m_Transform->Size.z}, {1,1,1,1}, {1,1}},
		{{-m_Transform->Size.x,-m_Transform->Size.y,-m_Transform->Size.z}, {1,1,1,1}, {0,1}},
		{{ m_Transform->Size.x,-m_Transform->Size.y,-m_Transform->Size.z}, {1,1,1,1}, {1,1}},
		{{ m_Transform->Size.x, m_Transform->Size.y, m_Transform->Size.z}, {1,1,1,1}, {1,0}},
		{{-m_Transform->Size.x, m_Transform->Size.y, m_Transform->Size.z}, {1,1,1,1}, {0,0}},
		{{ m_Transform->Size.x,-m_Transform->Size.y, m_Transform->Size.z}, {1,1,1,1}, {0,1}},
		{{-m_Transform->Size.x,-m_Transform->Size.y, m_Transform->Size.z}, {1,1,1,1}, {1,1}},
	};
	// インデックスデータ
	long idx[] = {
		0,1,2, 1,3,2,	// 前
		4,5,6, 5,7,6,	// 奥
		1,4,3, 4,6,3,	// 右
		5,2,7, 0,2,5,	// 左
		5,4,0, 4,1,0,	// 上
		2,3,7, 3,6,7,	// 下
	};

	// バッファ作成
	m_Buffer.CreateVertexBuffer(vtx, sizeof(Vertex), sizeof(vtx) / sizeof(Vertex));
	m_Buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));

	m_pTexture = nullptr;
}

//==================================================
// 描画
//==================================================
void Cube::Draw()
{
	Draw(false);
}
void Cube::Draw(bool Line)
{
	SHADER->SetTexture(m_pTexture);
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(m_Transform->Size.x, m_Transform->Size.y, m_Transform->Size.z)
		* DirectX::XMMatrixRotationX(m_Transform->Rotate.x)
		* DirectX::XMMatrixRotationY(m_Transform->Rotate.y)
		* DirectX::XMMatrixRotationZ(m_Transform->Rotate.z)
		* DirectX::XMMatrixTranslation(m_Transform->Position.x, m_Transform->Position.y, m_Transform->Position.z)
	);

	if (Line) m_Buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	else m_Buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Cube::SetTexture(const char * FileName)
{
	m_pTexture = TEXTURE->Load(FileName);
}
