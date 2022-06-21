//--- インクルード
#include "Shader.h"
#include "DirectX.h"
#include "Defines.h"
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

//--- 頂点シェーダ
// 通常
const char VSCodeWorld[] = "\
cbuffer ConstantBuffer : register(b0)\
{\
	float4x4 World;\
};\
cbuffer ConstantBuffer : register(b1)\
{\
	float4x4 View;\
	float4x4 Proj;\
};\
\
struct VS_IN\
{\
	float3 pos : POSITION0;\
	float4 color : COLOR0;\
	float2 uv : TEXCOORD0;\
	float3 normal : NORMAL0;\
};\
struct VS_OUT\
{\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
	float3 wPos : TEXCOORD3;\
};\
\
VS_OUT main(VS_IN VIN)\
{\
	VS_OUT VOUT;\
	VOUT.pos = float4(VIN.pos, 1);\
	VOUT.pos = mul(VOUT.pos, World);\
	VOUT.wPos = VOUT.pos;\
	VOUT.pos = mul(VOUT.pos, View);\
	VOUT.pos = mul(VOUT.pos, Proj);\
	VOUT.uv = VIN.uv;\
	VOUT.color = VIN.color;\
	VOUT.normal = mul(VIN.normal, (float3x3)World);\
	return VOUT;\
}";
// アニメ
const char VSCodeAnime[] = "\
struct VS_IN {\
	float3 pos : POSITION0;\
	float4 color : COLOR0;\
	float2 uv : TEXCOORD0;\
	float3 normal : NORMAL0;\
	float4 weight : BLENDWEIGHT0;\
	uint4 index : BLENDINDICES0;\
};\
struct VS_OUT {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
	float3 wPos : TEXCOORD3;\
};\
cbuffer ConstantBuffer : register(b0) {\
	float4x4 World;\
};\
cbuffer ConstantBuffer : register(b1) {\
	float4x4 View;\
	float4x4 Proj;\
};\
cbuffer ConstantBuffer : register(b2) {\
	float4x4 Bone[150];\
};\
VS_OUT main(VS_IN VIN) {\
	float4x4 mat = 0;\
	mat += Bone[VIN.index.x] * VIN.weight.x;\
	mat += Bone[VIN.index.y] * VIN.weight.y;\
	mat += Bone[VIN.index.z] * VIN.weight.z;\
	mat += Bone[VIN.index.w] * VIN.weight.w;\
	VS_OUT VOUT;\
	VOUT.pos = float4(VIN.pos, 1);\
	VOUT.pos = mul(VOUT.pos, mat);\
	VOUT.pos = mul(VOUT.pos, World);\
	VOUT.pos = mul(VOUT.pos, View);\
	VOUT.pos = mul(VOUT.pos, Proj);\
	VOUT.uv = VIN.uv;\
	VOUT.color = VIN.color;\
	VOUT.normal = VIN.normal;\
	VOUT.normal = mul(VOUT.normal, (float3x3)mat);\
	VOUT.normal = mul(VOUT.normal, (float3x3)World);\
	return VOUT;\
}";
// インスタンス
const char VSCodeMulti[] = "\
cbuffer ConstantBuffer : register(b3)\
{\
	float4x4 World[500];\
};\
cbuffer ConstantBuffer : register(b1)\
{\
	float4x4 View;\
	float4x4 Proj;\
};\
\
struct VS_IN\
{\
	float3 pos : POSITION0;\
	float4 color : COLOR0;\
	float2 uv : TEXCOORD0;\
	float3 normal : NORMAL0;\
	uint insID : SV_InstanceID;\
};\
struct VS_OUT\
{\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
	float3 wPos : TEXCOORD3;\
};\
\
VS_OUT main(VS_IN VIN)\
{\
	VS_OUT VOUT;\
	VOUT.pos = float4(VIN.pos, 1);\
	VOUT.pos = mul(VOUT.pos, World[VIN.insID % 500]);\
	VOUT.wPos = VOUT.pos;\
	VOUT.pos = mul(VOUT.pos, View);\
	VOUT.pos = mul(VOUT.pos, Proj);\
	VOUT.uv = VIN.uv;\
	VOUT.color = VIN.color;\
	VOUT.normal = mul(VIN.normal, (float3x3)World[VIN.insID]);\
	return VOUT;\
}";

