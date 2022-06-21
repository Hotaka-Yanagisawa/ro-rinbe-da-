//=======================================================================
// Scene.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/29	作成
//			
//=======================================================================
#pragma once

//--- 列挙体
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

//--- クラス
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
