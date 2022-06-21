//--- インクルード
#include "Control.h"
#include "Object.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Keyboard.h"
#include "Controller.h"
#include "Camera.h"
#include "Field.h"
#include "State/GameState.h"
#include "ObjectList.h"
#include "State/EnemyPlayer.h"

//==================================================
// 初期化
//==================================================
void Control::Init()
{
	m_Transform = m_Parent->Get<Transform>();
	m_Symbol.Init();
	m_Symbol.SetTexture(TEX_PNG("Title_Pattern"));
	m_Symbol.m_Transform.Position = m_Transform->Position;
	m_Symbol.m_Transform.Position.y = 0.5f;
	m_Symbol.m_Transform.Size = { 176,124,124 };
	m_Symbol.m_Transform.Size *= 0.2f;
	m_Symbol.m_Transform.Rotate.x = 90 * 3.141592f / 180.0f;

	m_Aim.Init();
	m_Aim.m_bParallel = true;
	m_Aim.SetTexture(TEX_PNG("Mark"));
	m_Aim.m_Transform.Position = { 0, 0, 0 };
	m_Aim.m_Transform.Size = { 160, 150, 0 };
	m_Aim.m_a = 0.8f;
}

//==================================================
// 終了
//==================================================
void Control::Uninit()
{
	//m_Parent->Get<Soundplayer>()->Uninit();
	m_Symbol.Uninit();
	m_Aim.Uninit();
}