//--- ピクセルシェーダ
// 影あり
const char PSCodeLambert[] = "\
struct PS_IN {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
};\
struct Material {\
	float4 diffuse;\
	float4 ambient;\
	float4 specular;\
	float4 emissive;\
};\
cbuffer ConstantBuffer : register(b0) {\
	Material objMat;\
};\
cbuffer ConstantBuffer : register(b1) {\
	float3 lightDir;\
	Material lightMat;\
};\
Texture2D tex : register(t0);\
SamplerState samp : register(s0);\
float4 main(PS_IN PIN) : SV_Target {\
	float4 color = tex.Sample(samp, PIN.uv) * PIN.color;\
	float4 diffuse = objMat.diffuse * lightMat.diffuse *\
					 max(dot(normalize(PIN.normal), -lightDir), 0);\
	float4 ambient = objMat.ambient * lightMat.ambient;\
	color.rgb *= diffuse + ambient;\
	return color;\
}";
//--- 影なし
const char PSCodeUnlit[] = "\
struct PS_IN {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
};\
Texture2D tex : register(t0);\
SamplerState samp : register(s0);\
float4 main(PS_IN PIN) : SV_Target {\
	float4 color = tex.Sample(samp, PIN.uv) * PIN.color;\
	if (color.a <= 0.2f) discard;\
	return color;\
}";
//--- フィールド用
const char PSCodeField[] = "\
cbuffer ConstantBuffer : register(b3)\
{\
	float4 val;\
}\
Texture2D tex : register(t0);\
SamplerState samp : register(s0);\
struct PS_IN {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
	float3 wPos : TEXCOORD3;\
};\
float4 main(PS_IN PIN) : SV_Target\
{\
	float4 color = val;\
	float coord = PIN.wPos.x * PIN.wPos.x + PIN.wPos.z * PIN.wPos.z;\
	if ((coord > ( 10 *  10)) && (coord < (120 * 120))) color.rgb *= 0.5f;\
	if ((coord > (120 * 120)) && (coord < (200 * 200))) color.rgb *= 0.8f;\
	if ((coord > (200 * 200)) && (coord < (250 * 250))) color.rgb *= 1.1f;\
	if ((coord > (250 * 250)) && (coord < (255 * 255))) color.rgb *= 10.0f;\
	return color;\
}";
//--- プレイヤー用
const char PSCodePlayer[] = "\
struct Material {\
	float4 diffuse;\
	float4 ambient;\
	float4 specular;\
	float4 emissive;\
};\
cbuffer ConstantBuffer : register(b0) {\
	Material objMat;\
};\
cbuffer ConstantBuffer : register(b1) {\
	float3 lightDir;\
	Material lightMat;\
};\
Texture2D tex : register(t0);\
SamplerState samp : register(s0);\
struct PS_IN {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
	float3 wPos : TEXCOORD3;\
};\
float4 main(PS_IN PIN) : SV_Target\
{\
	float4 color = tex.Sample(samp, PIN.uv) * PIN.color;\
	color.a *= 0.7f;\
	color.r *= 1.0f - PIN.wPos.y / 12.0f;\
	color.rgb *= 1.3f;\
	return color;\
}";

