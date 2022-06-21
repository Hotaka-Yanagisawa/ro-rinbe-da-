//--- インクルード
#include "Model.h"
#include "ModelManager.h"
#include "Shader.h"
#include "SelectScene.h"

//--- 静的メンバ変数
int Model::m_nInstCount[MULTI_MODEL_NUM];
FBXPlayer* Model::m_MultiModel[MULTI_MODEL_NUM];
DrawBuffer* Model::m_pMultiBuffer[MULTI_MODEL_NUM];

//==================================================
// 初期化
//==================================================
void Model::Init()
{
	m_Model = nullptr;
	m_Transform = m_Parent->Get<Transform>();

	m_bMulti = false;
	m_nMultiNum = 0;
	//if (m_Parent->m_Tag == OBJECT::BTREE)
	//{
	//	m_bMulti = true;
	//	m_nMultiNum = m_nInstCount[MI_BTREE];
	//}
	//else if (m_Parent->m_Tag == OBJECT::ENEMY1)
	//{
	//	m_bMulti = true;
	//	m_nMultiNum = m_nInstCount[MI_ENEMY1];
	//}

	// 色変え用
	m_fDif = 1.0f - (rand() % 7 / 10.0f);
}

//==================================================
// 描画
//==================================================
void Model::Draw()
{
	// 複数描画
	//if (m_bMulti)
	//{
	//	if (m_Parent->m_Tag == OBJECT::BTREE)
	//	{
	//		SHADER->SetWorldMulti(m_nMultiNum + 0,
	//			DirectX::XMMatrixScaling(m_Transform->Size.x * 0.1f, m_Transform->Size.y * 0.1f, m_Transform->Size.z * 0.1f)
	//			* DirectX::XMMatrixRotationX(m_Transform->Rotate.x)
	//			* DirectX::XMMatrixRotationY(m_Transform->Rotate.y)
	//			* DirectX::XMMatrixRotationZ(m_Transform->Rotate.z)
	//			* DirectX::XMMatrixTranslation(m_Transform->Position.x, m_Transform->Position.y, m_Transform->Position.z)
	//		);
	//	}
	//	//else if (m_Parent->m_Tag == OBJECT::ENEMY1)
	//	//{
	//	//	SHADER->SetWorldMulti(m_nMultiNum + m_nInstCount[MI_BTREE],
	//	//		DirectX::XMMatrixScaling(m_Transform->Size.x * 0.1f, m_Transform->Size.y * 0.1f, m_Transform->Size.z * 0.1f)
	//	//		* DirectX::XMMatrixRotationX(m_Transform->Rotate.x)
	//	//		* DirectX::XMMatrixRotationY(m_Transform->Rotate.y)
	//	//		* DirectX::XMMatrixRotationZ(m_Transform->Rotate.z)
	//	//		* DirectX::XMMatrixTranslation(m_Transform->Position.x, m_Transform->Position.y, m_Transform->Position.z)
	//	//	);
	//	//}
	//	return;
	//}

	if (m_Parent->m_Tag == OBJECT::TREE) SHADER->SetLightDiffuse(DirectX::XMFLOAT4(m_fDif, m_fDif, 1.0f, 1.0f));
	SHADER->SetLightDiffuse(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	if (m_Model->IsPlay()) SHADER->Bind(VS_ANIMATION, PS_LAMBERT);
	else SHADER->Bind(VS_WORLD, PS_LAMBERT);

	if (m_Parent->m_Tag == OBJECT::FIELD)
	{
		SHADER->Bind(VS_WORLD, PS_FIELD);
		if (SelectScene::m_nSelect == 0) SHADER->SetPSVal(DirectX::XMFLOAT4(0, 1, 0.5f, 1));
		if (SelectScene::m_nSelect == 1) SHADER->SetPSVal(DirectX::XMFLOAT4(1, 0.6f, 0.2f, 1));
		if (SelectScene::m_nSelect == 2) SHADER->SetPSVal(DirectX::XMFLOAT4(0.4f, 0.4f , 0.4f, 1));
	}
	if(m_Parent->m_Tag == OBJECT::PLAYER) SHADER->Bind(VS_WORLD, PS_PLAYER);

	SHADER->SetWorld(
		DirectX::XMMatrixScaling(m_Transform->Size.x * 0.1f, m_Transform->Size.y * 0.1f, m_Transform->Size.z * 0.1f)
		* DirectX::XMMatrixRotationX(m_Transform->Rotate.x)
		* DirectX::XMMatrixRotationY(m_Transform->Rotate.y)
		* DirectX::XMMatrixRotationZ(m_Transform->Rotate.z)
		* DirectX::XMMatrixTranslation(m_Transform->Position.x, m_Transform->Position.y, m_Transform->Position.z)
	);

	int meshNum = m_Model->GetMeshNum();
	for (int i = 0; i < meshNum; ++i)
	{
		if (m_Model->IsPlay()) SHADER->SetAnimation(m_Model->GetAnimeMatrix(i), m_Model->GetAnimeMatrixNum(i));

		SHADER->SetTexture(m_Model->GetTexture(i));

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	SHADER->Bind(VS_WORLD, PS_LAMBERT);
}

//==================================================
// 対応したモデル読み込み
//--------------------------------------------------
// 引数1	: キューブフラグ デフォルト:false
//==================================================
void Model::LoadModel(bool Load)
{
	// キューブ
	if (!Load)
	{
		m_Model = MODEL->Load(FILE_MODEL("Debug"));
	}
	else
	{
		// 種類ごとのモデル
		switch (m_Parent->m_Tag)
		{
		case OBJECT::PLAYER:
			m_Model = MODEL->Load(FILE_MODEL("Tornado/Tornado"));
			break;
		case OBJECT::ENEMY1:
			//++m_nInstCount[MI_ENEMY1]; return;
			m_Model = MODEL->Load(FILE_MODEL("Enemy/Mappie_Base"));
			if(!m_Model->IsPlay())
				m_Model->Play(m_Model->LoadAnimation(FILE_MODEL("Enemy/Mappie_Walk")), true);
			break;
		case OBJECT::ENEMY2:
		case OBJECT::ENEMY3:
			m_Model = MODEL->Load(FILE_MODEL("Enemy/Gotudan_Base"));
			if (!m_Model->IsPlay())
				m_Model->Play(m_Model->LoadAnimation(FILE_MODEL("Enemy/Gotudan_Walk")), true);
			break;
		case OBJECT::TREE:
			m_Model = MODEL->Load(FILE_MODEL("Gimmick/Tree"));
			break;
		case OBJECT::BTREE:
			m_Model = MODEL->Load(FILE_MODEL("Gimmick/Tree"));
			//++m_nInstCount[MI_BTREE]; return;
			break;
		case OBJECT::BOSS:
			m_Model = MODEL->Load(FILE_MODEL("Enemy/Ship"));
			//m_Model->Play(m_Model->LoadAnimation(FILE_MODEL("Enemy/Ship_Roll")), true);
			break;
		case OBJECT::FIELD:
			m_Model = MODEL->Load(FILE_MODEL("Field/Steppe"));
			break;
		case OBJECT::TEMPLE:
			m_Model = MODEL->Load(FILE_MODEL("Temple/Base"));
			break;
		case OBJECT::PILLAR:
			m_Model = MODEL->Load(FILE_MODEL("Temple/Pillar"));
			break;
		case OBJECT::CORE:
			m_Model = MODEL->Load(FILE_MODEL("Temple/Core"));
			break;
		case OBJECT::FLOOR1:
			m_Model = MODEL->Load(FILE_MODEL("Temple/Floor1"));
			break;
		case OBJECT::FLOOR2:
			m_Model = MODEL->Load(FILE_MODEL("Temple/Floor2"));
			break;
		case OBJECT::FLOOR3:
			m_Model = MODEL->Load(FILE_MODEL("Temple/Floor3"));
			break;
		default:
			break;
		}
	}

	// モデルのメッシュ数だけ頂点バッファ作成
	int meshNum = m_Model->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; ++i)
	{
		// メッシュごとに頂点バッファ作成
		m_pBuffer[i].CreateVertexBuffer(
			m_Model->GetVertexData(i),
			m_Model->GetVertexSize(i),
			m_Model->GetVertexCount(i)
		);
		// インデックスバッファ作成
		m_pBuffer[i].CreateIndexBuffer(
			m_Model->GetIndexData(i),
			m_Model->GetIndexCount(i)
		);
	}
}

//==================================================
// マルチ対象モデル読み込み
//==================================================
void Model::LoadMultiModel()
{
	m_MultiModel[MI_BTREE] = MODEL->Load(FILE_MODEL("Gimmick/Tree"));
	int meshNum = m_MultiModel[MI_BTREE]->GetMeshNum();
	m_pMultiBuffer[MI_BTREE] = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; ++i)
	{
		m_pMultiBuffer[MI_BTREE][i].CreateVertexBuffer(
			m_MultiModel[MI_BTREE]->GetVertexData(i),
			m_MultiModel[MI_BTREE]->GetVertexSize(i),
			m_MultiModel[MI_BTREE]->GetVertexCount(i));
		m_pMultiBuffer[MI_BTREE][i].CreateIndexBuffer(
			m_MultiModel[MI_BTREE]->GetIndexData(i),
			m_MultiModel[MI_BTREE]->GetIndexCount(i));
	}
	
	//m_MultiModel[MI_ENEMY1] = MODEL->Load(FILE_MODEL("Enemy/Mappie_Base"));
	//meshNum = m_MultiModel[MI_ENEMY1]->GetMeshNum();
	//m_pMultiBuffer[MI_ENEMY1] = new DrawBuffer[meshNum];
	//for (int i = 0; i < meshNum; ++i)
	//{
	//	m_pMultiBuffer[MI_ENEMY1][i].CreateVertexBuffer(
	//		m_MultiModel[MI_ENEMY1]->GetVertexData(i),
	//		m_MultiModel[MI_ENEMY1]->GetVertexSize(i),
	//		m_MultiModel[MI_ENEMY1]->GetVertexCount(i));
	//	m_pMultiBuffer[MI_ENEMY1][i].CreateIndexBuffer(
	//		m_MultiModel[MI_ENEMY1]->GetIndexData(i),
	//		m_MultiModel[MI_ENEMY1]->GetIndexCount(i));
	//}
}

//==================================================
// 一斉描画
//==================================================
void Model::DrawMultiModel()
{
	// 木
	SHADER->Bind(VS_MULTI, PS_LAMBERT);
	int meshNum = m_MultiModel[MI_BTREE]->GetMeshNum();
	for (int i = 0; i < meshNum; ++i)
	{
		SHADER->SetTexture(m_MultiModel[MI_BTREE]->GetTexture(i));
		m_pMultiBuffer[MI_BTREE]->MultiDraw(m_nInstCount[MI_BTREE], 0);
	}
	//// 敵
	//meshNum = m_MultiModel[MI_ENEMY1]->GetMeshNum();
	//for (int i = 0; i < meshNum; ++i)
	//{
	//	SHADER->SetTexture(m_MultiModel[MI_ENEMY1]->GetTexture(i));
	//	m_pMultiBuffer[MI_ENEMY1]->MultiDraw(m_nInstCount[MI_ENEMY1], m_nInstCount[MI_BTREE]);
	//}
}