//==================================================
// 更新
//==================================================
void Control::Update()
{
	// 移動
	bool keyL = PAD->IsLStickLeft() | IsKeyPress('A');
	bool keyR = PAD->IsLStickRight() | IsKeyPress('D');
	bool keyU = PAD->IsLStickUp() | IsKeyPress('W');
	bool keyD = PAD->IsLStickDown() | IsKeyPress('S');

	//float fLength(0);
	//float fDirection(0);
	const float Friction = 0.99f;
	float fAcc = 0.01f;
	float limit = 100.0f;		// 移動量制限

	const float RAD = 3.141519f / 180.0f;

	float cameraAngle = Camera::GetInstance()->m_xzAngle + 90;
	//Camera::GetInstance()->m_State

	bool &Tracking = GameState::GetInstance()->m_bTracking;

	Transform* BossTrans = GameScene::GetObjectList()->Get(OBJECT::BOSS)->Get<Transform>();
	DirectX::XMMATRIX world =
		DirectX::XMMatrixTranslation(BossTrans->Position.x, BossTrans->Position.y, BossTrans->Position.z);
	DirectX::XMFLOAT4X4 wvp;

	world = CAMERA->TransWVP(world);
	DirectX::XMStoreFloat4x4(&wvp, world);
	m_Aim.m_Transform.Position.x = wvp._41;
	m_Aim.m_Transform.Position.y = wvp._42;

	if (IsKeyTrigger(VK_CONTROL) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_Y) || (Tracking == true))
	{
		Tracking = true;
		Float3 Distance =
			GameScene::GetObjectList()->Get(OBJECT::BOSS)->Get<Transform>()->Position - m_Transform->Position;
		Camera::GetInstance()->m_xzAngle = atan2f(Distance.z, Distance.x) * 180.0f / 3.141592f + (-90);
		m_Aim.Update();
		//m_Aim.m_Transform.Position = GameScene::GetObjectList()->Get(OBJECT::BOSS)->Get<Transform>()->Position;
		//obj->m_yAngle = -atan2f(Distance.y, Distance.x) * 180.0f / 3.141592f;
	}

	if (keyU)
	{
		m_Transform->Move.x += cosf(cameraAngle * RAD) * fAcc;
		m_Transform->Move.z += sinf(cameraAngle * RAD) * fAcc;
	}
	if (keyD)
	{
		m_Transform->Move.x -= cosf(cameraAngle * RAD) * fAcc;
		m_Transform->Move.z -= sinf(cameraAngle * RAD) * fAcc;
	}
	if (keyR)
	{
		m_Transform->Move.x += cosf((cameraAngle - 90) * RAD) * fAcc;
		m_Transform->Move.z += sinf((cameraAngle - 90) * RAD) * fAcc;
	}
	if (keyL)
	{
		m_Transform->Move.x -= cosf((cameraAngle - 90) * RAD) * fAcc;
		m_Transform->Move.z -= sinf((cameraAngle - 90) * RAD) * fAcc;
	}


	if (m_Transform->Move.x > limit)
	{
		m_Transform->Move.x = limit;
	}
	if (m_Transform->Move.x < -limit)
	{
		m_Transform->Move.x = -limit;
	}
	if (m_Transform->Move.z > limit)
	{
		m_Transform->Move.z = limit;
	}
	if (m_Transform->Move.z < -limit)
	{
		m_Transform->Move.z = -limit;
	}

	Float3 oldPos;
	oldPos = m_Transform->Position;

	// 座標を更新
	m_Transform->Position += m_Transform->Move;

	static char count(1);
	if (!(count % 5)) // 数フレームに一回摩擦処理
	{
		count = 1;
		m_Transform->Move *= Friction;
	}
	count++;

	float fieldSize = FIELD_RANGE;

	Float3 templepos(0);
	Float3 fieldsize(fieldSize, 0.1f, fieldSize);
	float x, z, r;
	x = templepos.x - m_Transform->Position.x;
	z = templepos.z - m_Transform->Position.z;
	r = ((fieldsize.x - m_Transform->Size.x)  * 0.5f) + ((fieldsize.z - m_Transform->Size.z) * 0.5f) -
		(m_Transform->Size.x * 0.5f) + (m_Transform->Size.z * 0.5f);

	Float3 templesize = GameScene::GetObjectList()->Get(OBJECT::TEMPLE)->Get<Transform>()->Size;
	//templesize *= 0.5f;

	if ((((templepos.x + templesize.x) >= m_Transform->Position.x && m_Transform->Position.x >= (templepos.x - templesize.x)) &&
		((templepos.z + templesize.z) >= m_Transform->Position.z && m_Transform->Position.z >= (templepos.z - templesize.z))) ||
		(!(x * x + z * z < r * r)))
	{
		m_Transform->Position = oldPos;
		m_Transform->Move = 0;
	}

	// 回る
	m_Transform->Rotate.y += 20 * 3.141592f / 180;

	m_Symbol.m_Transform.Position = m_Transform->Position;
	m_Symbol.m_Transform.Position.y = 0.5f;
	m_Symbol.m_Transform.Rotate.y =
		90 * 3.141592f / 180.0f -
		atan2f(m_Transform->Move.z, m_Transform->Move.x);
	m_Symbol.Update();

	static int time;
	if (EnemyPlayer::m_nLoadingNum == 0)
	{

	}
	else if (EnemyPlayer::m_nLoadingNum < 2)
	{
		KIND kind = POWER1;
		if (++time % 3 == 0)
			EFFECT.SetEffect({
			m_Transform->Position.x + rand() % 10 - 5,
			m_Transform->Position.y + 30 + rand() % 10 - 5,
			m_Transform->Position.z + rand() % 10 - 5 },
			kind);
	}
	else if (EnemyPlayer::m_nLoadingNum < 4)
	{
		KIND kind = POWER2;
		if (++time % 3 == 0)
			EFFECT.SetEffect({
			m_Transform->Position.x + rand() % 10 - 5,
			m_Transform->Position.y + 30 + rand() % 10 - 5,
			m_Transform->Position.z + rand() % 10 - 5 },
			kind);
	}
	else if (EnemyPlayer::m_nLoadingNum < 7)
	{
		KIND kind = POWER3;
		if (++time % 3 == 0)
			EFFECT.SetEffect({
			m_Transform->Position.x + rand() % 10 - 5,
			m_Transform->Position.y + 30 + rand() % 10 - 5,
			m_Transform->Position.z + rand() % 10 - 5 },
			kind);
	}
	else if (EnemyPlayer::m_nLoadingNum < 10)
	{
		KIND kind = POWER4;
		if (++time % 3 == 0)
			EFFECT.SetEffect({
			m_Transform->Position.x + rand() % 10 - 5,
			m_Transform->Position.y + 30 + rand() % 10 - 5,
			m_Transform->Position.z + rand() % 10 - 5 },
			kind);
	}
	if (EnemyPlayer::m_nLoadingNum == 10)
	{
		KIND kind = POWER5;
		if (++time % 3 == 0)
			EFFECT.SetEffect({
			m_Transform->Position.x + rand() % 10 - 5,
			m_Transform->Position.y + 30 + rand() % 10 - 5,
			m_Transform->Position.z + rand() % 10 - 5 },
			kind);
	}
}

void Control::Draw()
{
	m_Symbol.Draw();

	if (GameState::GetInstance()->m_bTracking) m_Aim.Draw();
}
