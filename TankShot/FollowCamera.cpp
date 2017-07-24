#include "pch.h"
#include "FollowCamera.h"
#include "Player.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//�ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERA_DISTANCE = 0.5f;

FollowCamera::FollowCamera(int width, int height)
	:Camera(width,height)
{
	m_target_pos=Vector3::Zero;
	m_target_angle = 0.0f;
	m_keyboard = nullptr;
	m_player = nullptr;
}

void FollowCamera::Update()
{

	//�L�[�{�[�h�̏�Ԏ擾
	Keyboard::State keyboardstate = m_keyboard->GetState();
	m_keyboardTracker.Update(keyboardstate);

	if (m_player)
	{
		SetTargetPos(m_player->GetParentTrans());
		SetTargetAngle(m_player->GetParentRotation().y);
	}

	//C�L�[���������Ƃ�FPS/TPS��؂�ւ�
	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keys::C))
	{
		////�t���O��؂�ւ�
		//if (ModeChange != true)
		//{
		//	ModeChange = true;
		//}
		//else
		//{
		//	ModeChange = false;
		//}

		//�t���O��؂�ւ�(��̏�������s�ɏo����)
		ModeChange = !ModeChange;
		
	}
	if (ModeChange == true)
	{
		//TPS�J��������
		const float CAMERA_DISTANCE = 5.0f;
		//���_�A�Q�Ɠ_
		Vector3 eyepos, refpos;
		//���@�̏��2m�����Q�Ɠ_
		refpos = m_target_pos + Vector3(0, 2, 0);
		//�Q�Ɠ_�Ǝ��_�̍����̃x�N�g��
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
		//���@�̌��ɉ�荞�񂽂߂̉�]�s��𐶐�
		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
		//�����x�N�g������]
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		eyepos = refpos + cameraV;
		//���_�����݈ʒu�����Ԃ���
		eyepos = m_eyepos + (eyepos - m_eyepos)*0.05f;
		//�Q�Ɠ_�����݈ʒu�����Ԃ���
		refpos = m_refpos + (refpos - m_refpos)*0.2f;

		SetEyePos(eyepos);		//this���ȗ�
		SetRefPos(refpos);
	}
	if (ModeChange == false)
	{
		const float CAMERA_DISTANCE = 5.0f;
		//���_�A�Q�Ɠ_
		Vector3 eyepos, refpos;
		//���@�̖ڂ̈ʒu����������_�Ƃ���
		Vector3 UpPos;
		UpPos = m_target_pos + Vector3(0, 0.2f, 0);
		//�Q�Ɠ_�Ǝ��_�̍����̃x�N�g��
		Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANCE);
		//���@�̌��ɉ�荞�񂽂߂̉�]�s��𐶐�
		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
		//�����x�N�g������]
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		eyepos = UpPos + cameraV*0.1f;
		//�Q�Ɠ_���W���v�Z
		refpos = eyepos + cameraV;

		SetEyePos(eyepos);		//this���ȗ�
		SetRefPos(refpos);
	}

	//���N���X�̍X�V
	Camera::Update();

}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_target_pos = targetpos;
}

void FollowCamera::SetTargetAngle(float targetangle)
{
	m_target_angle = targetangle;
}

void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}

void FollowCamera::SetPlayer(Player * player)
{
	m_player = player;
}
