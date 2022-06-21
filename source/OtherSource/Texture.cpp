//--- インクルード
#include "Texture.h"
#include "DirectXTex/DirectXTex.h"

#ifdef _X86_
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/Win32/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "DirectXTex/Win32/Release/DirectXTex.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "DirectXTex/x64/Release/DirectXTex.lib")
#endif
#endif

//==================================================
// 初期化
//==================================================
void TextureManager::Init()
{
	m_bLoad = true;
}

//==================================================
// 終了
//==================================================
void TextureManager::Uninit()
{
	for (auto i : m_List) SAFE_RELEASE(i.second);
}

//==================================================
// テクスチャ読み込み
//--------------------------------------------------
// 引数		: ファイル名
// 戻り値	: テクスチャのアドレス
//==================================================
ID3D11ShaderResourceView* TextureManager::Load(std::string Name)
{
	if (!m_bLoad) return nullptr;

	if(!m_List.count(Name))
	{
		ID3D11ShaderResourceView* pTexture;
		LoadTextureFromFile(Name.c_str(), &pTexture);
		m_List[Name] = pTexture;
		return pTexture;
	}
	else return m_List[Name];
}

//==================================================
// テクスチャデータ読み込み
//--------------------------------------------------
// 引数1	: ファイル名
// 引数2	: ポインタ
//==================================================
void TextureManager::LoadTextureFromFile(const char *pszFileName, ID3D11ShaderResourceView **ppTexture)
{
	HRESULT hr;
	DirectX::TexMetadata mdata;
	DirectX::ScratchImage image;
	wchar_t wPath[MAX_PATH];
	size_t wLen = 0;

	// 文字変換
	MultiByteToWideChar(0, 0, pszFileName, -1, wPath, MAX_PATH);
	// ファイル別読み込み
	if (strstr(pszFileName, ".tga")) hr = DirectX::LoadFromTGAFile(wPath, &mdata, image);
	else hr = DirectX::LoadFromWICFile(wPath, DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &mdata, image);
	if (FAILED(hr)) MessageBox(NULL, pszFileName, "Failed to load texture.", MB_OK);

	// シェーダリソースビュー作成
	ID3D11Device *pDevice = GET_DX->GetDevice();
	hr = CreateShaderResourceView(
		pDevice, image.GetImages(), image.GetImageCount(),
		mdata, ppTexture);
}