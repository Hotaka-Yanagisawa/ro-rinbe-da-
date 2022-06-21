//=======================================================================
// Scene.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/29	�쐬
//			
//=======================================================================
#pragma once

//--- �񋓑�
namespace SCENE
{
	enum TYPE
	{
		NO,
		TITLE,
		SELECT,
		GAME,
		RESULT,

		MAX
	};
}

//--- �N���X
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() = 0;
	virtual void Uninit() = 0;

	virtual SCENE::TYPE Update() = 0;
	virtual void Draw() = 0;

private:

};
