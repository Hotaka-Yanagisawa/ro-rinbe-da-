//=======================================================================
// Effect.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/12/02	�쐬
//			16	�v���C���[�̋��E������������邽�߂̃v���O����������
//			22	�y�������߂�
//			25	�z���G�t�F�N�g
//	2021/01/09	�q�b�g
//
//=======================================================================

//--- �C���N���[�h
#include "Pol2D.h"

//--- �萔
#define MAX_PARTICLE	(50 * 2)

//--- �񋓑�
enum KIND
{
	PLAYER = 0,
	CIRCLE,
	SMOKE,
	POWER1,
	POWER2,
	POWER3,
	POWER4,
	POWER5,
	ABSORB,
	HIT,

	MAX
};

//--- �N���X
class Effect
{
	struct PARTICLE
	{
		Pol2D Polygon;
		KIND Kind;
		int	nLife;
		bool bExist;
		float fMass;
	};

public:

	void Init();
	void Uninit();

	void Update();
	void Draw();

	void SetEffect(Float3 Pos, KIND Kind);

private:
	PARTICLE m_Particle[MAX_PARTICLE];

};
