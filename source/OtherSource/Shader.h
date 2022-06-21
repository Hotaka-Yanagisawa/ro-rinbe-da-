//=======================================================================
// Shader.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// シェーダ関連
//-----------------------------------------------------------------------
// 更新履歴
//	2021/01/05	作成
//			15	ジオメトリシェーダ追加
//			19	定数バッファ用の列挙体追加
//			20	複数インスタンス
//			22	文字列で
//			
//=======================================================================
#pragma once

//--- インクルード
#include "DirectX.h"
#include <DirectXMath.h>

//--- 定数・マクロ
#define SHADER	(Shader::GetInstance())
#define MAX_INSTANCE_NUM	(500)

//--- 列挙体
// 頂点シェーダ
enum VertexShaderKind
{
	VS_WORLD,
	VS_ANIMATION,
	VS_MULTI,

	VS_KIND_MAX
};
// ジオメトリシェーダ
enum GeometryShaderKind
{
	GS_NORMAL,

	GS_KIND_MAX
};
// ピクセルシェーダ
enum PixelShaderKind
{
	PS_LAMBERT,
	PS_UNLIT,
	PS_FIELD,
	PS_PLAYER,

	PS_KIND_MAX
};

//--- 定数バッファ
// カメラ変換行列
struct VSBufferCamera
{
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 proj;
};
// マテリアル
struct PSBufferMaterial
{
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 ambient;
	DirectX::XMFLOAT4 specular;
	DirectX::XMFLOAT4 emissive;
};
// ライト
struct PSBufferLight
{
	DirectX::XMFLOAT4 dir;
	PSBufferMaterial material;
};
// カメラ
struct PSBufferCamera
{
	DirectX::XMFLOAT4 pos;
};

// 適当
struct PSBufferValue
{
	DirectX::XMFLOAT4 val;
};
struct GSBufferValue
{
	DirectX::XMFLOAT4 val;
};

// 定数バッファ種類
enum CBUF_KIND
{
	// 頂点シェーダ
	CBV_WORLD,
	CBV_CAMERA,
	CBV_ANIME,
	CBV_MWORLD,
	// ジオメトリシェーダ
	CBG_MARGIN,
	// ピクセルシェーダ
	CBP_MAT,
	CBP_LIGHT,
	CBP_CAMERA,
	CBP_MARGIN,

	CBUF_NUM
};
// 定数バッファ数
#define CBV_NUM (4)
#define CBG_NUM (1)
#define CBP_NUM (4)

//--- クラス
class Shader
{
	Shader() {}
	~Shader() {}
public:
	inline static Shader* GetInstance()
	{
		static Shader instance;
		return &instance;
	}

	friend class CDirectX;

	HRESULT Init();
	void Uninit();

	void Bind(VertexShaderKind vs, PixelShaderKind ps);

	void SetWorld(const DirectX::XMMATRIX& world);
	void SetView(const DirectX::XMMATRIX& view);
	void SetProjection(const DirectX::XMMATRIX& proj);
	void SetAnimation(const DirectX::XMMATRIX* pMatrix, int num);
	void SetWorldMulti(int num, const DirectX::XMMATRIX& world);
	void SetTexture(ID3D11ShaderResourceView* pTexture);
	void SetDiffuse(const DirectX::XMFLOAT4& diffuse);
	void SetAmbient(const DirectX::XMFLOAT4& ambient);
	void SetSpecular(const DirectX::XMFLOAT4& specular, float exp);
	void SetEmissive(const DirectX::XMFLOAT4& emissive);
	void SetLightDir(const DirectX::XMFLOAT4& dir);
	void SetLightDiffuse(const DirectX::XMFLOAT4& diffuse);
	void SetLightAmbient(const DirectX::XMFLOAT4& ambient);
	void SetLightSpecular(const DirectX::XMFLOAT4& specular);
	void SetPSCameraPos(const DirectX::XMFLOAT3& pos);
	void SetPSVal(const DirectX::XMFLOAT4& val);
	void SetGSVal(const DirectX::XMFLOAT4& val);

private:
	ID3D11InputLayout* m_pInputLayout[VS_KIND_MAX];
	ID3D11VertexShader* m_pVertexShader[VS_KIND_MAX];
	ID3D11GeometryShader* m_pGeometryShader[GS_KIND_MAX];
	ID3D11PixelShader* m_pPixelShader[PS_KIND_MAX];

	ID3D11ShaderResourceView* m_pTexture[2];

	ID3D11Buffer* m_pBuffers[CBUF_NUM];

	DirectX::XMFLOAT4X4 m_world;
	VSBufferCamera		m_vsCamera;
	DirectX::XMFLOAT4X4 m_anime[150];
	DirectX::XMFLOAT4X4 m_multiWorld[MAX_INSTANCE_NUM];

	GSBufferValue		m_gsVal;

	PSBufferMaterial	m_material;
	PSBufferLight		m_light;
	PSBufferCamera		m_psCamera;
	PSBufferValue		m_psVal;
};
