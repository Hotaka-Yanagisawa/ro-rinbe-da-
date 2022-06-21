//=======================================================================
// TextureManager.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/12/13	作成
//			19	パスのマクロ追加
//			
//=======================================================================
#pragma once

//--- インクルード
#include "DirectX.h"
#include <unordered_map>

//--- マクロ
#define FILE_TEX(name)	"Assets/Texture/"##name
#define TEX_PNG(name) FILE_TEX(name)##".png"
#define TEX_JPG(name) FILE_TEX(name)##".jpg"

#define TEXTURE	(TextureManager::GetInstance())

//--- クラス
class TextureManager
{
public:
	inline static TextureManager* GetInstance()
	{
		static TextureManager instance;
		return &instance;
	}

	void Init();
	void Uninit();

	ID3D11ShaderResourceView* Load(std::string Name);

private:
	TextureManager() {}
	~TextureManager() {}

	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_List;

	void LoadTextureFromFile(const char *pszFileName, ID3D11ShaderResourceView **ppTexture);

	bool m_bLoad;
};
