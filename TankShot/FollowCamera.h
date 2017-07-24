/// <summary>
/// ���@�ɒǏ]����J�����N���X
/// </summary>
#pragma once

#include "Camera.h"
#include <Keyboard.h>
#include "Player.h"

class Player;

class FollowCamera : public Camera
{
public:
	//�Ǐ]�Ώۂ̃J�����̋���
	static const float CAMERA_DISTANCE;

	//�R���X�g���N�^
	FollowCamera(int width,int height);

	//���t���[���X�V
	void Update() override;

	//���_���Z�b�g
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);

	//���_���Z�b�g
	void SetTargetAngle(float targetangle);

	//�L�[�{�[�h���Z�b�g
	void SetKeyboard(DirectX::Keyboard* keyboard);

	//Player���Z�b�g
	void SetPlayer(Player* player);
protected:
	//�Ǐ]�Ώۂ̍��W
	DirectX::SimpleMath::Vector3 m_target_pos;
	//�Ǐ]�Ώۂ̉�]�p
	float m_target_angle;
	//�L�[�{�[�h
	DirectX::Keyboard* m_keyboard;
	//�L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;
	//FPS/TPS�̐؂�ւ��p�t���O
	bool ModeChange=true;
	//�v���C���[
	Player* m_player;
};
