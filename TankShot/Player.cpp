#include "pch.h"
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player()
{
}


Player::~Player()
{
}

//������
void Player::Initialize()
{
	//���@�p�[�c�̓ǂݍ���
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resources/Body.cmo");
	m_ObjPlayer[PLAYER_PARTS_NECK].LoadModel(L"Resources/Neck.cmo");
	m_ObjPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resources/Head.cmo");
	m_ObjPlayer[PLAYER_PARTS_LEGS].LoadModel(L"Resources/Legs.cmo");
	m_ObjPlayer[PLAYER_PARTS_WINGS].LoadModel(L"Resources/Wings.cmo");

	//�p�[�c�̐e�q�֌W���Z�b�g
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetParent(&m_ObjPlayer[PLAYER_PARTS_NECK]);
	m_ObjPlayer[PLAYER_PARTS_NECK].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_LEGS].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);

	//////�e����̃I�t�Z�b�g(���W�̂��炵��)���Z�b�g
	m_ObjPlayer[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//////�ό`�O�̐ݒ�
	m_ObjPlayer[PLAYER_PARTS_BODY].SetTrans(Vector3(0, 1.2f, 0));
	m_ObjPlayer[PLAYER_PARTS_NECK].SetScale(Vector3(1.2f, 1.2f, 1.2f));
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetTrans(Vector3(0, 2, -12));
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetRotation(Vector3(-1.5, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_NECK].SetRotation(Vector3(-4.75, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_NECK].SetTrans(Vector3(0, -8, 3));
	m_ObjPlayer[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	m_ObjPlayer[PLAYER_PARTS_LEGS].SetRotation(Vector3(0, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_LEGS].SetTrans(Vector3(0, 0, 0));

	returnTimer = 0;

	{//�e�ۗp�̓����蔻���ݒ�
		m_CollisionNodeBullet.Initialize();
		//�e�p�[�c���w��
		m_CollisionNodeBullet.SetParent(&m_ObjPlayer[PLAYER_PARTS_WINGS]);
		m_CollisionNodeBullet.SetOfset(Vector3(0, -3, 0));
		m_CollisionNodeBullet.SetLocalRadius(10.0f);
	}

	{//�e�ۗp�̓����蔻���ݒ�
		m_CollisionNodeBody.Initialize();
		//�e�p�[�c���w��
		m_CollisionNodeBody.SetParent(&m_ObjPlayer[0]);
		m_CollisionNodeBody.SetOfset(Vector3(0, -1, 0));
		m_CollisionNodeBody.SetLocalRadius(7.0f);
	}

}

//�X�V
void Player::Update()
{
	if (m_key.IsKeyDown(Keyboard::Keys::Space))
	{
		//�W�����v�J�n
		StartJump();
	}

	// �W�����v��
	if (m_isJump)
	{
		m_Velocity.y -= GRAVITY_ACC;
		// ���x����
		if (m_Velocity.y <= -JUMP_SPEED_MAX)
		{
			m_Velocity.y = -JUMP_SPEED_MAX;
		}
	}

	Vector3 trans = this->GetTrans();
	trans += m_Velocity;
	this->SetParentTrans(trans);

	//A�L�[��������Ă����獶����
	if (m_key.A)
	{
		//���@�̊p�x����]������
		float angle = GetParentRotation().y;
		SetParentRotation(Vector3(0, angle + 0.03f, 0));
	}
	//D�L�[��������Ă�����E����
	if (m_key.D)
	{
		//���@�̊p�x����]������
		float angle = GetParentRotation().y;
		SetParentRotation(Vector3(0, angle - 0.03f, 0));
	}

	//W�L�[��������Ă�����O�i
	if (m_key.W)
	{
		//�ړ��x�N�g��(Z���W)
		Vector3 moveV(0, 0, -0.1f);
		//�ړ��ʃx�N�g�������@�̊p�x����]������
		float angle = GetParentRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//���@�̍��W���ړ�������
		Vector3 pos = GetParentTrans();
		SetParentTrans(pos + moveV);
	}
	//S�L�[��������Ă�������
	if (m_key.S)
	{
		//�ړ��x�N�g��(Z���W)
		Vector3 moveV(0, 0, 0.1f);
		//�ړ��ʃx�N�g�������@�̊p�x����]������
		float angle = GetParentRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//���@�̍��W���ړ�������
		Vector3 pos = GetParentTrans();
		SetParentTrans(pos + moveV);
	}
	//SPACE�L�[�ŕό`
	//if (m_key.Space)
	//{
	//	int cnt = 10;
	//	////�ʏ���
	//	//if (ModiFlag == true)
	// 	//{
	//	//	m_ObjPlayer[PLAYER_PARTS_BODY].SetTrans(Vector3(0, 1.2f, 0));
	//	//	m_ObjPlayer[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//	//	m_ObjPlayer[PLAYER_PARTS_NECK].SetScale(Vector3(6, 6, 6));
	//	//	m_ObjPlayer[PLAYER_PARTS_HEAD].SetTrans(Vector3(0, 0, -0.2f));
	//	//	m_ObjPlayer[PLAYER_PARTS_NECK].SetTrans(Vector3(0, 0, -3.5f));
	//	//}
	//	////�ό`��
	//	//if (ModiFlag == false)
	//	//{
	//	if (ModiFlag == true)
	//	{
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetTrans();
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetRotation();
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetWorld();

	//		//�ό`��̐ݒ�
	//		m_ObjPlayer[PLAYER_PARTS_BODY].SetTrans(Vector3(0, 1.2f, 0));
	//		m_ObjPlayer[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//		m_ObjPlayer[PLAYER_PARTS_NECK].SetScale(Vector3(1.2f, 1.2f, 1.2f));
	//		m_ObjPlayer[PLAYER_PARTS_HEAD].SetTrans(Vector3(0, 0, -0.2f));
	//		m_ObjPlayer[PLAYER_PARTS_HEAD].SetRotation(Vector3(0, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_NECK].SetTrans(Vector3(0, 0.9, 0));
	//		m_ObjPlayer[PLAYER_PARTS_NECK].SetRotation(Vector3(0, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_LEGS].SetRotation(Vector3(3.15, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_LEGS].SetTrans(Vector3(0, -16.4, 3));


	//		ModiFlag = false;
	//	}

	//}
	////SPACE�L�[�ŕό`
	//if (m_key.B)
	//{
	//	int cnt = 10;
	//	//�ʏ���
	//	if (ModiFlag == false)
	//	{
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetTrans();
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetRotation();
	//		m_ObjPlayer[PLAYER_PARTS_BODY].GetWorld();

	//		m_ObjPlayer[PLAYER_PARTS_BODY].SetTrans(Vector3(m_ObjPlayer[PLAYER_PARTS_BODY].GetTrans().x, 1.2f, m_ObjPlayer[PLAYER_PARTS_BODY].GetTrans().z));
	//		m_ObjPlayer[PLAYER_PARTS_HEAD].SetTrans(Vector3(0, 2, -12));
	//		m_ObjPlayer[PLAYER_PARTS_HEAD].SetRotation(Vector3(-1.5, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_NECK].SetRotation(Vector3(-4.75, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_NECK].SetTrans(Vector3(0, -8, 3));
	//		m_ObjPlayer[PLAYER_PARTS_BODY].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//		m_ObjPlayer[PLAYER_PARTS_LEGS].SetRotation(Vector3(0, 0, 0));
	//		m_ObjPlayer[PLAYER_PARTS_LEGS].SetTrans(Vector3(0, 0, 0));
	//		ModiFlag = true;

	//	}
	//}
	if (m_key.Space)
	{
		ShotFlag = false;
	}

	if (ShotFlag == false)
	{
		FireBullet();

		Vector3 pos = m_ObjPlayer[PLAYER_PARTS_WINGS].GetTrans();
		m_ObjPlayer[PLAYER_PARTS_WINGS].SetTrans(pos + m_BulletVel);
		returnTimer++;
		if (returnTimer >= 120)
		{
			ResetBullet();
			ShotFlag = true;
			returnTimer = 0;
		}
	}
	//if (m_key.IsKeyDown(Keyboard::Keys::D1))
	//{
	//	ChangeFlag();
	//}
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Update();
	}
	m_CollisionNodeBody.Update();
	m_CollisionNodeBullet.Update();
}

//�v���C���[�̕`��
void Player::PlayerDraw()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Draw();
	}

	//if (ReturnFlag()==false)
	//{
	m_CollisionNodeBody.Draw();
	//}
}

void Player::FireBullet()
{
	if (m_FireFlag) return;

	// ���˂���p�[�c�̃t�B�[���h�s����擾
	Matrix worldm = m_ObjPlayer[PLAYER_PARTS_WINGS].GetWorld();
	//���[���h�s�񂩂�e�v�f�𒊏o
	Vector3 scale;				//���[���h�X�P�[�����O
	Quaternion rotation;		//���[���h��]
	Vector3 translation;		//���[���h���W
	worldm.Decompose(scale, rotation, translation);

	//���˃p�[�c��e���番�����ēƗ�
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetParent(nullptr);
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetScale(scale);
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetRotationQ(rotation);
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetTrans(translation);

	//�e�ۂ̑��x��ݒ�
	m_BulletVel = Vector3(0, 0, -0.3f);
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

	m_FireFlag = true;
}

void Player::ResetBullet()
{
	//���˒��łȂ�
	if (!m_FireFlag)	return;
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetParent(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetScale(Vector3(1, 1, 1));
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetRotation(Vector3(0, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_WINGS].SetTrans(Vector3(0, 0, 0));

	m_FireFlag = false;
}

//�L�[�{�[�h�̃Z�b�g
void Player::SetKeyBord(Keyboard::State key)
{
	m_key = key;
}

//�e�I�u�W�F�N�g�̉�]�p���Z�b�g
void Player::SetParentRotation(DirectX::SimpleMath::Vector3 rotate)
{
	m_ObjPlayer[PLAYER_PARTS_BODY].SetRotation(rotate);
}

//�e�I�u�W�F�N�g�̍��W���Z�b�g
void Player::SetParentTrans(DirectX::SimpleMath::Vector3 trans)
{
	m_ObjPlayer[PLAYER_PARTS_BODY].SetTrans(trans);
}

//�e�I�u�W�F�N�g�̉�]�p���擾
const DirectX::SimpleMath::Vector3 Player::GetParentRotation()
{
	return m_ObjPlayer[PLAYER_PARTS_BODY].GetRotation();
}

//�e�I�u�W�F�N�g�̍��W���擾
const DirectX::SimpleMath::Vector3 Player::GetParentTrans()
{
	return m_ObjPlayer[PLAYER_PARTS_BODY].GetTrans();
}

bool Player::ChangeFlag()
{
	DebugFlag = !DebugFlag;

	return DebugFlag;
}

bool Player::ReturnFlag()
{
	return DebugFlag;
}


/// <summary>
/// �W�����v�J�n
/// </summary>
void Player::StartJump()
{
	//�W�����v���łȂ�
	if (!m_isJump)
	{
		//
		m_Velocity.y = JUMP_SPEED_FIRST;
		m_isJump = true;
	}
}

/// <summary>
/// �����J�n
/// </summary>
void Player::StartFall()
{
	//
	if (!m_isJump)
	{
		//
		m_Velocity.y = 0.0f;
		m_isJump = true;
	}
}
/// <summary>
/// �W�����v���I������
/// <summary>
void Player::StopJump()
{
	m_isJump = false;
	m_Velocity = Vector3::Zero;
}