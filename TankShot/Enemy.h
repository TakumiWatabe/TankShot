#pragma once
#include <Keyboard.h>
#include <SimpleMath.h>
#include "FollowCamera.h"
#include "Obj3d.h"
#include <vector>
#include "CollisionNode.h"
#include "Collision.h"

class Enemy:public Obj3d
{
private:
	std::vector<Obj3d> m_ObjEnemy;
	//�ڕW�p�x��ێ�
	float m_DistAngle;
	//�e�ۗp�̓����蔻��
	SphereNode CollisionNodeBody;
	
public:
	//���@�p�[�c
	enum ENEMY_PARTS
	{
		ENEMY_PARTS_BODY,
		ENEMY_PARTS_NUM
	};
	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();

	//������
	void Initialize();
	//�X�V
	void Update();
	//�v���C���[�̕`��
	void EnemyDraw();
	//�e�I�u�W�F�N�g�̉�]�p���Z�b�g
	void SetParentRotation(DirectX::SimpleMath::Vector3 rotate);
	//�e�I�u�W�F�N�g�̍��W���Z�b�g
	void SetParentTrans(DirectX::SimpleMath::Vector3 trans);
	//�e�I�u�W�F�N�g�̉�]�p���擾
	const DirectX::SimpleMath::Vector3 GetParentRotation();
	//�e�I�u�W�F�N�g�̍��W���擾
	const DirectX::SimpleMath::Vector3 GetParentTrans();
	//�p�x��⊮����
	float GetShortAngleRad(float rot, float radian);
	//�S�g�p�̓����蔻����擾
	const SphereNode& GetCollisionNodeBody() { return CollisionNodeBody; };

protected:
	//�^�C�}�[
	int m_Timer;

};

