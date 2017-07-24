/// <summary>
/// 当たり判定のノード
/// </summary>
#pragma once

#include "Collision.h"
#include "Obj3d.h"
class CollisionNode
{
protected:
	//デバッグ表示ON
	static bool m_GetDebugVisible;

public:
	static bool SetDebugVisible(bool flag) { return m_GetDebugVisible = flag; }

	static bool GetDebugVisible() { return m_GetDebugVisible; }

public:
	
	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual void Update() = 0;
	//描画
	virtual void Draw() = 0;

	void SetParent(Obj3d* parent);

	void SetOfset(const DirectX::SimpleMath::Vector3& ofset) { m_Ofset = ofset; };
protected:
	//デバック表示用のオブジェクト
	Obj3d m_Obj;
	//親からのオフセット(座標のずれ)
	DirectX::SimpleMath::Vector3 m_Ofset;
};
//球当たり判定ノード
class SphereNode :public CollisionNode, public Sphere
{
public:
	SphereNode();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();

	void SetLocalRadius(float radius) { m_LocalRadius = radius; };
protected:
	//ローカル半径
	float m_LocalRadius;

};
