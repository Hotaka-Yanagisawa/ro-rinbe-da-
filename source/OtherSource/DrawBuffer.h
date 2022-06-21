#pragma once

//--- �C���N���[�h��
#include "DirectX.h"

class DrawBuffer
{
public:
	DrawBuffer();
	~DrawBuffer();

	// ���_���o�b�t�@
	HRESULT CreateVertexBuffer(
		void* pVtx,
		UINT size,
		UINT count,
		bool isWrite = false
	);

	// �C���f�b�N�X�o�b�t�@
	HRESULT CreateIndexBuffer(
		const long* pIdx,
		UINT count
	);

	// �o�b�t�@�̏�������
	void Write(void* pData);

	// �o�b�t�@�̕`��
	void Draw(D3D11_PRIMITIVE_TOPOLOGY primitive);
	void MultiDraw(int num, int offset);

private:
	ID3D11Buffer* m_pVertexBuffer;
	UINT m_vtxSize;
	UINT m_vtxCount;

	ID3D11Buffer* m_pIndexBuffer;
	UINT m_idxCount;

};
