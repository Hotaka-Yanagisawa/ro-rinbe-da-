//--- インクルード部
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

	// バッファの初期値
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pVtx;

	// 頂点バッファの作成
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

// バッファの書き込み
void DrawBuffer::Write(void* pData)
{
	HRESULT hr;
	ID3D11DeviceContext* pContext = GET_DX->GetContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;
	hr = pContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
	// Map関数で書き込みOKであれば実行
	if (SUCCEEDED(hr))
	{
		memcpy_s(mapResource.pData, m_vtxSize*m_vtxCount, pData, m_vtxSize * m_vtxCount);
	}
	// 書き込み終了
	pContext->Unmap(m_pVertexBuffer, 0);
}

void DrawBuffer::Draw(D3D11_PRIMITIVE_TOPOLOGY primitive)
{
	ID3D11DeviceContext* pContext = GET_DX->GetContext();
	// 頂点一つ当たりの大きさ
	UINT stride = m_vtxSize;
	// 頂点データの読み取り開始位置
	UINT offset = 0;

	// プリミティブの設定
	pContext->IASetPrimitiveTopology(primitive);

	// 描画に使用するバッファの設定
	pContext->IASetVertexBuffers(
		0,	// GPUへの割り当て先
		1,	// 頂点バッファの数
		&m_pVertexBuffer,	// 頂点バッファ
		&stride,	// 頂点のサイズ
		&offset		// 読み取り開始位置
	);

	// 描画
	if (m_idxCount > 0)
	{
		// 描画に使用するインデックスバッファを設定
		pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// インデックスバッファを使用して描画
		pContext->DrawIndexed(m_idxCount, 0, 0);
	}
	else
	{
		// 頂点バッファのみで描画
		pContext->Draw(m_vtxCount, 0);
	}
}

void DrawBuffer::MultiDraw(int num, int offset)
{
	ID3D11DeviceContext* pContext = GET_DX->GetContext();
	// プリミティブ設定
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// 頂点バッファ設定
	const UINT stride = m_vtxSize;
	const UINT off = 0;
	pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &off);

	// 描画
	if (m_idxCount > 0)
	{
		// インデックスバッファ設定
		pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		pContext->DrawIndexedInstanced(m_idxCount, num, 0, 0, offset);
	}
	else
	{
		// 頂点バッファのみで描画
		pContext->DrawInstanced(m_vtxCount, num, 0, offset);
	}
}
