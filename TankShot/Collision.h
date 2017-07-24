/// <summary>
/// �����蔻��p�̃��C�u����
/// </summary>

#pragma once

//#include <Windows.h>
#include <d3d11_1.h>
#include <SimpleMath.h>

//���O�̃��C�u�����ł͂�����������
//namespace Collision
//{}

//���`��̃N���X
class Sphere
{
public:
	//���a
	float Radius;
	//���S���W
	DirectX::SimpleMath::Vector3 Center;
	// �R���X�g���N�^
	Sphere() { Radius = 1.0f; }
};

//����
class Segment
{
public:
	//���_���W
	DirectX::SimpleMath::Vector3 Start;
	//�I�_���W
	DirectX::SimpleMath::Vector3 End;

};

class Collision
{
public:
	Collision();
	~Collision();
};

// �@���t���O�p�`�i�����v��肪�\�ʁj

class Triangle

{
public:

	DirectX::SimpleMath::Vector3	P0;

	DirectX::SimpleMath::Vector3	P1;

	DirectX::SimpleMath::Vector3	P2;

	DirectX::SimpleMath::Vector3	Normal;	// �@���x�N�g��

};
bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);

void ComputeTriangle(const DirectX::SimpleMath::Vector3 & _p0, const DirectX::SimpleMath::Vector3 & _p1, const DirectX::SimpleMath::Vector3 & _p2, Triangle * _triangle);

bool CheckPoint2Triangle(const DirectX::SimpleMath::Vector3 & _point, const Triangle & _tri);

bool CheckSphere2Triangle(const Sphere & _sphere, const Triangle & _tri, DirectX::SimpleMath::Vector3 * _inter);

bool CheckSegment2Triangle(const Segment & _segment, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);
