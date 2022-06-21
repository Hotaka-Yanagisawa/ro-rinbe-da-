/*
InitSound�֐���LoadTexture�֐�����ɌĂяo���ƃG���[
��������COM�I�u�W�F�N�g�𗘗p���邽��

���X�i�[
���𕷂����߂́u���v�ɑ����B3D�T�E���h�ŕK�v�B
�\�[�X
���𔭂���u�����v�ɑ����B�X�s�[�J�[�BXAudio2�ł�Voice�ƌĂ΂��B
�o�b�t�@
���f�[�^���i�[���Ă����o�b�t�@�BWAV�t�@�C���AOGG�t�@�C���Ȃǂ��烍�[�h�B
 */
#ifndef __MYSOUND_H__
#define __MYSOUND_H__

#define _USE_MATH_DEFINES
#include <math.h>
#include <xaudio2.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <MSAcm.h>
#include <Shlwapi.h>
#include <vector>
#include <map>
#include <Windows.h>
#include <stdio.h>


#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msacm32.lib")
#pragma comment(lib, "shlwapi.lib")


#pragma comment(lib, "xaudio2.lib")

 //----------
 // �萔��`
 //----------
const BYTE CMP_MATCH = 0;

//----------
// �\����
//----------
struct SoundData
{
	WAVEFORMATEX		format;		// WAV�t�H�[�}�b�g
	BYTE				*pBuffer;	// �T�E���h�f�[�^
	DWORD				bufSize;	// �f�[�^�T�C�Y
	XAUDIO2_BUFFER		sound;		// �T�E���h�o�b�t�@
};
struct MP3FormatInfo
{
	DWORD offset;
	DWORD dataSize;
};
struct MP3FrameInfo
{
	BYTE channel;
	BYTE padding;
	DWORD sampleRate;
	DWORD bitRate;
	DWORD frameSize;
};

struct FLOAT2
{
	float x;
	float y;
};

typedef std::pair<std::string, SoundData> SoundKey;
typedef std::map<std::string, SoundData> SoundList;
typedef std::vector<IXAudio2SourceVoice*> SourceList;

class CSound
{

public:
	CSound();
	~CSound();

	XAUDIO2_BUFFER* m_pBuffer;
	IXAudio2SourceVoice* m_pSpeaker;

	static HRESULT InitSound(void);
	static void UninitSound(void);

	bool Fade(float TargetVolume, float TargetTime);
	void UpdateSoundFade();
	void Update();
	void Uninit();

	XAUDIO2_BUFFER* CreateSound(const char *file, bool loop = false);				// �T�E���h�̓ǂݍ���
	IXAudio2SourceVoice* PlaySound(XAUDIO2_BUFFER* pSound,
		float TargetVolume = NULL, float TargetTime = NULL);	// �T�E���h�̍Đ�

	std::tuple<int, int> LoadIOCh(IXAudio2SourceVoice*, IXAudio2MasteringVoice*);

	void Pan(IXAudio2SourceVoice* pSourceVoice, IXAudio2MasteringVoice* pMasteringVoice,
		int Type = 0, FLOAT2 pos = { NULL,NULL });


	bool m_bFade;
	float m_Deltatime;
private:
	static IXAudio2 *m_pXAudio;
	static IXAudio2MasteringVoice *m_pMasterVoice;

	float m_vol=0;
	float m_tempVol=0;
	float m_tempTime=0;


	//float m_Pan = -90.0f; // �炵�����p�x
	float m_Rad; // ���W�A���ɕϊ�
	float m_RadX; // ���W�A���ɕϊ�
	float m_RadY; // ���W�A���ɕϊ�

	float m_DistanceX;
	float m_DistanceY;

	int m_InChannels = -1;
	int m_OutChannels = -1;
	bool m_LRswitch = false;
	float m_Volumes[2] = { 1.0f, 0.0f };	//�p���j���O�p
	int m_Cnt = 0;


	SoundList m_soundList;
	SourceList m_sourceList;

	
	HRESULT LoadWav(const char *file, SoundData *pData);
	HRESULT LoadMP3(const char *file, SoundData *pData);
	DWORD ReadMP3Format(HANDLE hFile, MP3FormatInfo *pFormat);
	DWORD ReadMP3FrameHeader(HANDLE hFile, DWORD seek, MP3FrameInfo *pFrame);
	DWORD ReadMP3Data(HANDLE hFile, DWORD seek, DWORD size, MP3FrameInfo *pFrame, SoundData *pData);
};
















//----------
// �v���g�^�C�v�錾
//----------
//HRESULT InitSound(void);
//void UninitSound(void);
//
//// �T�E���h�̓ǂݍ���
////XAUDIO2_BUFFER* CreateSound(const char *file, bool loop = false);
//// �T�E���h�̍Đ�
//IXAudio2SourceVoice* PlaySound(XAUDIO2_BUFFER* pSound);

#endif // __SOUND_H__