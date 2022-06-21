//--- インクルード
#include "Effect.h"
#include "GameScene.h"
#include "Transform.h"
#include "Shader.h"

//==================================================
// 初期化
//==================================================
void Effect::Init()
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		m_Particle[i].Polygon.Init();
		m_Particle[i].Polygon.m_bBillboard = true;
		m_Particle[i].Polygon.m_bZSort = false;

		m_Particle[i].nLife = 0;
		m_Particle[i].bExist = false;
	}
}

//==================================================
// 終了
//==================================================
void Effect::Uninit()
{
	for (int i = 0; i < MAX_PARTICLE; i++)
		m_Particle[i].Polygon.Uninit();
}

//==================================================
// 更新
//==================================================
void Effect::Update()
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (!m_Particle[i].bExist) continue;

		// 摩擦
		if (m_Particle[i].Kind != SMOKE)
			m_Particle[i].Polygon.m_Transform.Move *= 0.99f;
		// 重力
		m_Particle[i].Polygon.m_Transform.Move.y -= m_Particle[i].fMass;
		// 反射
		if (m_Particle[i].Polygon.m_Transform.Position.y < 0)
			m_Particle[i].Polygon.m_Transform.Move.y *= -0.9f;

		// 特殊処理
		if (m_Particle[i].Kind == SMOKE) m_Particle[i].Polygon.m_Transform.Size += 2.0f;
		if (m_Particle[i].Kind == ABSORB) m_Particle[i].Polygon.m_Transform.Size -= 0.3f;
		if (m_Particle[i].Kind == HIT) m_Particle[i].Polygon.m_a = m_Particle[i].nLife / 60.0f;

		// 移動量更新
		m_Particle[i].Polygon.m_Transform.Position += m_Particle[i].Polygon.m_Transform.Move;

		// 寿命
		--m_Particle[i].nLife;
		if (m_Particle[i].nLife == 0) m_Particle[i].bExist = false;

		m_Particle[i].Polygon.Update();
	}
}

//==================================================
// 描画
//==================================================
void Effect::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (!m_Particle[i].bExist) continue;

		if (m_Particle[i].Kind == POWER3) GET_DX->SetBlendState(BLEND::ADD);
		m_Particle[i].Polygon.Draw();
		GET_DX->SetBlendState(BLEND::ALPHA);
	}
}

