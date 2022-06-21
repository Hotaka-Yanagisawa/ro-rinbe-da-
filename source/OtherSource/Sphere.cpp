//--- インクルード
#include "Sphere.h"
#include "Shader.h"
#include "Texture.h"
#include "SelectScene.h"

//==================================================
// 初期化
//==================================================
void Sphere::Init()
{
	m_Transform = m_Parent->Get<Transform>();

	// 頂点バッファ
	struct Vertex
	{
		float pos[3];
		float color[4];
	};
	const int u_max = 30;
	const int v_max = 15;
	int vertex_num = u_max * (v_max + 1);
	int index_num = 2 * v_max * (u_max + 1);

	Vertex* vertices = new Vertex[vertex_num];
	for (int v = 0; v <= v_max; v++) {
		for (int u = 0; u < u_max; u++) {
			float theta = DirectX::XMConvertToRadians(180.0f * v / v_max);
			float phi = DirectX::XMConvertToRadians(360.0f * u / u_max);
			vertices[u_max * v + u].pos[0] = sin(theta) * cos(phi);
			vertices[u_max * v + u].pos[1] = cos(theta);
			vertices[u_max * v + u].pos[2] = sin(theta) * sin(phi);
		}
	}
	for (int i = 0; i < vertex_num; i++)
		vertices[i].color[0] =
		vertices[i].color[1] =
		vertices[i].color[2] =
		vertices[i].color[3] = 1;

	// ポリゴンのインデックスデータの作成
	int i = 0;
	long* indexes = new long[index_num];
	//for (int v = v_max - 1; v >= 0; v--)
	for (int v = 0; v < v_max; v++)
	{
		//for (int u = u_max; u >= 0; u--)
		for (int u = 0; u <= u_max; u++)
		{
			if (u == u_max)
			{
				indexes[i++] = v * u_max;
				indexes[i++] = (v + 1) * u_max;
			}
			else
			{
				indexes[i++] = (v * u_max) + u;
				indexes[i++] = indexes[i - 1] + u_max;
			}
		}
	}
	// バッファ作成
	m_Buffer.CreateVertexBuffer(vertices, sizeof(Vertex), vertex_num);
	m_Buffer.CreateIndexBuffer(indexes, index_num);

	switch (SelectScene::m_nSelect)
	{
	case 0:
		m_pTexture = TEXTURE->Load(TEX_PNG("BlueSky"));

		break;
	case 1:
		m_pTexture = TEXTURE->Load(TEX_PNG("OrangeSky"));

		break;
	case 2:
		m_pTexture = TEXTURE->Load(TEX_PNG("BlackSky"));

		break;
	}
	m_Transform->Rotate.z = 3.1415f;
}

//==================================================
// 描画
//==================================================
void Sphere::Draw()
{
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(m_Transform->Size.x, m_Transform->Size.y, m_Transform->Size.z)
		* DirectX::XMMatrixRotationX(m_Transform->Rotate.x)
		* DirectX::XMMatrixRotationY(m_Transform->Rotate.y)
		* DirectX::XMMatrixRotationZ(m_Transform->Rotate.z)
		* DirectX::XMMatrixTranslation(m_Transform->Position.x, m_Transform->Position.y, m_Transform->Position.z)
	);

	SHADER->SetLightAmbient(DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f));
	SHADER->SetTexture(m_pTexture);

	GET_DX->SetRasterizer(RASTERIZE::ZCLIP_OFF);

	m_Buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	GET_DX->SetRasterizer(RASTERIZE::NORMAL);

	SHADER->SetLightAmbient(DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.f));
}
