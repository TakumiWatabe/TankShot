/// <summary>
/// �����蔻��̃m�[�h
/// </summary>
#pragma once

#include "Collision.h"
#include "Obj3d.h"
class CollisionNode
{
protected:
	//�f�o�b�O�\��ON
	static bool m_GetDebugVisible;

public:
	static bool SetDebugVisible(bool flag) { return m_GetDebugVisible = flag; }

	static bool GetDebugVisible() { return m_GetDebugVisible; }

public:
	
	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update() = 0;
	//�`��
	virtual void Draw() = 0;

	void SetParent(Obj3d* parent);

	void SetOfset(const DirectX::SimpleMath::Vector3& ofset) { m_Ofset = ofset; };
protected:
	//�f�o�b�N�\���p�̃I�u�W�F�N�g
	Obj3d m_Obj;
	//�e����̃I�t�Z�b�g(���W�̂���)
	DirectX::SimpleMath::Vector3 m_Ofset;
};
//�������蔻��m�[�h
class SphereNode :public CollisionNode, public Sphere
{
public:
	SphereNode();
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

	void SetLocalRadius(float radius) { m_LocalRadius = radius; };
protected:
	//���[�J�����a
	float m_LocalRadius;

};
