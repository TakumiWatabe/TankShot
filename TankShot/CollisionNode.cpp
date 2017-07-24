#include "pch.h"
#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

static bool m_GetDebugVisible;
bool CollisionNode::m_GetDebugVisible=true;

/// <summary>
/// CollisionNode�̃����o�֐�
/// </summary>

void CollisionNode::SetParent(Obj3d * parent)
{
	m_Obj.SetParent(parent);
}


SphereNode::SphereNode()
{
	//�f�t�H���g���a1���[�g���ɂ���
	m_LocalRadius = 1.0f;
}

/// <summary>
/// SphereNode�̃����o�֐�
/// </summary>
void SphereNode::Initialize()
{
	//�f�o�b�N�\���p
	m_Obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_Obj.SetTrans(m_Ofset);
	m_Obj.SetScale(Vector3(m_LocalRadius));
	m_Obj.Update();

	{//���[���h���W�ł̓����蔻�苅���v�Z
		//�v�Z�ς݂̃��[���h�s����擾
		Matrix worldm = m_Obj.GetWorld();

		//���f���̍��W�n�ł̒��S�_
		Vector3 center(0, 0, 0);
		//���f�����W�n�ł̉E�[
		Vector3 right(1, 0, 0);
		//���[���h�s��ɕϊ�
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		//�����蔻��Ɍ��ʂ���
		Sphere::Center = center;
		Sphere::Radius = Vector3::Distance(center, right);
	}
}

void SphereNode::Draw()
{
	m_Obj.Draw();
}
