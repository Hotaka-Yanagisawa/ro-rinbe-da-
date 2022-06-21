//--- インクルード
#include "Pol2D.h"
#include "Shader.h"
#include "Camera.h"

//==================================================
// 初期化
//==================================================
void Pol2D::Init()
{
	m_Vertex = new Vertex[4];

	m_Vertex[0].pos = { -0.5f, 0.5f, 0 };
	m_Vertex[1].pos = {  0.5f, 0.5f, 0 };
	m_Vertex[2].pos = { -0.5f,-0.5f, 0 };
	m_Vertex[3].pos = { 0.5f, -0.5f, 0 };

	for (int i = 0; i < 4; ++i)
		m_Vertex[i].color = DirectX::XMFLOAT4(1, 1, 1, 1);

	m_Vertex[0].uv = { 0, 0 };
	m_Vertex[1].uv = { 1, 0 };
	m_Vertex[2].uv = { 0, 1 };
	m_Vertex[3].uv = { 1, 1 };

	long idx[] = { 0,1,2, 1,3,2 };

	// バッファ作成
	m_Buffer.CreateVertexBuffer(m_Vertex, sizeof(Vertex), 4, true);
	m_Buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));

	m_r = m_g = m_b = m_a = 1;
	m_fSplitX = m_fSplitY = 1;
	m_fTexCoordX = m_fTexCoordY = 0;

	m_pTexture = nullptr;

	m_bBillboard = false;
	m_bParallel = false;
	m_bZSort = false;

	m_AnimeStatus = ANIME::NO;
}

//==================================================
// 終了
//==================================================
void Pol2D::Uninit()
{
	delete[] m_Vertex;
}

//==================================================
// 更新
//==================================================
void Pol2D::Update()
{
	// アニメ更新
	if (m_AnimeStatus == ANIME::PLAY)
	{
		// 切り替え
		m_nCount++;
		if (m_nCount > m_nPace)
		{
			// アニメが一周した
			if ((m_fTexCoordX == m_nEndX) && (m_fTexCoordY == m_nEndY))
			{
				if (m_bLoop)	// ループする
				{
					m_fTexCoordX = (float)m_nStartX;
					m_fTexCoordY = (float)m_nStartY;
				}
				else m_AnimeStatus = ANIME::END;
			}
			else
			{
				// 次の座標
				m_fTexCoordX++;

				// 端までいった
				if (m_fTexCoordX >= m_fSplitX)
				{
					m_fTexCoordX = 0.0f;
					m_fTexCoordY += 1.0f;
				}
				// 終端までいった
				if (m_fTexCoordY >= m_fSplitY)
					m_fTexCoordY = 0.0f;
			}

			// カウントリセット
			m_nCount = 0;
		}
	}

	// UV座標反映
	float w = 1.0f / m_fSplitX; float h = 1.0f / m_fSplitY;
	float TexX = w * m_fTexCoordX; float TexY = h * m_fTexCoordY;
	m_Vertex[0].uv = { TexX    , TexY };
	m_Vertex[1].uv = { TexX + w, TexY };
	m_Vertex[2].uv = { TexX    , TexY + h };
	m_Vertex[3].uv = { TexX + w, TexY + h };
	// 色反映
	for (int i = 0; i < 4; i++)
		m_Vertex[i].color = { m_r, m_g, m_b, m_a };

}

//==================================================
// 描画
//==================================================
void Pol2D::Draw()
{
	// 逆行列取得
	if (m_bBillboard)
	{
		DirectX::XMMATRIX InvCamera = DirectX::XMMatrixInverse(0, CAMERA->m_ViewMatrix);
		DirectX::XMFLOAT4X4 mat;
		DirectX::XMStoreFloat4x4(&mat, InvCamera);
		mat._41 = 0; mat._42 = 0; mat._43 = 0;
		InvCamera = DirectX::XMLoadFloat4x4(&mat);

		Float3 Size = m_Transform.Size * 0.5f;
		SHADER->SetWorld(
			InvCamera
			* DirectX::XMMatrixScaling(Size.x, Size.y, Size.z)
			* DirectX::XMMatrixRotationX(m_Transform.Rotate.x)
			* DirectX::XMMatrixRotationY(m_Transform.Rotate.y)
			* DirectX::XMMatrixRotationZ(m_Transform.Rotate.z)
			* DirectX::XMMatrixTranslation(m_Transform.Position.x, m_Transform.Position.y, m_Transform.Position.z));
	}
	else if (m_bParallel)
	{
		SHADER->SetWorld(
			DirectX::XMMatrixScaling(m_Transform.Size.x, m_Transform.Size.y, 0)
			* DirectX::XMMatrixRotationX(m_Transform.Rotate.x)
			* DirectX::XMMatrixRotationY(m_Transform.Rotate.y)
			* DirectX::XMMatrixRotationZ(m_Transform.Rotate.z)
			* DirectX::XMMatrixTranslation(m_Transform.Position.x, m_Transform.Position.y, 0));
	}
	else
	{
		SHADER->SetWorld(
			DirectX::XMMatrixScaling(m_Transform.Size.x, m_Transform.Size.y, 0)
			* DirectX::XMMatrixRotationX(m_Transform.Rotate.x)
			* DirectX::XMMatrixRotationY(m_Transform.Rotate.y)
			* DirectX::XMMatrixRotationZ(m_Transform.Rotate.z)
			* DirectX::XMMatrixTranslation(m_Transform.Position.x, m_Transform.Position.y, m_Transform.Position.z));
	}

	SHADER->Bind(VS_WORLD, PS_UNLIT);
	SHADER->SetTexture(m_pTexture);

	// 平行投影
	if (m_bParallel) CAMERA->Bind(true);
	if (m_bZSort) GET_DX->SetRenderTarget(false);

	m_Buffer.Write(m_Vertex);
	m_Buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (m_bZSort) GET_DX->SetRenderTarget(true);
	if (m_bParallel) CAMERA->Bind(false);

}

//==================================================
// テクスチャの設定
//--------------------------------------------------
// 引数		: ファイル名
//==================================================
void Pol2D::SetTexture(const char* szFileName)
{
	if (szFileName == nullptr) m_pTexture = nullptr;
	else m_pTexture = TEXTURE->Load(szFileName);
}

//==================================================
// アニメーションの設定
//--------------------------------------------------
// 引数1	: 開始UV座標
// 引数2	: 枚数
// 引数3	: アニメ速度
// 引数4	: ループ (デフォルトでtrue)
//==================================================
void Pol2D::SetAnime(int Start, int Num, int Pace, bool Loop)
{
	if (m_AnimeStatus == ANIME::PLAY) return;

	// 開始位置
	m_nStartX = Start % int(m_fSplitX);
	m_nStartY = int(Start / m_fSplitX);
	m_fTexCoordX = (float)m_nStartX;
	m_fTexCoordY = (float)m_nStartY;
	// 終了位置
	m_nEndX = (m_nStartX + (Num - 1)) % (int)m_fSplitX;
	m_nEndY = (int)(m_nStartY + ((m_nStartX + (Num - 1)) / m_fSplitY));

	m_nPace = Pace;
	m_bLoop = Loop;
	m_AnimeStatus = ANIME::PLAY;
	m_nCount = 0;
}