//==================================================
// 初期化
//==================================================
HRESULT Shader::Init()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GET_DX->GetDevice();

	//--- シェーダ生成
	// 初期化
	ZeroMemory(m_pInputLayout, sizeof(m_pInputLayout));
	ZeroMemory(m_pVertexShader, sizeof(m_pVertexShader));
	ZeroMemory(m_pGeometryShader, sizeof(m_pGeometryShader));
	ZeroMemory(m_pPixelShader, sizeof(m_pPixelShader));
	ZeroMemory(m_pBuffers, sizeof(m_pBuffers));

	//--- シェーダ作成
	ID3DBlob *Error;
	ID3DBlob *pBlob;
	// 頂点レイアウト
	const D3D11_INPUT_ELEMENT_DESC LayoutWorld[] =
	{
		{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,							 D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",			0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	const D3D11_INPUT_ELEMENT_DESC LayoutAnime[] =
	{
		{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,							 D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",			0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BLENDINDICES",	0, DXGI_FORMAT_R32G32B32A32_UINT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	const D3D11_INPUT_ELEMENT_DESC* pLayout[] = { LayoutWorld, LayoutAnime, LayoutWorld };
	UINT pLayoutNum[] = { _countof(LayoutWorld), _countof(LayoutAnime),_countof(LayoutWorld), };
	// シェーダーパス
	const wchar_t* VSFile[] = { L"Shader/VNormal.hlsl", L"Shader/VAnime.hlsl", L"Shader/VMulti.hlsl" };
	const wchar_t* GSFile[] = { L"Shader/GDisas.hlsl" };
	const wchar_t* PSFile[] = { L"Shader/PNormal.hlsl", L"Shader/PUnlit.hlsl", L"Shader/PField.hlsl", L"Shader/PPlayer.hlsl" };
	//--- 頂点シェーダ作成
	const char* pVSCode[] = { VSCodeWorld, VSCodeAnime, VSCodeMulti };
	for (int i = 0; i < VS_KIND_MAX; ++i)
	{
		// コンパイル
		hr = D3DCompile(pVSCode[i], strlen(pVSCode[i]), NULL, NULL, NULL, "main", "vs_5_0", 0, 0, &pBlob, &Error);
		//hr = D3DCompileFromFile(VSFile[i], NULL, NULL, "main", "vs_5_0", NULL, NULL, &pBlob, &Error);
		if (FAILED(hr)) return hr;
		//頂点レイアウト作成
		hr = pDevice->CreateInputLayout(pLayout[i], pLayoutNum[i],
			pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_pInputLayout[i]);
		if (FAILED(hr)) return hr;
		//オブジェクト生成
		hr = pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &m_pVertexShader[i]);
		if (FAILED(hr)) return hr;
	}
	SAFE_RELEASE(pBlob);
	//--- ジオメトリシェーダ作成
	for (int i = 0; i < GS_KIND_MAX; ++i)
	{
		// コンパイル
		hr = D3DCompileFromFile(GSFile[i], NULL, NULL, "main", "gs_5_0", NULL, NULL, &pBlob, &Error);
		if (FAILED(hr)) return hr;
		//オブジェクト生成
		hr = pDevice->CreateGeometryShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &m_pGeometryShader[0]);
		if (FAILED(hr)) return hr;
	}
	SAFE_RELEASE(pBlob);
	//--- ピクセルシェーダ作成
	const char* pPSCode[] = { PSCodeLambert, PSCodeUnlit, PSCodeField, PSCodePlayer };
	for (int i = 0; i < PS_KIND_MAX; ++i)
	{
		// コンパイル
		hr = D3DCompile(pPSCode[i], strlen(pPSCode[i]), NULL, NULL, NULL, "main", "ps_5_0", 0, 0, &pBlob, &Error);
		//hr = D3DCompileFromFile(PSFile[i], NULL, NULL, "main", "ps_5_0", NULL, NULL, &pBlob, &Error);
		if (FAILED(hr)) return hr;
		//オブジェクト生成
		hr = pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &m_pPixelShader[i]);
		if (FAILED(hr)) return hr;
	}
	SAFE_RELEASE(pBlob);

	//--- 定数バッファ生成
	// 初期化
	m_pTexture[0] = nullptr;
	m_pTexture[1] = nullptr;
	m_world._11 = m_vsCamera.view._11 = m_vsCamera.proj._11 = 1.0f;
	m_world._22 = m_vsCamera.view._22 = m_vsCamera.proj._22 = 1.0f;
	m_world._33 = m_vsCamera.view._33 = m_vsCamera.proj._33 = 1.0f;
	m_world._44 = m_vsCamera.view._44 = m_vsCamera.proj._44 = 1.0f;
	m_gsVal.val = DirectX::XMFLOAT4(0, 0, 0, 0);
	m_material.diffuse = DirectX::XMFLOAT4(1, 1, 1, 1);
	m_material.ambient = DirectX::XMFLOAT4(1, 1, 1, 1);
	m_material.specular = DirectX::XMFLOAT4(1, 1, 1, 1);
	m_material.emissive = DirectX::XMFLOAT4(0, 0, 0, 0);
	m_light.dir = DirectX::XMFLOAT4(-1, -1, 1, 0);
	DirectX::XMStoreFloat4(&m_light.dir, DirectX::XMVector3Normalize(DirectX::XMLoadFloat4(&m_light.dir)));
	m_light.material.diffuse = DirectX::XMFLOAT4(1, 1, 1, 1);
	m_light.material.ambient = DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.f);
	m_light.material.specular = DirectX::XMFLOAT4(1, 1, 1, 1);
	m_light.material.emissive = DirectX::XMFLOAT4(0, 0, 0, 0);
	m_psCamera.pos = DirectX::XMFLOAT4(0, 0, -1, 0);
	m_psVal.val = DirectX::XMFLOAT4(0, 0, 0, 0);
	// 作成
	D3D11_BUFFER_DESC shaderBufDesc = {};
	D3D11_SUBRESOURCE_DATA shaderSubResource = {};
	shaderBufDesc.Usage = D3D11_USAGE_DEFAULT;
	shaderBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	UINT BufferSize[] = {
		sizeof(m_world), sizeof(m_vsCamera), sizeof(m_anime), sizeof(m_multiWorld),
		sizeof(m_gsVal),
		sizeof(m_material), sizeof(m_light), sizeof(m_psCamera), sizeof(m_psVal),
	};
	void* BufferData[] = {
		&m_world, &m_vsCamera, m_anime, m_multiWorld,
		&m_gsVal,
		&m_material, &m_light, &m_psCamera, &m_psVal,
	};
	for (int i = 0; i < CBUF_NUM; ++i)
	{
		shaderBufDesc.ByteWidth = BufferSize[i];
		shaderSubResource.pSysMem = BufferData[i];
		hr = pDevice->CreateBuffer(&shaderBufDesc, &shaderSubResource, &m_pBuffers[i]);
		if (FAILED(hr)) return hr;
	}

	// テクスチャ情報
	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = texDesc.Height = 1;
	texDesc.MipLevels = texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	// テクスチャデータ
	BYTE color[4] = { 0xff, 0xff, 0xff, 0xff };
	D3D11_SUBRESOURCE_DATA texSubResource = {};
	texSubResource.SysMemPitch = sizeof(color);
	texSubResource.pSysMem = &color;
	// データ生成
	ID3D11Texture2D *pTex = nullptr;
	hr = pDevice->CreateTexture2D(&texDesc, &texSubResource, &pTex);
	if (FAILED(hr)) return hr;
	// シェーダリソースビュー設定
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderViewDesc = {};
	shaderViewDesc.Format = texDesc.Format;
	shaderViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderViewDesc.Texture2D.MipLevels = texDesc.MipLevels;
	// シェーダリソースビュー作成
	hr = pDevice->CreateShaderResourceView(pTex, &shaderViewDesc, &m_pTexture[0]);
	if (FAILED(hr)) return hr;
	SetTexture(nullptr);

	// シャドウマップ
	texDesc = {};
	texDesc.Width = SCREEN_WIDTH;
	texDesc.Height = SCREEN_HEIGHT;
	texDesc.MipLevels = texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R16_FLOAT;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	// データ生成
	pTex = nullptr;
	hr = pDevice->CreateTexture2D(&texDesc, nullptr, &pTex);
	if (FAILED(hr)) return hr;
	// シェーダリソースビュー設定
	shaderViewDesc = {};
	shaderViewDesc.Format = texDesc.Format;
	shaderViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderViewDesc.Texture2D.MipLevels = texDesc.MipLevels;
	// シェーダリソースビュー作成
	hr = pDevice->CreateShaderResourceView(pTex, &shaderViewDesc, &m_pTexture[1]);
	if (FAILED(hr)) return hr;

	return hr;
}

