//--- �C���N���[�h
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
// ������
//==================================================
void TextureManager::Init()
{
	m_bLoad = true;
}

//==================================================
// �I��
//==================================================
void TextureManager::Uninit()
{
	for (auto i : m_List) SAFE_RELEASE(i.second);
}

//==================================================
// �e�N�X�`���ǂݍ���
//--------------------------------------------------
// ����		: �t�@�C����
// �߂�l	: �e�N�X�`���̃A�h���X
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
// �e�N�X�`���f�[�^�ǂݍ���
//--------------------------------------------------
// ����1	: �t�@�C����
// ����2	: �|�C���^
//==================================================
void TextureManager::LoadTextureFromFile(const char *pszFileName, ID3D11ShaderResourceView **ppTexture)
{
	HRESULT hr;
	DirectX::TexMetadata mdata;
	DirectX::ScratchImage image;
	wchar_t wPath[MAX_PATH];
	size_t wLen = 0;

	// �����ϊ�
	MultiByteToWideChar(0, 0, pszFileName, -1, wPath, MAX_PATH);
	// �t�@�C���ʓǂݍ���
	if (strstr(pszFileName, ".tga")) hr = DirectX::LoadFromTGAFile(wPath, &mdata, image);
	else hr = DirectX::LoadFromWICFile(wPath, DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &mdata, image);
	if (FAILED(hr)) MessageBox(NULL, pszFileName, "Failed to load texture.", MB_OK);

	// �V�F�[�_���\�[�X�r���[�쐬
	ID3D11Device *pDevice = GET_DX->GetDevice();
	hr = CreateShaderResourceView(
		pDevice, image.GetImages(), image.GetImageCount(),
		mdata, ppTexture);
}