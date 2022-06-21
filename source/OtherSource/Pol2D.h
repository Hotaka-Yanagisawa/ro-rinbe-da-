//=======================================================================
// Pol2D.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/28	�쐬
//		 12/05	�A�j���̏����ǉ�
//			24	�`����@�t���O�ǉ�
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Transform.h"
#include "Texture.h"
#include "DrawBuffer.h"

//--- �񋓑�
namespace ANIME
{
	enum STATUS
	{
		NO,		// �A�j���Ȃ�
		PLAY,	// �Đ���
		STOP,	// ��~��
		END,	// �I������

		MAX
	};
}

//--- �N���X
class Pol2D
{
public:
	Pol2D() {}
	~Pol2D() {}

	void Init();
	void Uninit();

	void Update();
	void Draw();

	// �`����
	Transform m_Transform;
	float m_r, m_g, m_b, m_a;
	float m_fSplitX, m_fSplitY;
	float m_fTexCoordX, m_fTexCoordY;

	// �`����@�t���O
	bool m_bBillboard;
	bool m_bParallel;
	bool m_bZSort;

	// �ݒ�
	void SetTexture(const char*);
	void SetAnime(int Start, int Num, int Pace, bool Loop = true);

	// �A�j���[�V�����p�ϐ�
public:
	ANIME::STATUS m_AnimeStatus;
	bool m_bLoop;
private:
	int m_nCount;
	int m_nPace;
	int m_nStartX, m_nStartY;
	int m_nEndX, m_nEndY;

private:
	// ���_���
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 uv;
	};
	Vertex* m_Vertex;

	ID3D11ShaderResourceView* m_pTexture;
	DrawBuffer m_Buffer;
};
