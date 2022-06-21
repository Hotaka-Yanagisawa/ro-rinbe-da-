//=======================================================================
// Cube.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/16	授業内のをコンポーネント化
//			22	Transformを外から触れるように変更
//		 12/10	テクスチャ貼れるようにした			
//
//=======================================================================
#pragma once

//--- インクルード
#include "Object.h"
#include "DrawBuffer.h"

class Cube : public Component
{
public:
	Cube() {}
	~Cube() {}

	void Init() override;

	void Draw() override;
	void Draw(bool Line);

	void SetTexture(const char* FileName);

	Transform* m_Transform;

private:

	DrawBuffer m_Buffer;
	ID3D11ShaderResourceView* m_pTexture;
};
