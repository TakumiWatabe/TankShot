#include "pch.h"
#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

static bool m_GetDebugVisible;
bool CollisionNode::m_GetDebugVisible=true;

/// <summary>
/// CollisionNodeのメンバ関数
/// </summary>

void CollisionNode::SetParent(Obj3d * parent)
{
	m_Obj.SetParent(parent);
}


SphereNode::SphereNode()
{
	//デフォルト半径1メートルにする
	m_LocalRadius = 1.0f;
}

/// <summary>
/// SphereNodeのメンバ関数
/// </summary>
void SphereNode::Initialize()
{
	//デバック表示用
	m_Obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_Obj.SetTrans(m_Ofset);
	m_Obj.SetScale(Vector3(m_LocalRadius));
	m_Obj.Update();

	{//ワールド座標での当たり判定球を計算
		//計算済みのワールド行列を取得
		Matrix worldm = m_Obj.GetWorld();

		//モデルの座標系での中心点
		Vector3 center(0, 0, 0);
		//モデル座標系での右端
		Vector3 right(1, 0, 0);
		//ワールド行列に変換
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		//当たり判定に結果を代入
		Sphere::Center = center;
		Sphere::Radius = Vector3::Distance(center, right);
	}
}

void SphereNode::Draw()
{
	m_Obj.Draw();
}