//==================================================
// パーティクル生成
//--------------------------------------------------
// 引数1	: 座標
// 引数2	: エフェクトの種類
//==================================================
void Effect::SetEffect(Float3 Pos, KIND Kind)
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (m_Particle[i].bExist) continue;
		switch (Kind)
		{
		case PLAYER:
			m_Particle[i].Polygon.SetTexture(TEX_PNG("Tuti"));

			// プレイヤーの足元から周りに
			m_Particle[i].Polygon.m_Transform.Position = Pos;
			m_Particle[i].Polygon.m_Transform.Size = 2;
			m_Particle[i].Polygon.m_Transform.Move.x = float(rand() % 30 - 15) / 10.0f;
			m_Particle[i].Polygon.m_Transform.Move.z = float(rand() % 30 - 15) / 10.0f;
			m_Particle[i].Polygon.m_Transform.Move.y = float(rand() % 3 + 1) * 2.0f;
			m_Particle[i].nLife = 50;
			m_Particle[i].fMass = 0.1f;

			m_Particle[i].Polygon.m_r =
				m_Particle[i].Polygon.m_g =
				m_Particle[i].Polygon.m_b = 1.0f - (rand() % 6 / 10.0f);

			m_Particle[i].Kind = PLAYER;
			m_Particle[i].bExist = true;

			break;
		case CIRCLE:
			m_Particle[i].Polygon.SetTexture(nullptr);

			// 境界判定の可視化
			m_Particle[i].Polygon.m_Transform.Position = Pos;
			m_Particle[i].Polygon.m_Transform.Size = 20;
			m_Particle[i].Polygon.m_Transform.Move.y = float(rand() % 10 / 10 + 1.0f);
			m_Particle[i].nLife = 50;
			m_Particle[i].fMass = 0;
			m_Particle[i].Polygon.m_r =
				m_Particle[i].Polygon.m_g =
				m_Particle[i].Polygon.m_b = 1.0f;
			m_Particle[i].Polygon.m_a = 0.5f;

			m_Particle[i].Kind = CIRCLE;
			m_Particle[i].bExist = true;

			break;

		case SMOKE:
			m_Particle[i].Polygon.SetTexture(TEX_PNG("Smoke"));

			m_Particle[i].Polygon.m_Transform.Position = Pos;
			m_Particle[i].Polygon.m_Transform.Position.y += 10;
			m_Particle[i].Polygon.m_Transform.Size = 5;
			m_Particle[i].Polygon.m_Transform.Move.x = float((rand() % 10 - 5.0f) / 20.0f);
			m_Particle[i].Polygon.m_Transform.Move.y = float(rand() % 5 / 10.0f + 0.5f);
			m_Particle[i].nLife = 60;
			m_Particle[i].fMass = 0;
			m_Particle[i].Polygon.m_a = 0.5f;
			m_Particle[i].Polygon.m_r = 0.8f;
			m_Particle[i].Polygon.m_g = 0.5f;
			m_Particle[i].Polygon.m_b = 0.2f;

			m_Particle[i].Kind = SMOKE;
			m_Particle[i].bExist = true;

			break;

		case POWER1:
		{
			m_Particle[i].Polygon.SetTexture(TEX_PNG("Smoke"));
			m_Particle[i].Polygon.m_Transform.Position = Pos;
			m_Particle[i].Polygon.m_Transform.Position.y;
			m_Particle[i].Polygon.m_Transform.Size = 30;
			m_Particle[i].nLife = 10;
			m_Particle[i].fMass = 0;
			Float3 PlayerPos = GameScene::GetObjectList()->Get(OBJECT::PLAYER)->Get<Transform>()->Position;
			PlayerPos.y += 30;
			m_Particle[i].Polygon.m_Transform.Move = (PlayerPos - Pos) / (float)m_Particle[i].nLife;
			m_Particle[i].Polygon.m_a = 0.6f;
			m_Particle[i].Polygon.m_r = 1.0f;
			m_Particle[i].Polygon.m_g = 1.0f;
			m_Particle[i].Polygon.m_b = 1.0f;
			m_Particle[i].Kind = POWER1;
			m_Particle[i].bExist = true;

			break;
		}
		case POWER2:
		{
			m_Particle[i].Polygon.SetTexture(TEX_PNG("Smoke"));
			m_Particle[i].Polygon.m_Transform.Position = Pos;
			m_Particle[i].Polygon.m_Transform.Position.y;
			m_Particle[i].Polygon.m_Transform.Size = 30;
			m_Particle[i].nLife = 10;
			m_Particle[i].fMass = 0;
			Float3 PlayerPos = GameScene::GetObjectList()->Get(OBJECT::PLAYER)->Get<Transform>()->Position;
			PlayerPos.y += 30;
			m_Particle[i].Polygon.m_Transform.Move = (PlayerPos - Pos) / (float)m_Particle[i].nLife;
			m_Particle[i].Polygon.m_a = 0.6f;
			m_Particle[i].Polygon.m_r = 0.8f;
			m_Particle[i].Polygon.m_g = 0.8f;
			m_Particle[i].Polygon.m_b = 0.8f;
			m_Particle[i].Kind = POWER2;
			m_Particle[i].bExist = true;

			break;
		}
		case POWER3:
		{
			m_Particle[i].Polygon.SetTexture(TEX_PNG("Smoke"));
			m_Particle[i].Polygon.m_Transform.Position = Pos;
			m_Particle[i].Polygon.m_Transform.Position.y;
			m_Particle[i].Polygon.m_Transform.Size = 30;
			m_Particle[i].nLife = 10;
			m_Particle[i].fMass = 0;
			Float3 PlayerPos = GameScene::GetObjectList()->Get(OBJECT::PLAYER)->Get<Transform>()->Position;
			PlayerPos.y += 30;
			m_Particle[i].Polygon.m_Transform.Move = (PlayerPos - Pos) / (float)m_Particle[i].nLife;
			m_Particle[i].Polygon.m_a = 0.6f;
			m_Particle[i].Polygon.m_r = 0.7f;
			m_Particle[i].Polygon.m_g = 0.7f;
			m_Particle[i].Polygon.m_b = 0.3f;
			m_Particle[i].Kind = POWER3;
			m_Particle[i].bExist = true;

			break;
		}
		case POWER4:
		{
			m_Particle[i].Polygon.SetTexture(TEX_PNG("Smoke"));
			m_Particle[i].Polygon.m_Transform.Position = Pos;
			m_Particle[i].Polygon.m_Transform.Position.y;
			m_Particle[i].Polygon.m_Transform.Size = 30;
			m_Particle[i].nLife = 10;
			m_Particle[i].fMass = 0;
			Float3 PlayerPos = GameScene::GetObjectList()->Get(OBJECT::PLAYER)->Get<Transform>()->Position;
			PlayerPos.y += 30;
			m_Particle[i].Polygon.m_Transform.Move = (PlayerPos - Pos) / (float)m_Particle[i].nLife;
			m_Particle[i].Polygon.m_a = 0.6f;
			m_Particle[i].Polygon.m_r = 1.0f;
			m_Particle[i].Polygon.m_g = 0.6f;
			m_Particle[i].Polygon.m_b = 0.0f;
			m_Particle[i].Kind = POWER4;
			m_Particle[i].bExist = true;

			break;
		}
		case POWER5:
		{
			m_Particle[i].Polygon.SetTexture(TEX_PNG("Smoke"));
			m_Particle[i].Polygon.m_Transform.Position = Pos;
			m_Particle[i].Polygon.m_Transform.Position.y;
			m_Particle[i].Polygon.m_Transform.Size = 30;
			m_Particle[i].nLife = 10;
			m_Particle[i].fMass = 0;
			Float3 PlayerPos = GameScene::GetObjectList()->Get(OBJECT::PLAYER)->Get<Transform>()->Position;
			PlayerPos.y += 30;
			m_Particle[i].Polygon.m_Transform.Move = (PlayerPos - Pos) / (float)m_Particle[i].nLife;
			m_Particle[i].Polygon.m_a = 0.6f;
			m_Particle[i].Polygon.m_r = 0.9f;
			m_Particle[i].Polygon.m_g = 0.2f;
			m_Particle[i].Polygon.m_b = 0.2f;
			m_Particle[i].Kind = POWER5;
			m_Particle[i].bExist = true;

			break;
		}
		case ABSORB:
			m_Particle[i].Polygon.SetTexture(TEX_PNG("Smoke"));

			m_Particle[i].Polygon.m_Transform.Position = GameScene::GetObjectList()->Get(OBJECT::CORE)->Get<Transform>()->Position;
			m_Particle[i].Polygon.m_Transform.Position.x += 10;
			m_Particle[i].Polygon.m_Transform.Size = 30;
			m_Particle[i].nLife = 60;
			m_Particle[i].fMass = 0;
			m_Particle[i].Polygon.m_Transform.Move = (Pos - m_Particle[i].Polygon.m_Transform.Position) / (float)m_Particle[i].nLife;
			m_Particle[i].Polygon.m_a = 0.8f;
			m_Particle[i].Polygon.m_r = 0.3f;
			m_Particle[i].Polygon.m_g = 0.3f;
			m_Particle[i].Polygon.m_b = 1.0f;

			m_Particle[i].Kind = ABSORB;
			m_Particle[i].bExist = true;

			break;

		case HIT:
		{
			m_Particle[i].Polygon.SetTexture(TEX_PNG("Star"));

			m_Particle[i].Polygon.m_Transform.Position = Pos;
			int ran = rand() % 20 + 10;
			m_Particle[i].Polygon.m_Transform.Size.x = ran * 1.0f;
			m_Particle[i].Polygon.m_Transform.Size.y = ran * 0.9f;
			m_Particle[i].Polygon.m_Transform.Size.z = ran * 1.6f;
			m_Particle[i].nLife = 60;
			m_Particle[i].Polygon.m_Transform.Move.x = float(rand() % 30 - 15) / 10.0f;
			m_Particle[i].Polygon.m_Transform.Move.z = float(rand() % 30 - 15) / 10.0f;
			m_Particle[i].Polygon.m_Transform.Move.y = float(rand() % 3 + 1) * -1.0f;
			m_Particle[i].fMass = -0.02f;
			m_Particle[i].Polygon.m_a = 1.0f;
			m_Particle[i].Polygon.m_r = 1.0f;
			m_Particle[i].Polygon.m_g = 1.0f;
			m_Particle[i].Polygon.m_b = 1.0f;

			m_Particle[i].Kind = HIT;
			m_Particle[i].bExist = true;

			break;
		}
		default:
			break;
		}
		
		break;
	}

}