//==================================================
// 終了
//==================================================
void Shader::Uninit()
{
	for (int i = 0; i < 2; ++i)
		SAFE_RELEASE(m_pTexture[1]);
	for (int i = 0; i < CBUF_NUM; ++i)
		SAFE_RELEASE(m_pBuffers[i]);
	for (int i = 0; i < PS_KIND_MAX; ++i)
		SAFE_RELEASE(m_pPixelShader[i]);
	for (int i = 0; i < GS_KIND_MAX; ++i)
		SAFE_RELEASE(m_pGeometryShader[i]);
	for (int i = 0; i < VS_KIND_MAX; ++i)
	{
		SAFE_RELEASE(m_pVertexShader[i]);
		SAFE_RELEASE(m_pInputLayout[i]);
	}
}

//==================================================
// シェーダセット
//==================================================
void Shader::Bind(VertexShaderKind vs, PixelShaderKind ps)
{
	ID3D11DeviceContext* pContext = GET_DX->GetContext();

	// 入力レイアウト設定
	pContext->IASetInputLayout(m_pInputLayout[vs]);

	// ステージ設定
	pContext->VSSetShader(m_pVertexShader[vs], nullptr, 0);
	//pContext->GSSetShader(m_pGeometryShader[GS_NORMAL], nullptr, 0);
	pContext->PSSetShader(m_pPixelShader[ps], nullptr, 0);

	// 定数バッファ設定
	pContext->VSSetConstantBuffers(0, CBV_NUM, &m_pBuffers[0]);
	//pContext->GSSetConstantBuffers(0, CBG_NUM, &m_pBuffers[CBV_NUM]);
	pContext->PSSetConstantBuffers(0, CBP_NUM, &m_pBuffers[CBV_NUM + CBG_NUM]);

	pContext->PSSetShaderResources(1, 1, m_pTexture);
}

