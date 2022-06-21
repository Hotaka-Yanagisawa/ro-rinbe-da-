#pragma once

//--- インクルード部
#include "DirectX.h"

class DrawBuffer
{
public:
	DrawBuffer();
	~DrawBuffer();

	// 頂点情報バッファ
	HRESULT CreateVertexBuffer(
		void* pVtx,
		UINT size,
		UINT count,
		bool isWrite = false
	);

	// インデックスバッファ
	HRESULT CreateIndexBuffer(
		const long* pIdx,
		UINT count
	);

	// バッファの書き込み
	void Write(void* pData);

	// バッファの描画
	void Draw(D3D11_PRIMITIVE_TOPOLOGY primitive);
	void MultiDraw(int num, int offset);

private:
	ID3D11Buffer* m_pVertexBuffer;
	UINT m_vtxSize;
	UINT m_vtxCount;

	ID3D11Buffer* m_pIndexBuffer;
	UINT m_idxCount;

};
