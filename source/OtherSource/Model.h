//=======================================================================
// Model.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/16	�N���X�쐬��������
//			20	���œǂݍ���
//			27	�I�u�W�F�N�g���Ƃ̃��f�����Ǘ�������
//		 12/18	�ꕔ��ModelManager�Ɉړ�
//			19	�f�o�b�O�p�̃L���[�u���f���ǂݍ��ݏ����ǉ�
//	2021/01/20	�����`��p�t���O�Ə���
//
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Object.h"
#include "FBX/FBXPlayer.h"
#include "DrawBuffer.h"

//--- �萔
// �}���`�Ώ�
enum MultiInstanceModel
{
	MI_BTREE,
	//MI_ENEMY1,

	MULTI_MODEL_NUM
};

//--- �N���X
class Model : public Component
{
public:
	Model() {}
	~Model() {}

	void Init() override;
	void Draw() override;

	void LoadModel(bool Load = true);

	FBXPlayer* m_Model;

private:
	Transform* m_Transform;
	DrawBuffer* m_pBuffer;

	float m_fDif;

public:
	bool m_bMulti;
	int m_nMultiNum;
	static void LoadMultiModel();
	static void DrawMultiModel();
private:
	static int m_nInstCount[MULTI_MODEL_NUM];
	static FBXPlayer* m_MultiModel[MULTI_MODEL_NUM];
	static DrawBuffer* m_pMultiBuffer[MULTI_MODEL_NUM];
};
