#include "pch.h"
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Enemy::Enemy()
{
	//Initialize();
	
}


Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{

	////���@�p�[�c�̓ǂݍ���
	m_ObjEnemy.resize(ENEMY_PARTS_NUM);
	m_ObjEnemy[ENEMY_PARTS_BODY].LoadModel(L"Resources/Body.cmo");
	//m_ObjEnemy[PLAYER_PARTS_NECK].LoadModel(L"Resources/Neck.cmo");
	//m_ObjEnemy[PLAYER_PARTS_HEAD].LoadModel(L"Resources/Head.cmo");
	//m_ObjEnemy[PLAYER_PARTS_LEGS].LoadModel(L"Resources/Legs.cmo");
	//m_ObjEnemy[PLAYER_PARTS_WINGS].LoadModel(L"Resources/Wings.cmo");

	////�p�[�c�̐e�q�֌W���Z�b�g
	//m_ObjEnemy[PLAYER_PARTS_HEAD].SetParent(&m_ObjEnemy[PLAYER_PARTS_NECK]);
	//m_ObjEnemy[PLAYER_PARTS_NECK].SetParent(&m_ObjEnemy[PLAYER_PARTS_BODY]);
	//m_ObjEnemy[PLAYER_PARTS_LEGS].SetParent(&m_ObjEnemy[PLAYER_PARTS_BODY]);
	//m_ObjEnemy[PLAYER_PARTS_WINGS].SetParent(&m_ObjEnemy[PLAYER_PARTS_BODY]);

	////////�e����̃I�t�Z�b�g(���W�̂��炵��)���Z�b�g
	m_ObjEnemy[ENEMY_PARTS_BODY].SetScale(Vector3(0.2f, 0.2f, 0.2f));
	////////�ό`�O�̐ݒ�
	m_ObjEnemy[ENEMY_PARTS_BODY].SetTrans(Vector3(0, 1.2f, 0));
	//m_ObjEnemy[PLAYER_PARTS_NECK].SetScale(Vector3(1.2f, 1.2f, 1.2f));
	//m_ObjEnemy[PLAYER_PARTS_HEAD].SetTrans(Vector3(0, 2, -12));
	//m_ObjEnemy[PLAYER_PARTS_HEAD].SetRotation(Vector3(-1.5, 0, 0));
	//m_ObjEnemy[PLAYER_PARTS_NECK].SetRotation(Vector3(-4.75, 0, 0));
	//m_ObjEnemy[PLAYER_PARTS_NECK].SetTrans(Vector3(0, -8, 3));
	//m_ObjEnemy[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//m_ObjEnemy[PLAYER_PARTS_LEGS].SetRotation(Vector3(0, 0, 0));
	//m_ObjEnemy[PLAYER_PARTS_LEGS].SetTrans(Vector3(0, 0, 0));
	
	//�����z�u
	Vector3 pos;
	pos.x = rand() % 15;
	pos.z = rand() % 10;
	//pos.y = 10;
	//pos.x = 0;
	//pos.z = 0;
	pos.y = 2;

	this->SetParentTrans(pos);

	m_Timer = 0;
	m_DistAngle = 0;

	{//�e�ۗp�̓����蔻���ݒ�
		CollisionNodeBody.Initialize();
		//�e�p�[�c���w��
		CollisionNodeBody.SetParent(&m_ObjEnemy[ENEMY_PARTS_BODY]);
		CollisionNodeBody.SetOfset(Vector3(0, -1, 0));
		CollisionNodeBody.SetLocalRadius(7.0f);
	}

}

//�X�V
void Enemy::Update()
{
	//����I�ɐi�s������ς���
	m_Timer--;
	if (m_Timer < 0)
	{
		//�J�E���g��0�ɒB������
		m_Timer = 60;

		//�ڕW�p�x��ύX
		float TargetAngle = (float)rand() / RAND_MAX - 0.5f;
		TargetAngle *= 180.0f;
		m_DistAngle += TargetAngle;
	}

	//�ڕW�n�_�Ɍ������āA�@�̂̊p�x�����킶���Ԃ���
	Vector3 rotv = m_ObjEnemy[ENEMY_PARTS_BODY].GetRotation();

	//�ڕW�p�x�ւ̍ŒZ�p�x���擾
	float angle = m_DistAngle - rotv.y;
	
	//180���𒴂��Ă����ꍇ�A�t���̂ق����߂�
	if (angle>XM_PI)
	{
		angle -= XM_2PI;
	}

	if (angle<-XM_PI)
	{
		angle += XM_2PI;
	}

	//���
	rotv.y += angle*0.01f;

	SetParentRotation(rotv);

	//�@�̂̌����Ă�������ɐi��

	//// �ړ��ʂ̃x�N�g��
	//Vector3 moveV(0, 0, -0.1f);
	//// �ړ��ʃx�N�g�������@�̊p�x����]������
	////moveV = Vector3::TransformNormal(moveV, tank_world);
	//angle = m_ObjEnemy[ENEMY_PARTS_BODY].GetRotation().y;
	//Matrix rotmat = Matrix::CreateRotationY(angle);
	//moveV = Vector3::TransformNormal(moveV, rotmat);
	//// ���@�̍��W���ړ�������
	//Vector3 pos = m_ObjEnemy[ENEMY_PARTS_BODY].GetTrans();
	//m_ObjEnemy[ENEMY_PARTS_BODY].SetTrans(pos + moveV);

	//���̍��W���擾
	Vector3 trans = m_ObjEnemy[ENEMY_PARTS_BODY].GetTrans();
	Vector3 move(0.2f, 0, -0.2f);
	Matrix  rotm= Matrix::CreateRotationY(rotv.y);
	move = Vector3::TransformNormal(move, rotm);
	//���W���ړ�
	trans += move;
	//�ړ���̍��W���Z�b�g
	m_ObjEnemy[ENEMY_PARTS_BODY].SetTrans(trans);


	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin(); it != m_ObjEnemy.end(); it++)
	{
		it->Update();
	}
	CollisionNodeBody.Update();
}

//�v���C���[�̕`��
void Enemy::EnemyDraw()
{
	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin(); it != m_ObjEnemy.end(); it++)
	{
		it->Draw();
	}
	CollisionNodeBody.Draw();
}

//�e�I�u�W�F�N�g�̉�]�p���Z�b�g
void Enemy::SetParentRotation(DirectX::SimpleMath::Vector3 rotate)
{
	m_ObjEnemy[ENEMY_PARTS_BODY].SetRotation(rotate);
}

//�e�I�u�W�F�N�g�̍��W���Z�b�g
void Enemy::SetParentTrans(DirectX::SimpleMath::Vector3 trans)
{
	m_ObjEnemy[ENEMY_PARTS_BODY].SetTrans(trans);
}

//�e�I�u�W�F�N�g�̉�]�p���擾
const DirectX::SimpleMath::Vector3 Enemy::GetParentRotation()
{
	return m_ObjEnemy[ENEMY_PARTS_BODY].GetRotation();
}

//�e�I�u�W�F�N�g�̍��W���擾
const DirectX::SimpleMath::Vector3 Enemy::GetParentTrans()
{
	return m_ObjEnemy[ENEMY_PARTS_BODY].GetTrans();
}

//float Enemy::GetShortAngleRad(float rot, float radian)
//{
//	float timestep = 0;
//	timestep += 0.01f;
//	Vector3::Lerp(Vector3(rot), Vector3(radian), timestep);
//}
