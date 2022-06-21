//--- �C���N���[�h��
#include "DrawBuffer.h"

DrawBuffer::DrawBuffer()
	: m_pVertexBuffer(NULL)
	, m_vtxSize(0)
	, m_vtxCount(0)
	, m_pIndexBuffer(NULL)
	, m_idxCount(0)
{
}
DrawBuffer::~DrawBuffer()
{
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
}

HRESULT DrawBuffer::CreateVertexBuffer(void* pVtx, UINT size, UINT count, bool isWrite /* = false*/)
{
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size * count;
	if (isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
	}
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// �o�b�t�@�̏����l
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pVtx;

	// ���_�o�b�t�@�̍쐬
	HRESULT hr;
	ID3D11Device* pDevice = GET_DX->GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pVertexBuffer);

	if (SUCCEEDED(hr))
	{
		m_vtxSize = size;
		m_vtxCount = count;
	}
	return hr;
}

HRESULT DrawBuffer::CreateIndexBuffer(const long* pIdx, UINT count)
{
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = sizeof(long) * count;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pIdx;

	ID3D11Device* pDevice = GET_DX->GetDevice();
	HRESULT hr;
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pIndexBuffer);
	if (SUCCEEDED(hr))
	{
		m_idxCount = count;
	}

	return hr;
}

// �o�b�t�@�̏�������
void DrawBuffer::Write(void* pData)
{
	HRESULT hr;
	ID3D11DeviceContext* pContext = GET_DX->GetContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;
	hr = pContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
	// Map�֐��ŏ�������OK�ł���Ύ��s
	if (SUCCEEDED(hr))
	{
		memcpy_s(mapResource.pData, m_vtxSize*m_vtxCount, pData, m_vtxSize * m_vtxCount);
	}
	// �������ݏI��
	pContext->Unmap(m_pVertexBuffer, 0);
}

void DrawBuffer::Draw(D3D11_PRIMITIVE_TOPOLOGY primitive)
{
	ID3D11DeviceContext* pContext = GET_DX->GetContext();
	// ���_�������̑傫��
	UINT stride = m_vtxSize;
	// ���_�f�[�^�̓ǂݎ��J�n�ʒu
	UINT offset = 0;

	// �v���~�e�B�u�̐ݒ�
	pContext->IASetPrimitiveTopology(primitive);

	// �`��Ɏg�p����o�b�t�@�̐ݒ�
	pContext->IASetVertexBuffers(
		0,	// GPU�ւ̊��蓖�Đ�
		1,	// ���_�o�b�t�@�̐�
		&m_pVertexBuffer,	// ���_�o�b�t�@
		&stride,	// ���_�̃T�C�Y
		&offset		// �ǂݎ��J�n�ʒu
	);

	// �`��
	if (m_idxCount > 0)
	{
		// �`��Ɏg�p����C���f�b�N�X�o�b�t�@��ݒ�
		pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// �C���f�b�N�X�o�b�t�@���g�p���ĕ`��
		pContext->DrawIndexed(m_idxCount, 0, 0);
	}
	else
	{
		// ���_�o�b�t�@�݂̂ŕ`��
		pContext->Draw(m_vtxCount, 0);
	}
}

void DrawBuffer::MultiDraw(int num, int offset)
{
	ID3D11DeviceContext* pContext = GET_DX->GetContext();
	// �v���~�e�B�u�ݒ�
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// ���_�o�b�t�@�ݒ�
	const UINT stride = m_vtxSize;
	const UINT off = 0;
	pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &off);

	// �`��
	if (m_idxCount > 0)
	{
		// �C���f�b�N�X�o�b�t�@�ݒ�
		pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		pContext->DrawIndexedInstanced(m_idxCount, num, 0, 0, offset);
	}
	else
	{
		// ���_�o�b�t�@�݂̂ŕ`��
		pContext->DrawInstanced(m_vtxCount, num, 0, offset);
	}
}
