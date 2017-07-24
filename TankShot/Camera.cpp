#include "pch.h"
#include "Camera.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera(int width,int height)
{
	//�����o�ϐ��̏�����
	m_eyepos = Vector3(0, 0, 5.0f);
	m_refpos =Vector3(10, 10, 10);
	m_upvec = Vector3(0, 1, 0);
	m_fovY = XMConvertToRadians(60.0f);
	m_aspect = (float)width / height;
	m_nearClip = 0.1f;
	m_farClip = 1000.0f;

	//�r���[�s��̐���
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//�ˉe�s��̐���(�������e)
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);

}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{

}
/// <summary>
/// Updata
/// </summary>
void Camera::Update()
{
	//�r���[�s��̐���
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//�ˉe�s��̐���
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip,m_farClip);
}

//�r���[�s����擾
const Matrix& Camera::GetView()
{
	return m_view;
}

//�v���W�F�N�V�����s����擾
const Matrix& Camera::GetProjection()
{
	return m_proj;
}

//���_���Z�b�g
void Camera::SetEyePos(const Vector3& eyepos)
{
	m_eyepos = eyepos;

}
//�����_���Z�b�g
void Camera::SetRefPos(const Vector3& refpos)
{
	m_refpos = refpos;

}
//������x�N�g�����Z�b�g
void Camera::SetUpVec(const Vector3& upvec)
{
	m_upvec = upvec;
}

void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

void Camera::SetNearClip(float nearclip)
{
	m_nearClip = nearclip;
}

void Camera::SetFarClip(float farClip)
{
	m_farClip = farClip;
}