//==================================================
// セッター
//==================================================
void Shader::SetWorld(const DirectX::XMMATRIX& world)
{
	DirectX::XMStoreFloat4x4(&m_world, DirectX::XMMatrixTranspose(world));
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBV_WORLD], 0, NULL, &m_world, 0, 0);
}
void Shader::SetView(const DirectX::XMMATRIX& view)
{
	DirectX::XMStoreFloat4x4(&m_vsCamera.view, DirectX::XMMatrixTranspose(view));
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBV_CAMERA], 0, NULL, &m_vsCamera, 0, 0);
}
void Shader::SetProjection(const DirectX::XMMATRIX& proj)
{
	DirectX::XMStoreFloat4x4(&m_vsCamera.proj, DirectX::XMMatrixTranspose(proj));
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBV_CAMERA], 0, NULL, &m_vsCamera, 0, 0);
}
void Shader::SetAnimation(const DirectX::XMMATRIX* pMatrix, int num)
{
	for (int i = 0; i < num && i < 150; ++i)
	{
		DirectX::XMStoreFloat4x4(&m_anime[i], DirectX::XMMatrixTranspose(pMatrix[i]));
	}
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBV_ANIME], 0, NULL, &m_anime, 0, 0);
}
void Shader::SetWorldMulti(int num, const DirectX::XMMATRIX& world)
{
	DirectX::XMStoreFloat4x4(&m_multiWorld[num], DirectX::XMMatrixTranspose(world));
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBV_MWORLD], 0, NULL, &m_multiWorld, 0, 0);
}
void Shader::SetTexture(ID3D11ShaderResourceView* pTexture)
{
	ID3D11DeviceContext* pContext = GET_DX->GetContext();
	if (pTexture == nullptr) pTexture = m_pTexture[0];
	pContext->PSSetShaderResources(0, 1, &pTexture);
}
void Shader::SetDiffuse(const DirectX::XMFLOAT4& diffuse)
{
	m_material.diffuse = diffuse;
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBP_MAT], 0, NULL, &m_material, 0, 0);
}
void Shader::SetAmbient(const DirectX::XMFLOAT4& ambient)
{
	m_material.ambient = ambient;
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBP_MAT], 0, NULL, &m_material, 0, 0);
}
void Shader::SetSpecular(const DirectX::XMFLOAT4& specular, float exp)
{
	m_material.specular = specular;
	m_material.specular.w = exp;
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBP_MAT], 0, NULL, &m_material, 0, 0);
}
void Shader::SetEmissive(const DirectX::XMFLOAT4& emissive)
{
	m_material.emissive = emissive;
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBP_MAT], 0, NULL, &m_material, 0, 0);
}
void Shader::SetLightDir(const DirectX::XMFLOAT4& dir)
{
	DirectX::XMStoreFloat4(
		&m_light.dir,
		DirectX::XMVector3Normalize(DirectX::XMLoadFloat4(&dir)));
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBP_LIGHT], 0, NULL, &m_light, 0, 0);
}
void Shader::SetLightDiffuse(const DirectX::XMFLOAT4& diffuse)
{
	m_light.material.diffuse = diffuse;
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBP_LIGHT], 0, NULL, &m_light, 0, 0);
}
void Shader::SetLightAmbient(const DirectX::XMFLOAT4& ambient)
{
	m_light.material.ambient = ambient;
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBP_LIGHT], 0, NULL, &m_light, 0, 0);
}
void Shader::SetLightSpecular(const DirectX::XMFLOAT4& specular)
{
	m_light.material.specular = specular;
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBP_LIGHT], 0, NULL, &m_light, 0, 0);
}
void Shader::SetPSCameraPos(const DirectX::XMFLOAT3& pos)
{
	m_psCamera.pos = DirectX::XMFLOAT4(pos.x, pos.y, pos.z, 1);
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBP_CAMERA], 0, NULL, &m_psCamera, 0, 0);
}
void Shader::SetPSVal(const DirectX::XMFLOAT4 & val)
{
	m_psVal.val = DirectX::XMFLOAT4(val.x, val.y, val.z, val.w);
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBP_MARGIN], 0, NULL, &m_psVal, 0, 0);
}
void Shader::SetGSVal(const DirectX::XMFLOAT4 & val)
{
	m_gsVal.val = DirectX::XMFLOAT4(val.x, val.y, val.z, val.w);
	GET_DX->GetContext()->UpdateSubresource(m_pBuffers[CBG_MARGIN], 0, NULL, &m_gsVal, 0, 0);
}
