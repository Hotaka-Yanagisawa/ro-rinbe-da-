//--- インクルード
#include "Fly.h"
#include "Object.h"
#include "Shader.h"
#include "State/EnemyPlayer.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "SelectScene.h"

//==================================================
// 初期化
//==================================================
void Fly::Init()
{
	m_bFlag = false;
	m_Transform = m_Parent->Get<Transform>();
	m_Vitality = m_Parent->Get<Vitality>();

	m_fAngle = 720.0f * 3.1415f / 180;
	m_fRadius = 200;
	m_nCount = 0;

	m_pTexture = TEXTURE->Load(TEX_PNG("Shadow"));

	struct Vertex
	{
		float pos[3];
		float color[4];
		float uv[2];
	};
	Vertex vtx[] = {
		{{-m_Transform->Size.x, 0, m_Transform->Size.z}, {1,1,1,1}, {0,0}},
		{{ m_Transform->Size.x, 0, m_Transform->Size.z}, {1,1,1,1}, {1,0}},
		{{-m_Transform->Size.x, 0,-m_Transform->Size.z}, {1,1,1,1}, {0,1}},
		{{ m_Transform->Size.x, 0,-m_Transform->Size.z}, {1,1,1,1}, {1,1}},
	};
	// インデックスデータ
	long idx[] = { 0,1,2, 1,3,2 };

	// バッファ作成
	m_Buffer.CreateVertexBuffer(vtx, sizeof(Vertex), sizeof(vtx) / sizeof(Vertex));
	m_Buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));

	m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/Hit_1.mp3", false);

	m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
	m_SE.m_pSpeaker->SetVolume(0.0f);
	m_SE.m_bFade = false;
	m_SE.m_bFade = m_SE.Fade(0.0f, 0.1f);

	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/SE/UFO.mp3", false);
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
	m_Sound.m_bFade = false;
	m_Sound.m_bFade = m_Sound.Fade(0.0f, 0.1f);
}

//==================================================
// 更新
//==================================================
void Fly::Update()
{
	//Fadeが呼ばれたら機能する
	m_SE.Update();
	m_Sound.Update();
	float Speed = 1.f;
	float x = 0;
	float z = 0;
	float AddSpeed = 0;
	static bool flag = false;
	static float Angle;
	static int around = 360;
	static int Add;
	switch (SelectScene::m_nSelect)
	{
	case 0:
		// 原点を中心に回転
		if ((m_fAngle * 180.0f / 3.1415f) > 360 * 8) flag = true;
		if ((m_fAngle * 180.0f / 3.1415f) < 360 * 0) flag = false;
		if ((m_fAngle * 180.0f / 3.1415f) < 360 * 2) AddSpeed = 1.0f;

		if (!flag)
		{
			m_fAngle += (Speed + AddSpeed) * 3.1415f / 180;
		}
		else
		{
			m_fAngle -= (Speed + AddSpeed) * 3.1415f / 180;
		}

		x = (sinf(m_fAngle) + (m_fAngle * cosf(m_fAngle))) * 5;
		z = (cosf(m_fAngle) - (m_fAngle * sinf(m_fAngle))) * 5;


		break;
	case 1:
		m_fAngle += Speed * 3.1415f / 180;

		x = sinf(m_fAngle) * sinf(m_fAngle) * sinf(m_fAngle) * m_fRadius;
		z = cosf(m_fAngle) * cosf(m_fAngle) * cosf(m_fAngle) * m_fRadius;
		break;
	case 2:
		Speed = 0.3f;
		m_fAngle += Speed * 3.1415f / 180;

		if (around >= 360)
		{
			around = 0;
			Add = rand() % 7 + 3;
		}
		around += Add;
		Angle += Add * 3.1415f / 180;
		float AddRadiusX = cosf(Angle) * 50;
		float AddRadiusZ = sinf(Angle) * 50;

		x = sinf(m_fAngle) * m_fRadius + AddRadiusX;
		z = cosf(m_fAngle) * m_fRadius + AddRadiusZ;
		break;
	}

	m_Transform->Position.x = x;
	m_Transform->Position.z = z;
	// 自転
	m_Transform->Rotate.y += Speed * 3.1415f / 180;

	// 揺れる
	if (m_nCount > 0)
	{
		m_Transform->Rotate.x = sinf(m_nCount * 0.1f) / 3;
		m_Transform->Rotate.z = cosf(m_nCount * 0.1f) / 3;
		m_nCount--;
	}
	else m_Transform->Rotate = 0;

	if (GameScene::m_Step == GAMESCENE::CLEAR)
	{
		if (!m_bFlag)
		{
			m_bFlag = true;
			m_nCount = 100;
			m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/SE/nyu3.mp3", false);
			m_Sound.m_pBuffer->LoopCount = 5;
			m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
			m_Sound.m_pSpeaker->SetVolume(0.0f);
			m_Sound.m_bFade = false;
			m_Sound.m_bFade = m_Sound.Fade(2.0f, 0.1f);
		}
		if (m_Transform->Size.x > 0.0f)
			m_Transform->Size -= 0.10f;
		m_Transform->Position += 1.2f;


		m_Transform->Rotate.x = sinf(m_nCount * 0.2f) / 3;
		m_Transform->Rotate.z = cosf(m_nCount * 0.2f) / 3;
	}

	// 煙
	//static int time;
	//if (++time % 8 == 0) EFFECT.SetEffect(m_Transform->Position, SMOKE);
}

//==================================================
// 描画
//==================================================
void Fly::Draw()
{
	// 影
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(m_Transform->Size.x * 2, m_Transform->Size.y, m_Transform->Size.z * 2)
		* DirectX::XMMatrixRotationY(m_Transform->Rotate.y)
		* DirectX::XMMatrixTranslation(m_Transform->Position.x, 0.01f, m_Transform->Position.z)
	);

	SHADER->SetTexture(m_pTexture);

	m_Buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

//==================================================
// 衝突時
//==================================================
void Fly::OnCollisionEnter(Object* pObj)
{
	if ((pObj->m_Tag == OBJECT::ENEMY1) || (pObj->m_Tag == OBJECT::ENEMY2) || (pObj->m_Tag == OBJECT::ENEMY3)
		|| (pObj->m_Tag == OBJECT::TREE))
	{
		m_Vitality->m_fHp -= pObj->Get<EnemyPlayer>()->m_fAttack;
		m_nCount = 30;

		int randomNum = rand() % 3;
		if (randomNum == 0)	m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/Hit_1.mp3", false);
		else if (randomNum == 1)	m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/Hit_2.mp3", false);
		else if (randomNum == 2)	m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/Hit_3.mp3", false);
		else
		{
			m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/Hit_1.mp3", false);
		}
		m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
		m_SE.m_pSpeaker->SetVolume(0.0f);
		m_SE.m_bFade = false;
		m_SE.m_bFade = m_SE.Fade(2.0f, 0.1f);

		for (int i = 0; i < 5; ++i)
			EFFECT.SetEffect(m_Transform->Position, HIT);
	}
}
