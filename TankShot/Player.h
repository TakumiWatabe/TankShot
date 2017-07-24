#pragma once
#include <Keyboard.h>
#include <SimpleMath.h>
#include "FollowCamera.h"
#include "Obj3d.h"
#include <vector>
#include "CollisionNode.h"
#include "Collision.h"
class Player :public Obj3d
{
protected:
	std::vector<Obj3d> m_ObjPlayer;
	DirectX::Keyboard::State m_key;

	//�ό`���邽�߂̃t���O
	bool ModiFlag = true;
	//���˂��Ă��邩�ǂ����̃t���O
	bool m_FireFlag = false;
	//�e�ۂ̑��x�x�N�g��
	DirectX::SimpleMath::Vector3 m_BulletVel;
	//���˗p�̃t���O
	bool ShotFlag = true;
	//����߂����߂̃^�C�}�[
	float returnTimer;

	//�e�ۗp�̓����蔻��
	SphereNode m_CollisionNodeBody;
	SphereNode m_CollisionNodeBullet;
	bool DebugFlag = true;

	// ���x
	DirectX::SimpleMath::Vector3 m_Velocity;
	bool m_isJump;

public:
	// �d�͉����x<m/frame^2>
	const float GRAVITY_ACC = 0.03f;
	// �W�����v����<m/frame>
	const float JUMP_SPEED_FIRST = 0.5f;
	// �������x����<m/frame>
	const float JUMP_SPEED_MAX = 0.3f;

	//���@�p�[�c
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_BODY,
		PLAYER_PARTS_NECK,
		PLAYER_PARTS_HEAD,
		PLAYER_PARTS_LEGS,
		PLAYER_PARTS_WINGS,

		PLAYER_PARTS_NUM
	};
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//������
	void Initialize();
	//�X�V
	void Update();
	//�v���C���[�̕`��
	void PlayerDraw();
	//�e�ۂ𔭎�
	void FireBullet();
	//�e�ۂ��đ��U(���Z�b�g)
	void ResetBullet();
	//�L�[�{�[�h�̃Z�b�g
	void SetKeyBord(DirectX::Keyboard::State key);
	//�e�I�u�W�F�N�g�̉�]�p���Z�b�g
	void SetParentRotation(DirectX::SimpleMath::Vector3 rotate);
	//�e�I�u�W�F�N�g�̍��W���Z�b�g
	void SetParentTrans(DirectX::SimpleMath::Vector3 trans);
	//�e�I�u�W�F�N�g�̉�]�p���擾
	const DirectX::SimpleMath::Vector3 GetParentRotation();
	//�e�I�u�W�F�N�g�̍��W���擾
	const DirectX::SimpleMath::Vector3 GetParentTrans();
	//�S�g�p�̓����蔻����擾
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNodeBullet; };
	//�S�g�p�̓����蔻����擾
	const SphereNode& GetCollisionNodeBody() { return m_CollisionNodeBody; };
	const DirectX::SimpleMath::Vector3& GetVeclocity() { return m_BulletVel; };
	//�t���O�̒l��Ԃ����߂̊֐�
	bool ChangeFlag();
	bool ReturnFlag();
	void StartJump();
	void StartFall();
	void StopJump();
};
