//=======================================================================
// Shader.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �V�F�[�_�֘A
//-----------------------------------------------------------------------
// �X�V����
//	2021/01/05	�쐬
//			15	�W�I���g���V�F�[�_�ǉ�
//			19	�萔�o�b�t�@�p�̗񋓑̒ǉ�
//			20	�����C���X�^���X
//			22	�������
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "DirectX.h"
#include <DirectXMath.h>

//--- �萔�E�}�N��
#define SHADER	(Shader::GetInstance())
#define MAX_INSTANCE_NUM	(500)

//--- �񋓑�
// ���_�V�F�[�_
enum VertexShaderKind
{
	VS_WORLD,
	VS_ANIMATION,
	VS_MULTI,

	VS_KIND_MAX
};
// �W�I���g���V�F�[�_
enum GeometryShaderKind
{
	GS_NORMAL,

	GS_KIND_MAX
};
// �s�N�Z���V�F�[�_
enum PixelShaderKind
{
	PS_LAMBERT,
	PS_UNLIT,
	PS_FIELD,
	PS_PLAYER,

	PS_KIND_MAX
};

//--- �萔�o�b�t�@
// �J�����ϊ��s��
struct VSBufferCamera
{
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 proj;
};
// �}�e���A��
struct PSBufferMaterial
{
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 ambient;
	DirectX::XMFLOAT4 specular;
	DirectX::XMFLOAT4 emissive;
};
// ���C�g
struct PSBufferLight
{
	DirectX::XMFLOAT4 dir;
	PSBufferMaterial material;
};
// �J����
struct PSBufferCamera
{
	DirectX::XMFLOAT4 pos;
};

// �K��
struct PSBufferValue
{
	DirectX::XMFLOAT4 val;
};
struct GSBufferValue
{
	DirectX::XMFLOAT4 val;
};

// �萔�o�b�t�@���
enum CBUF_KIND
{
	// ���_�V�F�[�_
	CBV_WORLD,
	CBV_CAMERA,
	CBV_ANIME,
	CBV_MWORLD,
	// �W�I���g���V�F�[�_
	CBG_MARGIN,
	// �s�N�Z���V�F�[�_
	CBP_MAT,
	CBP_LIGHT,
	CBP_CAMERA,
	CBP_MARGIN,

	CBUF_NUM
};
// �萔�o�b�t�@��
#define CBV_NUM (4)
#define CBG_NUM (1)
#define CBP_NUM (4)

//--- �N���X
class Shader
{
	Shader() {}
	~Shader() {}
public:
	inline static Shader* GetInstance()
	{
		static Shader instance;
		return &instance;
	}

	friend class CDirectX;

	HRESULT Init();
	void Uninit();

	void Bind(VertexShaderKind vs, PixelShaderKind ps);

	void SetWorld(const DirectX::XMMATRIX& world);
	void SetView(const DirectX::XMMATRIX& view);
	void SetProjection(const DirectX::XMMATRIX& proj);
	void SetAnimation(const DirectX::XMMATRIX* pMatrix, int num);
	void SetWorldMulti(int num, const DirectX::XMMATRIX& world);
	void SetTexture(ID3D11ShaderResourceView* pTexture);
	void SetDiffuse(const DirectX::XMFLOAT4& diffuse);
	void SetAmbient(const DirectX::XMFLOAT4& ambient);
	void SetSpecular(const DirectX::XMFLOAT4& specular, float exp);
	void SetEmissive(const DirectX::XMFLOAT4& emissive);
	void SetLightDir(const DirectX::XMFLOAT4& dir);
	void SetLightDiffuse(const DirectX::XMFLOAT4& diffuse);
	void SetLightAmbient(const DirectX::XMFLOAT4& ambient);
	void SetLightSpecular(const DirectX::XMFLOAT4& specular);
	void SetPSCameraPos(const DirectX::XMFLOAT3& pos);
	void SetPSVal(const DirectX::XMFLOAT4& val);
	void SetGSVal(const DirectX::XMFLOAT4& val);

private:
	ID3D11InputLayout* m_pInputLayout[VS_KIND_MAX];
	ID3D11VertexShader* m_pVertexShader[VS_KIND_MAX];
	ID3D11GeometryShader* m_pGeometryShader[GS_KIND_MAX];
	ID3D11PixelShader* m_pPixelShader[PS_KIND_MAX];

	ID3D11ShaderResourceView* m_pTexture[2];

	ID3D11Buffer* m_pBuffers[CBUF_NUM];

	DirectX::XMFLOAT4X4 m_world;
	VSBufferCamera		m_vsCamera;
	DirectX::XMFLOAT4X4 m_anime[150];
	DirectX::XMFLOAT4X4 m_multiWorld[MAX_INSTANCE_NUM];

	GSBufferValue		m_gsVal;

	PSBufferMaterial	m_material;
	PSBufferLight		m_light;
	PSBufferCamera		m_psCamera;
	PSBufferValue		m_psVal;
};
